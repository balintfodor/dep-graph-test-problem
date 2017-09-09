#ifndef _GraphIO_h_
#define _GraphIO_h_

#include <string>
#include <sstream>

#include "DependencyGraph.h"

class IOError : public std::runtime_error {
public:
    IOError(std::string msg) : std::runtime_error(msg) {}
};

class ParseError : public std::runtime_error {
public:
    ParseError(std::string msg) : std::runtime_error(msg) {}
};

class GraphIO {
public:
    static DependencyGraph fromTextFile(std::string filename);
    static void toDotFile(const DependencyGraph& graph, std::string filename);
    static void toSVG(const DependencyGraph& graph, std::string filename,
        int nodeDistance = 100, int nodeRadius = 45);
};

#endif // _GraphIO_h_
