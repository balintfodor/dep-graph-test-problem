#ifndef __DependencyGraph_h__
#define __DependencyGraph_h__

#include "Node.h"
#include "Visitor.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <stdexcept>

class DependencyGraph {
public:
    typedef std::function<void(const Node::ptr_t&, int, int)> VisitorFunction;
    typedef std::map<std::string, Node::ptr_t> NodeMap;
public:
    void addNode(std::string nodeName);
    void addEdge(std::string nameFrom, std::string nameTo);
    bool traverse(Visitor &visitor);
    bool traverse(VisitorFunction func);
    bool traverse(Visitor &visitor) const;
    bool traverse(VisitorFunction func) const;
    NodeMap::iterator begin() { return nodes.begin(); }
    NodeMap::iterator end() { return nodes.end(); }
    NodeMap::const_iterator begin() const { return nodes.begin(); }
    NodeMap::const_iterator end() const { return nodes.end(); }
private:
    int numReady = 0;
    NodeMap nodes;
    std::list<Node::ptr_t> readyNodes;
private:
    Node::ptr_t getNode(std::string name);
    void reset();
    void step();
};

#endif // __DependencyGraph_h__