#include "GraphIO.h"

#include <fstream>
#include <regex>
#include <sstream>

using namespace std;

DependencyGraph GraphIO::fromTextFile(string filename)
{
    // TODO: handle 'file doesnt exist'
    ifstream inFile(filename);
    string line;
    regex lineRegex("([_[:alnum:]]+)[[:space:]]*:(.*)");
    regex tokenRegex("[_[:alnum:]]+");
    smatch lineMatch;
    DependencyGraph graph;

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
                    graph.addEdge(it->str(), nodeName);
                }
            } else {
                // TODO: parse error?
            }
        }
    }
    return graph;
}

map<string, pair<int, int>> buildInverseNodeMap(const vector<vector<Node::ptr_t>> &groups)
{
    map<std::string, std::pair<int, int>> result;
    for (int level = 0; level < groups.size(); ++level) {
        
        for (int i = 0; i < groups[level].size(); ++i) {
            result[groups[level][i]->getName()] = make_pair(level, i);
        }
    }
    return result;
}

void GraphIO::toSVG(const DependencyGraph& graph, std::string filename, int width, int height)
{
    int n = graph.getMaxGroupSize();
    const auto &ind = graph.getIndependentGroups();
    int maxLevels = ind.size();

    auto nodeToPos = buildInverseNodeMap(ind);

    stringstream svg;
    svg << "<svg "
        << "xmlns=\"http://www.w3.org/2000/svg\" "
        << "height=\"" << height << "\" "
        << "width=\"" << width << "\" "
        << ">" << endl;
    for (const auto &node : graph.getNodes()) {
        auto pos = nodeToPos[node.second->getName()];
        int y = height / (maxLevels + 2.0) * (pos.first + 1.0);
        int x = width / (n + 2.0) * (pos.second + 1.0);
        svg << "<circle "
            << "cx=\"" << x << "\" "
            << "cy=\"" << y << "\" "
            << "r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"white\" />" << endl;
        svg << "<text "
            << "x=\"" << x << "\" "
            << "y=\"" << y << "\" "
            << "fill=\"black\">" << node.second->getName() << "</text>" << endl;
    }
    svg << "</svg>" << endl;

    ofstream outFile(filename);
    outFile << svg.str();
}
