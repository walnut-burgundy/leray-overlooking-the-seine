# Leray bibliography continuation: cascades, generalized flows, and variational existence

Research date: 2026-10-12. **12 new source records, L164–L175; 22 located citation links and 2 explicitly editorial comparisons.** This follows all six leads left at the end of [the stochastic-Lagrangian continuation](stochastic-lagrangian-spider-continuation.md), then selected descendants. It is not an exhaustive recursive crawl.

Inspection: **7 selected full-text inspections, 3 own-abstract inspections, 1 institutional reproduction of the original abstract, 1 metadata/partial-abstract record.** The [relationship register](../bibliography/cascades-generalized-flows-edges.json) preserves evidence and versions. No simulations, independent proof verification or FP/AICI acceptance occurred in this research pass. [walnut-burgundy/leray-overlooking-the-seine PR #4, “Continue Arnold–Khesin bibliography: geometric numerics, smooth reconnection, and local-to-global methods”](https://github.com/walnut-burgundy/leray-overlooking-the-seine/pull/4) was subsequently merged on 2026-10-12 at fc469475943a13b678757b434c20d053012c19a7. That merge does not establish numerical-benchmark or FP/AICI acceptance.

## Findings

### Generalized flows contain more than two density pictures

Brenier's relaxed least-action problem replaces a single deterministic particle map with a probability measure Q on complete paths γ. In Benamou–Carlier–Nenna's formulation, let eₜ(γ)=γ(t), let m be normalized volume, and let π₀,T specify the joint distribution of starting and finishing positions. Then

    (eₜ)₊Q = m           for every time t,
    (e₀,eT)₊Q = π₀,T,
    minimize  𝔼Q[½ ∫₀ᵀ |γ̇(t)|² dt].

Here ₊ means pushforward of a measure. The endpoint coupling records which starting locations connect to which finishing locations. Merely giving uniform density at both endpoints discards that association. This observation is a deduction from L172 equations (1.3)–(1.6).

Time discretization yields multi-marginal optimal transport. Entropy regularization introduces strict convexity and a Sinkhorn algorithm. The finite-entropy constraint on the endpoint coupling matters: L172 §3 excludes an exact deterministic endpoint coupling from its unmodified finite-entropy formulation and discusses penalization as a workaround. The paper compares its method with Brownian-reference entropic interpolation on the torus. None of this identifies an arbitrary numerical entropy parameter with physical viscosity or converts endpoint reconstruction into a Navier–Stokes initial-value solver.

**Uniqueness requires care.** L171's preprint conclusion uses an unrestricted uniqueness phrase. L172 §2 explicitly states that the unregularized problems need not have unique solutions. Existence, uniqueness under additional hypotheses, and uniqueness after entropy regularization are distinct claims. This is an editorial comparison, not a formal correction published by either author group.

L171 also reports artificial statistical behavior when its reconstruction interval exceeds the relevant turnover-time threshold. Its successful short-interval examples are numerical reconstructions, not a general theorem identifying long-time physical motion with an endpoint action minimizer.

### A variational formulation can construct a weak solution, rather than assume one

Following Gomes reaches Ortiz–Schmidt–Stefanelli, L175. For an unforced three-dimensional fluid in a bounded container with homogeneous Dirichlet boundary conditions, their stabilized, exponentially time-weighted functionals admit minimizers. Theorem 3.2, with stabilization σ > 1/8, obtains a subsequential limit satisfying Navier–Stokes and an energy inequality: a Leray–Hopf weak solution.

This goes beyond showing that already-smooth solutions are stationary points of an action, as in the smooth critical-point formulations discussed alongside L168/L173. It does not prove uniqueness or global smoothness of the three-dimensional weak limit, or demonstrate an efficient discretized optimizer. The unstabilized σ=0 convergence question is left open in the inspected version.

### A branching tree can explode without that being a velocity-blowup certificate

Le Jan–Sznitman's approach represents a Fourier-space nonlinear integral equation using branching trees. L170 incorporates explosion into a minimal-cascade construction and relates it to Picard iteration. Its application proving finite-time blowup and nonuniqueness concerns the **Montgomery–Smith toy equation**. The Navier–Stokes vector product retains incompressibility-related cancellations that the comparison does not preserve.

For a future implementation, distinguish tree depth, probability of explosion, integrability of the vector-valued evaluation, and norms of the reconstructed velocity. These are proposed diagnostics, not a tested algorithm.

### Reset counts depend on the auxiliary representation

Cartes–Bustamante–Brachet, L164, introduces a time-dimensioned parameter τ in generalized Weber–Clebsch equations. Its Taylor–Green calculation at Reynolds number 800 reports **29 resets at τ=0 and 13 at τ=1**, between t=0 and t=12. These are the paper's Table I numbers, not new computations. PDF pages 6–7, including Figure 7, Table I and Appendix A, were visually inspected.

The physical equations remain Navier–Stokes while the auxiliary description changes. Reset count alone is therefore not an invariant measure of physical singularity or reconnection. The authors also report high-wavenumber errors; fewer resets alone do not certify accuracy. Appendix A distinguishes the minimum-norm equation (A10) from the simpler practical choice (A11).

### Curves, surfaces and three-dimensional motion interact explicitly

Eyink, L169 Proposition II.2, expresses magnetic flux through a present surface as an expectation of initial fluxes through stochastic preimage surfaces. For general magnetic Prandtl number the momentum equation must still be supplied separately. The stronger pair of stochastic conservation laws in Proposition II.1 assumes ν=λ, with the stated smoothness and domain conditions.

This supplies a concrete connection between loop integrals, surface fluxes and three-dimensional velocity fields. A sheaf organization of compatible observations is a possible additional construction, not a theorem or solver established by these papers. L174 follows magnetic flux into rough-flow limits and dynamo calculations; its finite-resistivity identities and turbulent-limit arguments must remain distinct.

### Probability has different roles in these papers

Chorin's random vorticity displacements (L165), Fourier branching trees (L166/L170), probability measures on complete paths (L167/L172), stochastic transported surfaces (L169/L174), smooth stochastic-control variations (L168), and minimization over whole velocity histories (L175) are different constructions. Their data, constraints and errors should not be merged into one generic stochastic solver.

## Source register

**F:** selected scientific full-text sections, not a complete proof audit. **A:** own abstract and bibliographic record. **A-mirror:** original abstract reproduced by an identified scholarly archive. **M:** metadata/partial abstract only. Reference numbers refer to the linked version.

### L164 — Generalized Eulerian-Lagrangian description of Navier-Stokes dynamics

Carlos Cartes, Miguel D. Bustamante, Marc E. Brachet. *Physics of Fluids* 19, 077101 (2007). DOI `10.1063/1.2748447`.

[Author-hosted PDF](https://www.phys.ens.psl.eu/~brachet/files/Publications_%26_Reprints_files/PhysFluids_19_077101.pdf)

**F:** abstract, introduction, conclusion, Appendix A and references; pages 6–7 visually checked. L156 [4] leads here. Its [2] and [3] cite L154 and L152. Moore–Penrose generalized potentials; τ→0 recovers the earlier formulation with the stated gauge choice. Reset statistics and numerical-error qualifications are above.

### L165 — Numerical study of slightly viscous flow

Alexandre Joel Chorin. *Journal of Fluid Mechanics* 57(4), 785–796 (1973). DOI `10.1017/S0022112073002016`.

[Publisher abstract](https://www.cambridge.org/core/journals/journal-of-fluid-mechanics/article/numerical-study-of-slightly-viscous-flow/4E4FE6AE32F826FFFD6F46E3E86F330A)

**A:** own abstract and displayed references. L157 [6] and L159 [4]. Random numbers approximate vorticity generation and dispersal in a two-dimensional viscous-flow method, illustrated with a cylinder. Journal year 1973; online-publication date 2006. No convergence theorem inferred from the abstract.

### L166 — Stochastic cascades and 3-dimensional Navier–Stokes equations

Yves Le Jan, Alain-Sol Sznitman. *Probability Theory and Related Fields* 109, 343–366 (1997). DOI `10.1007/s004400050135`.

[Publisher summary](https://link.springer.com/article/10.1007/s004400050135)

**A:** original summary and metadata. L157 [20] and L158 [26]. Branching and composition along trees represent a nonlinear Fourier-space integral equation. The summary's existence and uniqueness results concern specified classes, not arbitrary data. Original proofs were not retrieved; L170 gives an inspected later treatment.

### L167 — The least action principle and the related concept of generalized flows for incompressible perfect fluids

Yann Brenier. *Journal of the American Mathematical Society* 2(2), 225–255 (1989). DOI `10.1090/S0894-0347-1989-0969419-8`.

[AMS-derived institutional record](https://geodesic.mathdoc.fr/articles/10.1090/S0894-0347-1989-0969419-8/)

**A-mirror:** this record explicitly identifies AMS as its source. Original PDF retrieval failed. L161 [14]. Probability measures on whole paths relax the least-action problem. The formulas discussed above were read directly in L172, not attributed to unread original theorems.

### L168 — A Variational Formulation for the Navier-Stokes Equation

Diogo Aguiar Gomes. *Communications in Mathematical Physics* 257, 227–234 (2005). DOI `10.1007/s00220-004-1263-8`.

[Publisher abstract and references](https://link.springer.com/article/10.1007/s00220-004-1263-8)

**A:** own abstract and 16 references. L161 [10]. Smooth solutions enter a stochastic-control critical-point formulation. Its [6], [8], [9] cite L165, L155, L154. Stationarity does not imply global minimality or supply an existence theorem; compare L175.

### L169 — Stochastic Line-Motion and Stochastic Conservation Laws for Non-Ideal Hydromagnetic Models. I. Incompressible Fluids and Isotropic Transport Coefficients

Gregory L. Eyink. arXiv:0812.0153v1 (2008).

[Versioned full text](https://arxiv.org/html/0812.0153v1)

**F:** introduction, Propositions II.1–II.2, discussion and references. L158 [17]. Its [9] and [14] cite L157 and L161. Preserve the unit/general magnetic-Prandtl distinction. Part II was listed as 'in preparation' in this version; subsequent publication is not asserted.

### L170 — On Le Jan-Sznitman's stochastic approach to the Navier-Stokes equations

Radu Dascaliuc, Tuan N. Pham, Enrique Thomann. Inspected arXiv:1910.05500v7 (2021; first submitted 2019). Publisher-indexed journal locator: *Transactions of the American Mathematical Society* 377(4), 2335–2365 (2024).

[Inspected preprint](https://arxiv.org/html/1910.05500v7) · [Publisher PDF locator](https://www.ams.org/journals/tran/2024-377-04/S0002-9947-2024-08974-2/S0002-9947-2024-08974-2.pdf)

**F:** introduction, cascade definitions, minimal-solution discussion and bibliography. **Reference numbers are v7's, not the published edition's.** Its [19] cites L166, [16] cites L022, and [8]–[9] lead to the two Yule-cascade papers. The journal DOI was not independently resolved and is deliberately omitted; the publisher URL suffix is not being converted into a guessed DOI.

### L171 — Turbulence of generalised flows in two dimensions

Simon Thalabard, Jérémie Bec. *Journal of Fluid Mechanics* 883, A49 (2020). DOI `10.1017/jfm.2019.892`. Inspected arXiv:1812.02167v2 (2019).

[Full text](https://arxiv.org/html/1812.02167v2) · [Publisher](https://www.cambridge.org/core/journals/journal-of-fluid-mechanics/article/turbulence-of-generalised-flows-in-two-dimensions/4524DDA60B8FF4C1397B445F14BB822A)

**F:** formulation, introductory interpretation, conclusion and named bibliography entries. Published metadata checked separately. Brenier (1989) and Benamou–Carlier–Nenna (2017) locate L167/L172. No figure panels independently analyzed. Retain the long-interval and uniqueness qualifications above.

### L172 — Generalized incompressible flows, multi-marginal transport and Sinkhorn algorithm

Jean-David Benamou, Guillaume Carlier, Luca Nenna. Inspected arXiv:1710.08234v2 (2018; first submitted 2017).

[Full text](https://arxiv.org/html/1710.08234v2)

**F:** §§1–5 formulations, entropy constraints, algorithm and references. Its [6] cites L167; [1] is the entropic-interpolation lead. No unverified journal metadata assigned. Numerical figures were not audited. Exact endpoint constraints and finite-entropy conditions must be retained when translating the optimization into code.

### L173 — On a variational principle for the Navier-Stokes equation

Diogo Aguiar Gomes. In *Mathematical Analysis of Random Phenomena*, World Scientific (2007), pp. 93–100. DOI `10.1142/9789812770547_0008`.

[Publisher chapter](https://www.worldscientific.com/doi/abs/10.1142/9789812770547_0008)

**M:** publisher-indexed metadata and partial abstract; full chapter access failed. L175 [25] confirms the entry and discusses it alongside L168. A publisher snippet mentions clarifying boundary conditions, but the exact conditions were not inspected. No theorem-level claim is based on that snippet.

### L174 — Stochastic flux freezing and magnetic dynamo

Gregory L. Eyink. *Physical Review E* 83, 056405 (2011). DOI `10.1103/PhysRevE.83.056405`. Inspected arXiv:1008.4959v1 (2010).

[Preprint](https://arxiv.org/html/1008.4959v1) · [Publisher](https://link.aps.org/doi/10.1103/PhysRevE.83.056405)

**F:** abstract, introductory scientific discussion, selected appendix material and references; not a full proof or numerical audit. Publisher metadata checked separately. A regenerated HTML date is not the publication year. Its link to L169 is explicitly editorial, not a verified numbered citation in this pass.

### L175 — A variational approach to Navier-Stokes

Michael Ortiz, Bernd Schmidt, Ulisse Stefanelli. Inspected arXiv:1802.06606v2 (2018).

[Full text](https://arxiv.org/html/1802.06606v2)

**F:** introduction, admissible spaces, Theorem 3.2 and references. Its [24]–[25] cite L168/L173; [22] leads to Gigli–Mosconi. Stabilization, boundary conditions and the weak-limit conclusion are stated above. No optimizer implemented or run.

## Remaining bibliography frontier

These are located leads, not additional inspected-paper counts:

- Goodman, *Convergence of the random vortex method* (1987), and Long, *Convergence of the random vortex method in two dimensions* (1988): L157 [12], [21]. Inspect the precise convergence assumptions.
- Dascaliuc–Pham–Thomann–Waymire, *Doubly Stochastic Yule Cascades*, Parts I and II: arXiv:2103.06912 and 2107.13182, L170 v7 [8], [9]; also *Majorizing kernels and stochastic cascades* (2003), L170 [2].
- Arnaudon–Cruzeiro–Léonard–Zambrini, *An entropic interpolation problem for incompressible viscid fluids*, arXiv:1704.02126: L172 [1]. Determine the exact velocity and pressure equations before identifying the entropy minimizer with viscous flow.
- Gigli–Mosconi, *A variational approach to the Navier–Stokes equations* (2012): L175 [22]. Compare time-stepping with whole-history minimization.
- Recover original L167 and full L173 before upgrading their inspection labels. Follow magnetic-line transport separately from ordinary hydrodynamic vortex reconnection.

## Integration boundaries

All six previous leads now have records: Cartes 2007 → L164; Chorin 1973 → L165; Le Jan–Sznitman 1997 → L166; Brenier 1989 → L167; Gomes 2005 → L168; Eyink 0812.0153 → L169. Following a lead does not guarantee full-text access.

Inherited OpenAI-manuscript claims were not re-audited. Parallel Lockerby, CFD-solver, contact-topology and sheaf-implementation files were not changed. The graph defines inherited anchors and points from citing source to cited source unless explicitly marked editorial. This continuation makes no claim to have validated physical simulations or established a new regularity theorem.
