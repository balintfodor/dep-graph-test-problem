#include "DependencyGraph.h"

using namespace std;

Node::ptr_t DependencyGraph::getNode(string name)
{
    // retrieves or constructs one
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
    // reseting all the nodes and counters, preparing for a graph traversal
    
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
    // notifying all the nodes subseqent to the currently ready ones
    // then checking and collecting the nodes became ready because of the
    // notification

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

bool DependencyGraph::traverse(VisitorFunction func)
{
    // if this graph is really a DAG, then we need nodes.size() steps at the
    // the worst case to reach every node
    // 
    // so if we can't finish touching all nodes at the end, then there's 
    // something fishy with this DAG graph

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
    // if we reach this, then this is not a DAG, except it is an empty graph
    return nodes.empty();
}

bool DependencyGraph::traverse(Visitor &visitor)
{
    using namespace std::placeholders;
    auto func = bind(&Visitor::accept, &visitor, _1, _2, _3);
    return traverse(func);
}

bool DependencyGraph::traverse(VisitorFunction func) const
{
    DependencyGraph replica(*this);
    return replica.traverse(func);
}

bool DependencyGraph::traverse(Visitor &visitor) const
{
    DependencyGraph replica(*this);
    return replica.traverse(visitor);
}
