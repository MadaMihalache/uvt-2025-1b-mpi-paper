## 1. What your code does (high-level overview)

This code implements the Resolution Algorithm for propositional logic SAT solving.

**Specifically:**
 - It parses a SAT problem in DIMACS format (standard format for CNF formulas),
 - It applies propositional resolution between clauses,
 - If it eventually derives an empty clause ({}), then the formula is unsatisfiable (i.e., no truth assignment makes it true),
 - If it cannot derive an empty clause, the formula is satisfiable.

**In short:**
 -  If during resolution you find an empty clause ⇒ Unsatisfiable.
 -  Otherwise ⇒ Satisfiable.

## 2. Step-by-step breakdown of the code

### Input parsing

```cpp 
stringstream file(R"( 
p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
)");
```

Simulates reading from a file with 3 clauses:
  - (𝑥1 ∨ 𝑥2)
  - (¬x1 ∨ x3)
  - (¬𝑥2 ∨ ¬𝑥3)
Each line ending in 0 means the end of a clause.

### parseDIMACS function
 
 - Reads the input,
 - Ignores comments (c) and problem line (p),
 - Builds a list of clauses (ClauseSet = vector<unordered_set<int>>).

Example result after parsing:

```cpp
clauses = [
  {1, 2},
  {-1, 3},
  {-2, -3}
]
```

### resolutionSAT function

 - Repeatedly combines two clauses if one contains l and another contains ¬l.
 - Produces the resolvent (clause obtained by combining clauses minus l and ¬l).
 - If the resolvent is the empty set → Formula is UNSATISFIABLE.

Otherwise, it keeps adding new resolvents until no more new clauses can be generated.

### main()

 - Parses the input,
 - Applies resolution,
 - Prints "Satisfiable" or "Unsatisfiable".


## Example inputs

### 1. Satisfiable formula
Input:
```cpp
stringstream file(R"(
p cnf 2 2
1 0
2 0
)");
```
Output: Satisfiable

### 2. Unsatisfiable formula
Input:
```cpp
stringstream file(R"(
p cnf 1 2
1 0
-1 0
)");
```
Output: Unsatisfiable

### 3. More complex and satisfiable
Input:
```cpp
stringstream file(R"(
p cnf 3 3
1 2 0
-1 2 0
-2 3 0
)");
```
Means:
 - (x1 V x2)
 - (¬x1 V x2)
 - (¬x2 V x3)
Output: Satisfiable

### 2. More complex and unsatisfiable
Input:
```cpp
stringstream file(R"(
p cnf 2 3
1 0
2 0
-1 -2 0
)");

```
Output: Unsatisfiable