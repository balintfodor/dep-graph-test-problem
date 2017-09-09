#ifndef __DependencyGraph_h__
#define __DependencyGraph_h__

#include "Node.h"
#include "Visitor.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>

class DependencyGraph {
public:
    typedef std::function<void(const Node::ptr_t&, int, int)> VisitorFunction;
public:
    void addNode(std::string nodeName);
    void addEdge(std::string nameFrom, std::string nameTo);
    bool traverse(Visitor &visitor);
    bool traverse(VisitorFunction func);
    bool traverse(Visitor &visitor) const;
    bool traverse(VisitorFunction func) const;
public:
    std::map<std::string, Node::ptr_t>::iterator begin() { return nodes.begin(); }
    std::map<std::string, Node::ptr_t>::iterator end() { return nodes.end(); }
    std::map<std::string, Node::ptr_t>::const_iterator begin() const { return nodes.begin(); }
    std::map<std::string, Node::ptr_t>::const_iterator end() const { return nodes.end(); }
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