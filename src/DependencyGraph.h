#ifndef __DependencyGraph_h__
#define __DependencyGraph_h__

#include "Node.h"

#include <string>
#include <list>
#include <map>

class DependencyGraph {
public:
    void addNode(std::string nodeName);
    void addEdge(std::string nameFrom, std::string nameTo);
private:
    std::map<std::string, Node::ptr_t> nodes;
    std::list<Node::ptr_t> readyNodes;
    int numReady = 0;
private:
    Node::ptr_t getNode(std::string name);
    // void print();
    void initialize();
    bool isReady() const;
    void step();
    std::list<std::list<Node::ptr_t>> getParallelNodes();
public:
    void run();
    // void draw();
};

#endif // __DependencyGraph_h__