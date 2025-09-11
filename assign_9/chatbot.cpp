#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>
using namespace std;

// Convert to lowercase
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Load knowledge base from file
unordered_map<string, string> loadKnowledgeBase(const string& filename) {
    unordered_map<string, string> kb;
    ifstream file(filename);
    string q, a;

    while (getline(file, q) && getline(file, a)) {
        kb[toLowerCase(q)] = a;
    }
    file.close();
    return kb;
}

// Save knowledge base to file
void saveKnowledgeBase(const unordered_map<string, string>& kb, const string& filename) {
    ofstream file(filename);
    for (auto &entry : kb) {
        file << entry.first << "\n" << entry.second << "\n";
    }
    file.close();
}

int main() {
    string filename = "knowledge.txt";
    unordered_map<string, string> knowledgeBase = loadKnowledgeBase(filename);

    cout << "SmartBot: Hello! I am your assistant. Type 'exit' to quit.\n";

    string userInput;
    while (true) {
        cout << "\nYou: ";
        getline(cin, userInput);

        if (toLowerCase(userInput) == "exit") {
            cout << "SmartBot: Goodbye!\n";
            break;
        }

        string lowerInput = toLowerCase(userInput);

        // Check knowledge base
        if (knowledgeBase.find(lowerInput) != knowledgeBase.end()) {
            cout << "SmartBot: " << knowledgeBase[lowerInput] << endl;
        } else {
            cout << "SmartBot: I dont know the answer. Can you teach me? (yes/no)\n";
            string teach;
            getline(cin, teach);

            if (toLowerCase(teach) == "yes") {
                cout << "Please provide the correct answer:\n";
                string newAnswer;
                getline(cin, newAnswer);

                // Save new Q&A
                knowledgeBase[lowerInput] = newAnswer;
                saveKnowledgeBase(knowledgeBase, filename);

                cout << "SmartBot: Thank you! I will remember this.\n";
            } else {
                cout << "SmartBot: Okay, maybe next time.\n";
            }
        }
    }
    return 0;
}
