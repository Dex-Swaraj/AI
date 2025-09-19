#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

// Rule structure: conditions → conclusion
struct Rule {
    vector<string> conditions;
    string conclusion;
};

// Backward chaining function
bool backwardChaining(const string &goal, const set<string> &facts, const vector<Rule> &rules, set<string> &proven) {
    // If goal is already a known fact
    if (facts.find(goal) != facts.end()) {
        cout << "Fact known: " << goal << endl;
        proven.insert(goal);
        return true;
    }

    // Try to prove goal using rules
    for (auto &rule : rules) {
        if (rule.conclusion == goal) {
            cout << "Checking rule for: " << goal << endl;
            bool allConditionsMet = true;

            // Check all conditions (sub-goals)
            for (auto &cond : rule.conditions) {
                if (proven.find(cond) == proven.end()) { 
                    // Prove condition recursively
                    if (!backwardChaining(cond, facts, rules, proven)) {
                        allConditionsMet = false;
                        break;
                    }
                }
            }

            if (allConditionsMet) {
                cout << "Proved: " << goal << endl;
                proven.insert(goal);
                return true;
            }
        }
    }

    // If no rule or facts prove the goal
    cout << "Could not prove: " << goal << endl;
    return false;
}

int main() {
    // Known facts (symptoms observed)
    set<string> facts = {"Fever", "Cough"};

    // Define rules
    vector<Rule> rules = {
        {{"Fever", "Cough"}, "Flu"},
        {{"Flu"}, "RestNeeded"},
        {{"Flu"}, "SeeDoctor"}
    };

    // Goal: try to prove "SeeDoctor"
    string goal = "SeeDoctor";
    set<string> proven;

    cout << "Trying to prove: " << goal << endl << endl;
    bool result = backwardChaining(goal, facts, rules, proven);

    cout << "\nFinal Result: ";
    if (result) cout << goal << " is TRUE (proven)" << endl;
    else cout << goal << " cannot be proven" << endl;

    return 0;
}
