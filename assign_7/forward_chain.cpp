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

// Forward chaining function
set<string> forwardChaining(set<string> facts, vector<Rule> rules) {
    bool newFactAdded = true;

    while (newFactAdded) {
        newFactAdded = false;

        for (auto &rule : rules) {
            bool allConditionsMet = true;

            // Check if all conditions of rule are in facts
            for (auto &cond : rule.conditions) {
                if (facts.find(cond) == facts.end()) {
                    allConditionsMet = false;
                    break;
                }
            }

            // If conditions met and conclusion is new, add it
            if (allConditionsMet && facts.find(rule.conclusion) == facts.end()) {
                cout << "Inferred new fact: " << rule.conclusion << endl;
                facts.insert(rule.conclusion);
                newFactAdded = true;
            }
        }
    }

    return facts;
}

int main() {
    // Initial facts (symptoms observed in patient)
    set<string> facts = {"Fever", "Cough", "BodyAche"};

    // Define rules
    vector<Rule> rules = {
        {{"Fever", "Cough"}, "Flu"},
        {{"Flu"}, "RestNeeded"},
        {{"Flu"}, "SeeDoctor"}
    };

    cout << "Initial facts: ";
    for (auto &f : facts) cout << f << " ";
    cout << endl;

    // Run forward chaining
    set<string> inferred = forwardChaining(facts, rules);

    cout << "\nFinal inferred facts: ";
    for (auto &f : inferred) cout << f << " ";
    cout << endl;

    return 0;
}
