#ifndef _GraphIO_h_
#define _GraphIO_h_

#include <string>
#include <sstream>

#include "DependencyGraph.h"

class GraphSVG {
public:
    void addNode(std::string name, int x, int y);
    void addEdge(std::string from, std::string to);
    std::string getContent() const;
private:
    std::stringstream body;
    static std::string bodyTag;
    static std::string circleTag;
    static std::string lineTag;
    static std::string textTag;
private:
    std::string subs(std::string templ, std::map<std::string, std::string> dict);
};

class GraphIO {
public:
    static DependencyGraph fromTextFile(std::string filename);
    static void toSVG(const DependencyGraph& graph, std::string filename, 
        int width=400, int height=400);
};

#endif // _GraphIO_h_
