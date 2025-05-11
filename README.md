# uvt-2025-1b-mpi-paper

## SAT Implementations

This repository contains different C++ implementations of classic SAT solving algorithms:
 - *Resolution Method:* Applies resolution between clauses to detect unsatisfiability.
 - *DP (Davis-Putnam) Algorithm:* Eliminates variables through resolution without branching.
 - *DPLL (Davis-Putnam-Logemann-Loveland) Algorithm:* An improved backtracking search with unit propagation and pure literal elimination.

Each solver reads a propositional logic formula in DIMACS CNF format and determines if it is **satisfiable** or **unsatisfiable**.

These codes demonstrate core techniques used in modern SAT solvers and provide a foundation for further optimization and extension.