#include "GraphIO.h"

#include <fstream>
#include <sstream>
#include <regex>

#include "GraphSVG.h"

using namespace std;

DependencyGraph GraphIO::fromTextFile(string filename)
{
    // TODO: handle 'file doesnt exist'
    ifstream inFile(filename);
    string line;
    regex lineRegex("([^:[:space:]]+)[[:space:]]*:(.*)");
    regex tokenRegex("[^:[:space:]]+");
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
void GraphIO::toDotFile(const DependencyGraph& graph, string filename)
{
    ofstream outFile(filename);
    outFile << "digraph G {" << endl;

    graph.traverse([&outFile](const Node::ptr_t &node, int level, int which)
    {
        outFile << "subgraph cluster_" << level << " { \"" << node->getName() << "\";}" << endl;
    });

    for (const auto &node : graph) {
        for (const auto &out : node.second->getOutputs()) {
            outFile << "\"" << node.first << "\" -> \"" << out->getName() << "\";" << endl;
        }
    }

    outFile << "}" << endl;
}

void GraphIO::toSVG(const DependencyGraph& graph, string filename)
{
    GraphSVG svg;
    vector<int> groupSizes;
    static const vector<string> colorLut = {"#2E95A3", "#50B8B4", "#C6FFFA", "#E2FFA8", "#D6E055"};
    
    graph.traverse([&groupSizes](const Node::ptr_t &node, int level, int which)
    {
        groupSizes.resize(max(groupSizes.size(), (size_t)level + 1));
        groupSizes[level]++;
    });

    int maxN = *max_element(groupSizes.begin(), groupSizes.end());

    graph.traverse([&svg, &groupSizes, maxN](const Node::ptr_t &node, int level, int which)
    {
        int n = groupSizes[level];
        //(which - n / 2.0) * 50. + maxN / 2.0 * 50;
        //50.0 * which - (n + maxN) / 25.0;
        double d = 100.;
        double x = d * (which - 0.5 * (n - maxN));
        double y = level * d;
        int r = 45;
        string color = colorLut[level % colorLut.size()];
        svg.addNode(node->getName(), (int)x, (int)y, r, color);
    });

    for (const auto &node : graph) {
        for (const auto &out : node.second->getOutputs()) {
            svg.addEdge(node.first, out->getName());
        }
    }

    ofstream outFile(filename);
    outFile << svg.getContent();
}
