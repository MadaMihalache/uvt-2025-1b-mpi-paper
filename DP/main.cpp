#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <chrono>
#include <set>
using namespace std;
using Clause = set<int>;
using ClauseSet = vector<Clause>;

stringstream file(R"(
p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
)");

ClauseSet parseDIMACS(istream& in) {
    ClauseSet clauses;
    string line;
    while (getline(in, line)) {
        if (line.empty() || line[0] == 'c') 
            continue;
        if (line[0] == 'p') 
            continue;
        istringstream iss(line);
        int lit;
        Clause clause;
        while (iss >> lit) {
            if (lit == 0) {
                if (!clause.empty()) 
                    clauses.push_back(clause);
                clause.clear();
            } else { 
                clause.insert(lit); 
            }
        }
    }
    return clauses;
}

bool hasEmptyClause(const ClauseSet& clauses) {
    for (const auto& clause : clauses)
        if (clause.empty()) 
            return true;
    return false;
}

bool containsClause(const ClauseSet& clauses, const Clause& target) {
    for (const auto& clause : clauses) {
        if (clause == target) 
            return true;
    }
    return false;
}

set<int> getAllVariables(const ClauseSet& clauses) {
    set<int> vars;
    for (const auto& clause : clauses) {
        for (int lit : clause) 
            vars.insert(abs(lit));
    }
    return vars;
}

ClauseSet eliminateVariable(const ClauseSet& clauses, int var) {
    ClauseSet posClauses, negClauses, keepClauses;
    for (const auto& clause : clauses) {
        if (clause.count(var)) 
            posClauses.push_back(clause);
        else if (clause.count(-var)) 
            negClauses.push_back(clause);
        else 
            keepClauses.push_back(clause);
    }
    ClauseSet newClauses = keepClauses;
    for (const auto& c1 : posClauses) {
        for (const auto& c2 : negClauses) {
            Clause resolvent;
            for (int lit : c1) if (lit != var) 
                resolvent.insert(lit);
            for (int lit : c2) if (lit != -var) 
                resolvent.insert(lit);
            if (!containsClause(newClauses, resolvent)) 
                newClauses.push_back(resolvent);
        }
    }
    return newClauses;
}

bool DavisPutnam(ClauseSet clauses) {
    set<int> vars = getAllVariables(clauses);
    for (int var : vars) {
        clauses = eliminateVariable(clauses, var);
        if (hasEmptyClause(clauses)) {
            return false;
        }
    }
    return true;
}

int main() {
    ClauseSet clauses = parseDIMACS(file);
    bool sat = DavisPutnam(clauses);
    if (sat) cout << "Satisfiable\n";
    else cout << "Unsatisfiable\n";
    return 0;
}