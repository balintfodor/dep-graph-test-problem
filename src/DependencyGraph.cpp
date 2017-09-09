#include "DependencyGraph.h"

using namespace std;

Node::ptr_t DependencyGraph::getNode(string name)
{
    return nodes.emplace(name, make_shared<Node>(name)).first->second;
}

void DependencyGraph::addNode(string nodeName)
{
    getNode(nodeName);
}

void DependencyGraph::addEdge(string nameFrom, string nameTo)
{
    shared_ptr<Node> u = getNode(nameFrom);
    shared_ptr<Node> v = getNode(nameTo);
    u->addOutput(v);
    v->addInput();
}

void DependencyGraph::reset()
{
    numReady = 0;
    readyNodes.clear();
    for (auto &node : nodes) {
        node.second->reset();
        if (node.second->isReady()) {
            ++numReady;
            readyNodes.push_back(node.second);
        }
    }
}

void DependencyGraph::step()
{
    list<Node::ptr_t> nextNodesList;
    for (auto &node : readyNodes) {
        for (auto &out : node->getOutputs()) {
            out->notifyInputReady();
            if (out->isReady()) {
                ++numReady;
                nextNodesList.push_back(out);
            }
        }
    }
    swap(readyNodes, nextNodesList);
}

bool DependencyGraph::traverse(function<void(const Node::ptr_t&, int, int)> func)
{
    reset();
    for (int i = 0; i < nodes.size(); ++i) {
        int cnt = 0;
        for (const Node::ptr_t &node : readyNodes) {
            func(node, i, cnt++);
        }
        if (numReady == nodes.size()) {
            return true;
        }
        step();
    }
    return false;
}

bool DependencyGraph::traverse(Visitor &visitor)
{
    return traverse([&visitor](const Node::ptr_t& a, int b, int c)
        { 
            visitor.accept(a, b, c);
        });
}
