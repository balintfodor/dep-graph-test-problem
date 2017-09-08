#include <iostream>
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <regex>

using namespace std;

class Node {
private:
    int numInputs = 0;
    int numInputsReady = 0;
    bool ready = true;
    string name;
    list<shared_ptr<Node>> outputs;
public:
    Node(string name): name(name) {}
    void addInput()
    {
        ++numInputs; 
        ready = false;
    }
    void addOutput(shared_ptr<Node> &node)
    {
        outputs.push_back(node);
    }
    bool isReady() const
    {
        return ready;
    }
    void notifyReadyInput()
    {
        if (++numInputsReady == numInputs) {
            ready = true;
        }
    }
    string getName() const
    {
        return name;
    }
    const list<shared_ptr<Node>>& getOutputs() const
    {
        return outputs;
    }
};

class NodeContainer {
private:
    map<string, shared_ptr<Node>> nodes;
    shared_ptr<Node> getNode(string name)
    {
        return nodes.emplace(name, make_shared<Node>(name)).first->second;
    }
public:
    void addEdge(string nameFrom, string nameTo)
    {
        shared_ptr<Node> u = getNode(nameFrom);
        shared_ptr<Node> v = getNode(nameTo);
        u->addOutput(v);
        v->addInput();
    }
    void print()
    {
        for (const auto &node : nodes) {
            cout << node.second->getName() << " ->";
            for (const auto &out : node.second->getOutputs()) {
               cout << " " << out->getName();
            }
            cout << endl;
        }
    }
};

NodeContainer parseFile(string filename)
{
    ifstream inFile(filename);
    string line;
    regex lineRegex("([_[:alnum:]]+)[[:space:]]*:(.*)");
    regex tokenRegex("[_[:alnum:]]+");
    smatch lineMatch;
    NodeContainer container;

    while (getline(inFile, line)) {
        string nodeName;
        if (regex_match(line, lineMatch, lineRegex)) {
            if (lineMatch.size() > 1) {
                nodeName = lineMatch[1].str();
            } else {
                // TODO: parse error
            }
            if (lineMatch.size() > 2) {
                string s = lineMatch[2].str();
                auto itBegin = sregex_iterator(s.begin(), s.end(), tokenRegex);
                auto itEnd = sregex_iterator();
                for (auto it = itBegin; it != itEnd; ++it) {
                    container.addEdge(it->str(), nodeName);
                }
            } else {
                // TODO: parse error?
            }
        }
    }
    return container;
}

int main(int argc, char * argv[])
{
    NodeContainer nc = parseFile("test.txt");
    nc.print();
    return 0;
}