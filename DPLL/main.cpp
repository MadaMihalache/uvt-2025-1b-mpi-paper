#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void printClauses(vector<vector<int>> clauses) {
    for (const auto& clause : clauses) {
        for (int x : clause) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

vector<vector<int>> copyClauses(const vector<vector<int>>& clauses) {
    return clauses;
}

bool checkConsistency(const vector<vector<int>>& clauses) {
    return clauses.empty();
}

bool containsEmptyClause(const vector<vector<int>>& clauses) {
    for (const auto& clause : clauses)
        if (clause.empty())
            return true;
    return false;
}

int findLiteralInClause(int literal, const vector<int>& clause, bool &literalPolarity) {
    for (int i = 0; i < clause.size(); i++) {
        if (clause[i] == literal) {
            literalPolarity = true;
            return i;
        } else if (clause[i] == -literal) {
            literalPolarity = false;
            return i;
        }
    }
    return -1;
}

void updateClauses(int literal, bool literalAssignment, vector<vector<int>> &clauses) {
    for (int i = 0; i < clauses.size(); i++) {
        bool literalPolarity = false;
        int index = findLiteralInClause(literal, clauses[i], literalPolarity);
        if (index != -1) {
            if ((literalPolarity && literalAssignment) || (!literalPolarity && !literalAssignment)) {
                clauses.erase(clauses.begin() + i);
                i--;
            } else { 
                clauses[i].erase(clauses[i].begin() + index); 
            }
        }
    }
}

int checkUnitClause(const vector<int>& clause) {
    return clause.size() == 1 ? clause[0] : 0;
}

void unitPropagate(int literal, bool literalAssignment, vector<vector<int>> &clauses) {
    updateClauses(literal, literalAssignment, clauses);
}

int checkPureLiteral(int literal, const vector<vector<int>>& clauses) {
    int pos = 0, neg = 0;
    for (const auto& clause : clauses) {
        bool literalPolarity = false;
        int index = findLiteralInClause(literal, clause, literalPolarity);
        if (index != -1) {
            if (literalPolarity) pos++;
            else neg++;
        }
    }
    if (pos == 0 && neg == 0) 
        return 0;
    else if (pos == 0) 
        return -1;
    else if (neg == 0) 
        return 1;
    return 0;
}

void pureLiteralAssign(int literal, bool literalAssignment, vector<vector<int>> &clauses) {
    updateClauses(literal, literalAssignment, clauses);
}

int chooseLiteral(int n_vars, const vector<int> &usedLiterals) {
    for (int i = 1; i <= n_vars; i++) {
        if (find(usedLiterals.begin(), usedLiterals.end(), i) == usedLiterals.end())
            return i;
    }
    return -1;
}

bool SAT(vector<vector<int>> clauses, int n_vars, vector<int> &usedLiterals) {
    if (checkConsistency(clauses)) return true;
    if (containsEmptyClause(clauses)) return false;
    for (int i = 0; i < clauses.size(); i++){
        int unitLiteral = checkUnitClause(clauses[i]);
        if (unitLiteral != 0) {
            unitPropagate(std::abs(unitLiteral), unitLiteral > 0, clauses);
            usedLiterals.push_back(unitLiteral);
        }
    }
    for (int i = 1; i <= n_vars; i++) {
        int polarity = checkPureLiteral(i, clauses);
        if (polarity != 0) {
            pureLiteralAssign(i, polarity > 0, clauses);
            usedLiterals.push_back(polarity > 0 ? i : -i);
        }
    }
    vector<vector<int>> clausesCopy = copyClauses(clauses);
    vector<int> usedLiteralsCopy = usedLiterals;
    int chosenLiteral = chooseLiteral(n_vars, usedLiterals);
    if (chosenLiteral == -1) 
        return false;
    usedLiterals.push_back(chosenLiteral);
    updateClauses(chosenLiteral, true, clauses);
    if (SAT(clauses, n_vars, usedLiterals)) 
        return true;
    usedLiteralsCopy.push_back(-chosenLiteral);
    updateClauses(chosenLiteral, false, clausesCopy);
    return SAT(clausesCopy, n_vars, usedLiteralsCopy);
}

void solve(const string& input) {
    istringstream in(input);
    string line;
    int n_vars = 0, n_clauses = 0;
    vector<vector<int>> clauses;
    while (getline(in, line)) {
        if (line.empty() || line[0] == 'c') 
            continue;
        if (line[0] == 'p') {
            istringstream iss(line);
            string tmp;
            iss >> tmp >> tmp >> n_vars >> n_clauses;
        } else {
            istringstream iss(line);
            int lit;
            vector<int> clause;
            while (iss >> lit) {
                if (lit == 0) break;
                clause.push_back(lit);
            }
            if (!clause.empty()) 
                clauses.push_back(clause);
        }
    }
    vector<int> usedLiterals;
    bool sat = SAT(clauses, n_vars, usedLiterals);
    cout << (sat ? "Satisfiable\n" : "Unsatisfiable\n");
}

int main() {
    string dimacs = R"(
    p cnf 3 3
    1 2 0
    -1 3 0
    -2 -3 0
    )";
    solve(dimacs);
    return 0;
}