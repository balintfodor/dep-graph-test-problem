#include <iostream>

#include "GraphIO.h"
#include "DependencyGraph.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc < 2) {
        cerr << "usage: " << argv[0] << " <graph text file>" << endl;
        return -1;
    }
    string filename(argv[1]);
    DependencyGraph graph = GraphIO::fromTextFile(filename);
    
    graph.gatherGraphInfo();

    if (!graph.isValid()) {
        cerr << "this is not a directed acyclic graph" << endl;
        return -2;
    }
    
    auto indNodes = graph.getIndependentGroups();
    for (int level = 0; level < indNodes.size(); ++level) {
        cout << "level " << level << " :";
        for (int i = 0; i < indNodes[level].size(); ++i) {
            cout << " " << indNodes[level][i]->getName();
        }
        cout << endl;
    }

    GraphIO::toSVG(graph, "output.svg");

    return 0;
}
