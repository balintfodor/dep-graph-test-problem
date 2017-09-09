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

    graph.traverse([&svg](const Node::ptr_t &node, int level, int which)
    {
        svg.addNode(node->getName(), which * 160 + 100, level * 160 + 100);
    });

    for (const auto &node : graph) {
        for (const auto &out : node.second->getOutputs()) {
            svg.addEdge(node.first, out->getName());
        }
    }

    ofstream outFile(filename);
    outFile << svg.getContent();
}
