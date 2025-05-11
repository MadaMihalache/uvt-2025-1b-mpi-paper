#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
using namespace std;

stringstream file(R"(
p cnf 3 3
1 2 0
-1 3 0
-2 -3 0
)");

using Clause = unordered_set<int>;
using ClauseSet = vector<Clause>;

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
            } else { clause.insert(lit); }
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

ClauseSet resolutionSAT(ClauseSet clauses) {
    ClauseSet newClauses;
    while (true) {
        newClauses.clear();
        for (size_t i = 0; i < clauses.size(); ++i) {
            for (size_t j = i + 1; j < clauses.size(); ++j) {
                for (int lit : clauses[i]) {
                    if (clauses[j].count(-lit)) {
                        Clause resolvent;
                        for (int l1 : clauses[i])
                            if (l1 != lit) 
                                resolvent.insert(l1);
                        for (int l2 : clauses[j])
                            if (l2 != -lit) 
                                resolvent.insert(l2);
                        if (!containsClause(clauses, resolvent) && !containsClause(newClauses, resolvent)) {
                            newClauses.push_back(resolvent);
                        }
                        if (resolvent.empty()) {
                            clauses.push_back(resolvent);
                            return clauses;
                        }
                    }
                }
            }
        }
        if (newClauses.empty()) 
            break;
        for (const auto& c : newClauses) 
            clauses.push_back(c);
    }
    return clauses;
}

int main() {
    ClauseSet clauses = parseDIMACS(file);
    ClauseSet final = resolutionSAT(clauses);
    if (hasEmptyClause(final)) { 
        cout << "Unsatisfiable\n";
    } else { 
        cout << "Satisfiable\n"; 
    }
    return 0;
}