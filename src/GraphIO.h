#ifndef _GraphIO_h_
#define _GraphIO_h_

#include <string>

#include "DependencyGraph.h"

class GraphIO {
public:
    static DependencyGraph fromTextFile(std::string filename);
    static void toSVG(const DependencyGraph& graph, std::string filename, 
        int width=400, int height=400);
};

#endif // _GraphIO_h_
