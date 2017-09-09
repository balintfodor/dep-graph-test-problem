#include <iostream>

#include "GraphIO.h"
#include "GraphSVG.h"
#include "DependencyGraph.h"
#include "IndGroupsVisitor.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc < 2) {
        cerr << "usage: " << argv[0] << " <graph text file>" << endl;
        return -1;
    }

    DependencyGraph graph;
    IndGroupsVisitor visitor;
    string filename(argv[1]);

    try {
        graph = GraphIO::fromTextFile(filename);
    }
    catch (IOError &e) {
        cerr << "IOError: "<< e.what() << endl;
        return -2;
    }
    catch (ParseError &e) {
        cerr << "ParseError: "<< e.what() << endl;
        return -3;
    }

    bool invalid = !graph.traverse(visitor);

    if (invalid) {
        cerr << "this is not a directed acyclic graph" << endl;
        return -4;
    }
    
    auto indNodes = visitor.getIndGroups();
    for (int level = 0; level < indNodes.size(); ++level) {
        cout << "level " << level << " :";
        for (int i = 0; i < indNodes[level].size(); ++i) {
            cout << " " << indNodes[level][i]->getName();
        }
        cout << endl;
    }

    GraphIO::toDotFile(graph, "output.dot");

    try {
        GraphIO::toSVG(graph, "output.svg");
    }
    catch (SVGDrawError &e) {
        cerr << "SVGDrawError: " << e.what() << endl;
    }

    return 0;
}
