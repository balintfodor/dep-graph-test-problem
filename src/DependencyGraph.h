#ifndef __DependencyGraph_h__
#define __DependencyGraph_h__

#include "Node.h"

#include <string>
#include <vector>
#include <list>
#include <map>

class DependencyGraph {
public:
    void addNode(std::string nodeName);
    void addEdge(std::string nameFrom, std::string nameTo);
    void gatherGraphInfo();
    const std::vector<std::vector<Node::ptr_t>>& getIndependentGroups() const;
    const std::map<std::string, Node::ptr_t>& getNodes() const;
    int getMaxGroupSize() const;
    bool isValid() const;
private:
    int numReady = 0;
    bool valid = true;
    int maxGroupSize = 0;
    std::map<std::string, Node::ptr_t> nodes;
    std::list<Node::ptr_t> readyNodes;
    std::vector<std::vector<Node::ptr_t>> independentGroups;
private:
    Node::ptr_t getNode(std::string name);
    void reset();
    void step();
    void traverse();
};

#endif // __DependencyGraph_h__