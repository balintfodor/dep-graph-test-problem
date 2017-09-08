#include <iostream>
#include <fstream>
#include <regex>
#include "DependencyGraph.h"

using namespace std;

DependencyGraph parseFile(string filename)
{
    ifstream inFile(filename);
    string line;
    regex lineRegex("([_[:alnum:]]+)[[:space:]]*:(.*)");
    regex tokenRegex("[_[:alnum:]]+");
    smatch lineMatch;
    DependencyGraph container;

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
    DependencyGraph nc = parseFile("example/test.txt");
    nc.run();
    return 0;
}
