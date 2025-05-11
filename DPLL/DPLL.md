## 1. What the code does
 - It solves a Boolean SAT problem, given a CNF formula in DIMACS format.
 - It tries to find an assignment of True/False to variables that makes the whole formula true.
This time, it uses full DPLL features:
 - *Unit propagation*: if a clause has only 1 literal, it must be set accordingly.
 - *Pure literal elimination*: if a literal appears only positive or only negative, it can be assigned directly.
 - *Splitting*: if necessary, guess a literal and try recursively.

## 2. Step-by-step Breakdown of the code

#### solve(string input)
 Parses the DIMACS format string.
 Extracts:
   - n_vars = number of variables.
   - clauses = list of clauses.
Example:
```
p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
```
Means:
 - Variables: x₁, x₂, x₃
 - Clauses:
    - (x1 V x2)
    - (¬x1 V x3)
    - (¬x2 V x3)

#### SAT(clauses, n_vars, usedLiterals)
It does the algorithm explained in the paper at the DPLL subsection.

#### Other helper functions
 - **printClauses** - (Debugging) prints the list of clauses.
 - **copyClauses** - Makes a deep copy of the clauses.
 - **checkConsistency** - Checks if the formula is satisfied (no clauses left).
 - **containsEmptyClause** - Checks if some clause became empty.
 - **findLiteralInClause** - Looks for a literal (positive or negative) in a clause.
 - **updateClauses** - Updates clauses after assigning a literal.
 - **checkUnitClausez** - Checks if a clause is a unit clause.
 - **unitPropagate** - Simplify the formula by unit propagation.
 - **checkPureLiteral** - Checks if a literal is pure (appears only one way).
 - **pureLiteralAssign** - Simplify by pure literal elimination.
 - **chooseLiteral** - Picks the next unassigned literal.

 ## 3. Examples:

 #### 1. 
 Input:
 ```cpp
 p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
```
Output: satisfiable

 #### 2. 
 Input:
 ```cpp
 p cnf 1 2
1 0
-1 0
```
Output: unsatisfiable

#### 3. 
Input:
 ```cpp
p cnf 2 2
1 0
2 0
```
Output: satisfiable

#### 4. 
Input:
 ```cpp
p cnf 3 4
1 0
2 0
-1 -2 3 0
-3 0
```
Output: unsatisfiable

#### 5. 
Input:
 ```cpp
p cnf 3 3
1 0
2 3 0
-2 3 0
```
Output: satisfiable