#ifndef __DependencyGraph_h__
#define __DependencyGraph_h__

#include "Node.h"
#include "Visitor.h"

#include <string>
#include <vector>
#include <list>
#include <map>

class DependencyGraph {
public:
    void addNode(std::string nodeName);
    void addEdge(std::string nameFrom, std::string nameTo);
    void traverse(Visitor &visitor);
private:
    int numReady = 0;
    std::map<std::string, Node::ptr_t> nodes;
    std::list<Node::ptr_t> readyNodes;
private:
    Node::ptr_t getNode(std::string name);
    void reset();
    void step();
};

#endif // __DependencyGraph_h__