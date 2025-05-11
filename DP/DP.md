### 1. What this code does
 - This is an implementation of the Davis-Putnam algorithm (not DPLL, only DP) for SAT solving.
 - SAT = Given a set of clauses (in CNF form), can we assign True/False to variables so that every clause is satisfied?

### 2. Step-by-step explanation

#### Input parsing (parseDIMACS function)
 - The code reads a CNF formula in DIMACS format.
 - Each clause is a list of literals (variables or their negations) ending with 0.
 - Literals:
     - Positive integers: variable is True.
     - Negative integers: variable is False.
Example input:

```
p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
```

Means:
 - (x1 V x2)
 - (¬x1 V x3)
 - (¬x2 V ¬x3)

 We parse them into 3 clauses

 #### Clause representation
 - A Clause = set<int> = a set of literals.
 - A ClauseSet = vector<Clause> = a list of clauses.

Using set automatically keeps literals sorted.

#### Helper functions
 - **hasEmptyClause(clauses)** - Checks if there’s an empty clause (which means UNSAT).
 - **containsClause(clauses, target)** - Checks if a clause already exists in the clause set.
 - **getAllVariables(clauses)** - Extracts all distinct variables from the clauses.
 - **eliminateVariable(clauses, var)** - Eliminates a variable by combining clauses that contain var and ¬var, creating new resolvent clauses.

The main algorithm of DP method is explained in the paper.

### Examples:

#### 1. Satisfiable
Input:
```
p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
```

Output : Satisfiable

#### 2. Unsatisfiable
Input:
```
p cnf 1 2
1 0
-1 0
```

Output : Unsatisfiable

Input:
```
p cnf 2 4
1 2 0
-1 0
-2 0
0
```

Output : Unsatisfiable




