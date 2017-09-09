#ifndef _GraphIO_h_
#define _GraphIO_h_

#include <string>
#include <sstream>

#include "DependencyGraph.h"

class GraphIO {
public:
    static DependencyGraph fromTextFile(std::string filename);
    static void toDotFile(const DependencyGraph& graph, std::string filename);
    static void toSVG(const DependencyGraph& graph, std::string filename);
};

#endif // _GraphIO_h_
