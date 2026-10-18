/*
 * Exact Beltrami flow benchmark for Leray overlooking the Seine.
 *
 * Periodic box (2*pi)^3, with u(x,y,z,0) = (sin z, cos z, 0).
 * Curl u = u, divergence u = 0, Laplacian u = -u, u.grad u = 0.
 * For viscosity nu, u(t) = exp(-nu*t) u(0) solves unforced NS.
 *
 * The z-only reduction below tests periodic centered differences and
 * forward-Euler viscous diffusion. This is NOT a general 3-D CFD solver.
 * All diagnostics are normalized per unit volume of the 3-D domain.
 *
 * No external dependencies beyond the C11 standard library and libm.
 */
#include <math.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const double pi = 3.141592653589793238462643383279502884;

typedef struct {
    unsigned grid, steps;
    double nu, time;
    double rel_exact, rel_semidiscrete, particle_displacement_error;
    double laplace_truncation, curl_truncation;
    double energy, energy_exact;
    double energy_semidiscrete;
    double helicity, helicity_exact;
    double helicity_semidiscrete, displacement;
    double divergence_max;
} Result;

static int simulate(unsigned grid, unsigned steps, double nu, double stop, Result *out)
{
    /* Bound resources and keep the relative diagnostics representable. */
    if (grid < 8 || grid > 4096 || steps == 0 || steps > 2000000
        || (double)grid*steps > 200000000.0 || nu < 0 || stop < 0
        || !isfinite(nu) || !isfinite(stop) || nu*stop > 300.0)
        return 0;
    double h = (2.0*pi) / grid;
    double dt = stop / steps;
    double r = nu*dt/(h*h);
    if (!isfinite(r) || r > 0.5)
        return 0; /* explicit diffusion requires 0 <= r <= 1/2 */

    double *data = calloc((size_t)grid*7, sizeof *data);
    if (!data) return 0;
    double *x = data, *y = data + grid;
    double *next_x = data + 2*grid, *next_y = data + 3*grid;
    double *particle_x = data + 4*grid, *particle_y = data + 5*grid;
    double *vertical = data + 6*grid;
    for (unsigned j=0;j<grid;j++) {
        double z = j*h;
        x[j] = sin(z);
        y[j] = cos(z);
    }
    for (unsigned t=0;t<steps;t++) {
        for (unsigned j=0;j<grid;j++) {
            unsigned l = j ? j-1 : grid-1;
            unsigned rj = (j+1==grid) ? 0 : j+1;
            next_x[j] = x[j] + r*(x[l]-2*x[j]+x[rj]);
            next_y[j] = y[j] + r*(y[l]-2*y[j]+y[rj]);
            /* Particles have fixed z: integrate their horizontal path. */
            particle_x[j] += 0.5*dt*(x[j]+next_x[j]);
            particle_y[j] += 0.5*dt*(y[j]+next_y[j]);
        }
        double *temp = x; x = next_x; next_x = temp;
        temp = y; y = next_y; next_y = temp;
    }

    double amplitude_exact = exp(-nu*stop);
    double eigen = 4.0*pow(sin(h/2.0),2)/(h*h);
    double amplitude_semidiscrete = exp(-nu*eigen*stop);
    double err_exact=0, err_semidiscrete=0, particle_error=0, energy=0, helicity=0;
    double particle_factor=nu==0 ? stop : -expm1(-nu*stop)/nu;
    double lap_err=0, curl_err=0, displacement_squared=0, divergence_max=0;
    for (unsigned j=0;j<grid;j++) {
        unsigned l=j ? j-1 : grid-1;
        unsigned rj=(j+1==grid) ? 0 : j+1;
        double z=j*h, sx=sin(z), cy=cos(z);
        double dx=x[j]-amplitude_exact*sx;
        double dy=y[j]-amplitude_exact*cy;
        double ddx=x[j]-amplitude_semidiscrete*sx;
        double ddy=y[j]-amplitude_semidiscrete*cy;
        double curl_x=-(y[rj]-y[l])/(2*h);
        double curl_y=(x[rj]-x[l])/(2*h);
        /* Compare the discrete operators on the exact initial field.
         * For u0, -d_z cos z = sin z and d_z sin z = cos z. */
        double curl0_x=-(cos((rj)*h)-cos(l*h))/(2*h);
        double curl0_y=(sin((rj)*h)-sin(l*h))/(2*h);
        double lap0_x=(sin(l*h)-2*sx+sin(rj*h))/(h*h);
        double lap0_y=(cos(l*h)-2*cy+cos(rj*h))/(h*h);
        err_exact += dx*dx+dy*dy;
        particle_error += pow(particle_x[j]-particle_factor*sx,2)
                        + pow(particle_y[j]-particle_factor*cy,2);
        err_semidiscrete += ddx*ddx+ddy*ddy;
        energy += (x[j]*x[j]+y[j]*y[j])/2;
        helicity += x[j]*curl_x+y[j]*curl_y;
        lap_err += (lap0_x+sx)*(lap0_x+sx)+(lap0_y+cy)*(lap0_y+cy);
        curl_err += (curl0_x-sx)*(curl0_x-sx)+(curl0_y-cy)*(curl0_y-cy);
        displacement_squared += particle_x[j]*particle_x[j]+particle_y[j]*particle_y[j];
        /* Horizontal derivatives vanish because all arrays depend on z only.
         * Measure the remaining term; this is an ansatz diagnostic, not a
         * pressure projection or a general incompressibility test. */
        double divergence = fabs((vertical[rj]-vertical[l])/(2*h));
        if (divergence > divergence_max) divergence_max=divergence;
    }
    out->grid=grid;
    out->steps=steps;
    out->nu=nu;
    out->time=stop;
    out->rel_exact=sqrt(err_exact/grid)/amplitude_exact;
    out->rel_semidiscrete=sqrt(err_semidiscrete/grid)/amplitude_semidiscrete;
    out->particle_displacement_error=sqrt(particle_error/grid);
    out->laplace_truncation=sqrt(lap_err/grid);
    out->curl_truncation=sqrt(curl_err/grid);
    out->energy=energy/grid;
    out->energy_exact=0.5*exp(-2*nu*stop);
    out->energy_semidiscrete=0.5*amplitude_semidiscrete*amplitude_semidiscrete;
    out->helicity=helicity/grid;
    out->helicity_exact=exp(-2*nu*stop);
    out->helicity_semidiscrete=(sin(h)/h)*amplitude_semidiscrete*amplitude_semidiscrete;
    out->divergence_max=divergence_max;
    out->displacement=sqrt(displacement_squared/grid);
    free(data);
    return 1;
}

static void print_result(const char *test, Result a)
{
    printf("%s\t%u\t%u\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\t%.17g\n",
           test, a.grid, a.steps, a.nu, a.time,
           a.rel_exact, a.rel_semidiscrete, a.laplace_truncation,
           a.curl_truncation, a.particle_displacement_error, a.energy, a.energy_exact,
           a.energy_semidiscrete, a.helicity, a.helicity_exact,
           a.helicity_semidiscrete, a.divergence_max, a.displacement);
}

static int in_range(double value, double min, double max)
{
    return isfinite(value) && value > min && value < max;
}

static void print_header(void)
{
    puts("case\tgrid\tsteps\tnu\ttime\tvelocity_error\ttemporal_error\tlaplace_error\tcurl_error\tparticle_error\tenergy\tenergy_exact\tenergy_semidiscrete\thelicity\thelicity_exact\thelicity_semidiscrete\tdivergence_max\tdisplacement");
}

static int parse_unsigned(const char *text, unsigned *value)
{
    if (!*text) return 0;
    for (const char *c=text; *c; ++c) if (*c<'0' || *c>'9') return 0;
    char *end;
    errno=0;
    unsigned long parsed=strtoul(text,&end,10);
    if (errno || *end || parsed>UINT_MAX) return 0;
    *value=(unsigned)parsed;
    return 1;
}

static int parse_real(const char *text, double *value)
{
    if (!*text || *text==' ' || *text=='\t' || *text=='\n') return 0;
    char *end;
    errno=0;
    *value=strtod(text,&end);
    return !errno && !*end && isfinite(*value);
}

int main(int argc, char **argv)
{
    if (argc!=1 && !(argc==2 && strcmp(argv[1],"suite")==0)) {
        unsigned grid,steps;
        double nu,stop;
        Result result;
        if (argc!=6 || strcmp(argv[1],"run")!=0
            || !parse_unsigned(argv[2],&grid) || !parse_unsigned(argv[3],&steps)
            || !parse_real(argv[4],&nu) || !parse_real(argv[5],&stop)
            || !simulate(grid,steps,nu,stop,&result)) {
            fputs("Rejected invalid parameters, unsupported resource/decay range, or unstable timestep.\n"
                  "Usage: beltrami [suite | run GRID STEPS VISCOSITY FINAL_TIME]\n",stderr);
            return 2;
        }
        print_header();
        print_result("custom",result);
        return 0;
    }
    const double viscosity=0.2, final_time=1.0;
    int failures=0;
    Result prev={0};
    print_header();
    for (unsigned n=16;n<=128;n*=2) {
        Result current;
        if (!simulate(n,1,0,0,&current)) return 2;
        print_result("spatial",current);
        if (n>16 && !in_range(prev.laplace_truncation/current.laplace_truncation,3.90,4.10)) failures++;
        if (n>16 && !in_range(prev.curl_truncation/current.curl_truncation,3.90,4.10)) failures++;
        prev=current;
    }
    memset(&prev,0,sizeof prev);
    for (unsigned s=64;s<=512;s*=2) {
        Result current;
        if (!simulate(64,s,viscosity,final_time,&current)) return 2;
        print_result("temporal",current);
        if (s>64 && !in_range(prev.rel_semidiscrete/current.rel_semidiscrete,1.90,2.10)) failures++;
        prev=current;
    }
    memset(&prev,0,sizeof prev);
    for (unsigned n=16;n<=128;n*=2) {
        Result current;
        if (!simulate(n,4*n*n,viscosity,final_time,&current)) return 2;
        print_result("combined",current);
        if (n>16 && !in_range(prev.rel_exact/current.rel_exact,3.85,4.15)) failures++;
        if (!in_range(current.energy,0.0,1.0)) failures++;
        if (!in_range(current.helicity,0.0,2.0)) failures++;
        if (current.particle_displacement_error > 0.01) failures++;
        prev=current;
    }
    Result inviscid;
    if (!simulate(64,512,0,final_time,&inviscid)) return 2;
    print_result("inviscid",inviscid);
    if (inviscid.rel_exact>1e-12 || fabs(inviscid.energy-0.5)>1e-12
        || inviscid.particle_displacement_error>1e-12)
        failures++;
    Result invalid;
    if (simulate(64,1,10.0,1.0,&invalid) || simulate(3,20,0.2,1.0,&invalid) || simulate(16,20,-1.0,1.0,&invalid))
        failures++;
    for (unsigned i=0; i<3; ++i) {
        const double times[3]={0.5,1.0,2.0};
        Result decay;
        if (!simulate(64,512,viscosity,times[i],&decay)) return 2;
        print_result("decay",decay);
    }
    if (failures) fprintf(stderr,"Producer convergence checks failed: %d\n",failures);
    return failures ? 1 : 0;
}
