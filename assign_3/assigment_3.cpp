#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <algorithm>

struct Person {
    std::string name;
    std::string gender;  // "male" or "female"
    std::vector<Person*> parents;
    std::vector<Person*> children;

    Person(const std::string& n, const std::string& g) : name(n), gender(g) {}
};

class FamilyTree {
private:
    std::unordered_map<std::string, Person*> people;

public:
    ~FamilyTree() {
        for (auto& pair : people) {
            delete pair.second;
        }
    }

    void addPerson(const std::string& name, const std::string& gender) {
        if (people.find(name) == people.end()) {
            people[name] = new Person(name, gender);
        }
    }

    void addParentChild(const std::string& parentName, const std::string& parentGender,
                        const std::string& childName, const std::string& childGender) {
        addPerson(parentName, parentGender);
        addPerson(childName, childGender);
        Person* parent = people[parentName];
        Person* child = people[childName];
        parent->children.push_back(child);
        child->parents.push_back(parent);
    }

    std::vector<std::string> getParents(const std::string& name) {
        std::vector<std::string> result;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                result.push_back(p->name);
            }
        }
        return result;
    }

    std::vector<std::string> getFather(const std::string& name) {
        std::vector<std::string> fathers;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                if (p->gender == "male") {
                    fathers.push_back(p->name);
                }
            }
        }
        return fathers;
    }

    std::vector<std::string> getGrandmother(const std::string& name) {
        std::unordered_set<std::string> grandmothers;
        auto parents = getParents(name);
        for (const auto& parent : parents) {
            auto gps = getParents(parent);
            for (const auto& gp : gps) {
                if (people[gp]->gender == "female") {
                    grandmothers.insert(gp);
                }
            }
        }
        return {grandmothers.begin(), grandmothers.end()};
    }

    // Parse query: "relationship of person"
    bool parseQuery(const std::string& query, std::string& relationship, std::string& person) {
        std::regex pattern(R"((\w+)\s+of\s+(\w+))");
        std::smatch matches;
        std::string lowerQuery = query;
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
        if (std::regex_match(lowerQuery, matches, pattern)) {
            relationship = matches[1].str();
            person = matches[2].str();
            // Capitalize person name
            if (!person.empty()) person[0] = std::toupper(person[0]);
            return true;
        }
        return false;
    }

    std::string queryRelationship(const std::string& query) {
        std::string relationship, person;
        if (!parseQuery(query, relationship, person)) {
            return "Invalid query format. Use 'relationship of person' e.g., 'father of kate'";
        }

        std::vector<std::string> results;
        if (relationship == "father") {
            results = getFather(person);
        } else if (relationship == "grandmother") {
            results = getGrandmother(person);
        } else {
            return "Unsupported relationship: " + relationship;
        }

        if (results.empty()) {
            results.push_back("No " + relationship + " found");
        }

        // Format as slide
        std::string resultStr = "\n";
       
        resultStr += "            " + relationship.substr(0,1) + relationship.substr(1) + " of " + person + "\n";  // Capitalize relationship
        resultStr += "--------------------------------------------------\n";
        for (const auto& res : results) {
            resultStr += "| " + res + std::string(50 - res.length(), ' ') + "|\n";  // Pad for alignment
        }
        resultStr += "--------------------------------------------------\n";
        return resultStr;
    }
};

int main() {
    FamilyTree tree;

    // Add sample family tree
    tree.addParentChild("John", "male", "Bob", "male");
    tree.addParentChild("Mary", "female", "Bob", "male");
    tree.addParentChild("Bob", "male", "Kate", "female");
    tree.addParentChild("Alice", "female", "Kate", "female");
    tree.addParentChild("Bob", "male", "Frank", "male");
    tree.addParentChild("Alice", "female", "Frank", "male");

    // Get user input
    std::string query;
    std::cout << "Enter query (e.g., 'father of kate'): ";
    std::getline(std::cin, query);

    std::cout << tree.queryRelationship(query) << std::endl;

    return 0;
}