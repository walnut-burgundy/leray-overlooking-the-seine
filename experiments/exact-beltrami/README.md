# Exact periodic Beltrami flow

On the periodic box of side 2π, the initial velocity is
u₀ = (sin z, cos z, 0). The velocity stays equal to e^(−νt)u₀:
each particle keeps its z coordinate while its horizontal speed decays.
At ν = 0 the field stays fixed.

This C11 benchmark evolves that invariant, z-only diffusion subproblem using
periodic centered second differences and forward Euler time steps. It is a
**reduced exact-flow calculation, not a general 3-D Navier–Stokes solver**.
It exercises no nonlinear advection, pressure projection, walls or instability.

## Exact quantities

Curl u₀ = u₀, Δu₀ = −u₀, divergence u₀ = 0, and (u₀·∇)u₀ = 0.
With constant pressure and no forcing, energy per unit volume is
½e^(−2νt), helicity per unit volume is e^(−2νt), and particle displacement is

    [(1 − e^(−νt))/ν] (sin z, cos z), for ν > 0;
    t (sin z, cos z), for ν = 0.

For grid spacing h = 2π/N, the discrete diffusion eigenvalue is
λₕ = 4sin²(h/2)/h² and the centered curl factor is cₕ = sin(h)/h.
The semidiscrete amplitude is e^(−νλₕt); the fully discrete amplitude is
(1 − νλₕΔt)^steps. The semidiscrete energy is ½e^(−2νλₕt);
its discrete helicity is cₕe^(−2νλₕt). Finite-grid helicity consequently
differs from continuum helicity, including in the inviscid case.

The implementation advances actual sampled arrays, measures their velocity,
energy and centered curl, and accumulates particle paths with the trapezoidal
rule. The independent MOON/AI-CI verifier uses long-double closed forms,
including the closed geometric sum for particle displacement. It does not
reuse the producer's stencil loop or saved reference values.

## Separate refinements

| Cases | Held fixed | Varied | Checked result |
|---|---|---|---|
| Spatial | Initial field; t = 0 | N = 16,32,64,128 | Laplacian/curl error O(h²) |
| Temporal | N = 64, ν = .2, t = 1 | 64,128,256,512 steps | Velocity error against semidiscrete oracle O(Δt) |
| Combined | ν = .2, t = 1 | N doubled; steps = 4N² | Continuous velocity error O(h²) |
| Inviscid | N = 64, 512 steps, t = 1 | ν = 0 | Velocity, energy and particle translation |
| Decay | N = 64, 512 steps, ν = .2 | t = .5,1,2 | Quantitative energy/helicity decay |

The TSV includes all 16 cases, continuous and semidiscrete energy/helicity
references, relative velocity errors, operator errors, particle-displacement
error, measured displacement and maximum divergence. Divergence checks only
the chosen ansatz: the horizontal derivatives vanish and stored vertical
velocity stays zero. It cannot validate general incompressibility enforcement.

## Build and acceptance

Use the registered FP operation `leray-exact-01`. The
[exact-head workflow](../../.github/workflows/leray-exact-01.yml) pins FP,
Kitchen, Ike, the independent AI-CI source and the qualified ICK C compiler.
Kitchen runs the local `Ikefile` through compiled Grease. No stock consumer
compiler fallback is supplied.

The workflow records the C11 mode, compiler driver/frontend, runtime libraries,
source heads/digests, Ike receipt, two binary builds and two runtime outputs.
Both binary and output pairs must match byte for byte. The independent verifier
recomputes every diagnostic and reference; its 41 targeted corruption controls
must reject. Kitchen also observes 14 invalid-input exits, corrupts every numeric
diagnostic/reference column and requires rejection of a truncated suite.

The executable accepts no arguments (or `suite`) for the full suite, or
`run GRID STEPS VISCOSITY FINAL_TIME` for one diagnostic case. It rejects
nonfinite/negative viscosity or time, malformed integers, grids outside
8…4096, zero/oversized step counts, νΔt/h² > ½, excessive work, and νt > 300.
The last two are explicit resource/representability limits, not physical claims.

## Provenance and limits

The original C source and README were recovered only after FP checked and
recorded `leray-verification.zip`, SHA-256
`b804351df2404ee9fbe7c898a4901a45fa07e9615e29083dbd8c2286cdff7df6`.
See [source-artifact.tsv](source-artifact.tsv). Original local output remains
historical, unaccepted evidence; registration and source review grant no
numerical PASS. Hosted build/runtime and independent acceptance receipts are
required before acceptance. The PR remains draft; no direct merge is authorized.

Pressure-gradient invariance, geometric-method comparisons, the smooth-airfoil
baseline and all three Lockerby packets remain separate future work.
