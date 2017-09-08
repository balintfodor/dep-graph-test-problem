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
    // TODO: invalidate readyNodes, numReady etc...
}

void DependencyGraph::gatherGraphInfo()
{
    reset();
    traverse();
}

void DependencyGraph::reset()
{
    numReady = 0;
    readyNodes.clear();
    independentGroups.clear();
    valid = true;
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
    readyNodes = nextNodesList;
}

const vector<vector<Node::ptr_t>>& DependencyGraph::getIndependentGroups() const
{
    return independentGroups;
}

const std::map<std::string, Node::ptr_t>& DependencyGraph::getNodes() const
{
    return nodes;
}

bool DependencyGraph::isValid() const
{
    return valid;
}

int DependencyGraph::getMaxGroupSize() const
{
    return maxGroupSize;
}

void DependencyGraph::traverse()
{
    reset();
    auto &ind = independentGroups;
    valid = false;
    for (int i = 0; i < nodes.size(); ++i) {
        ind.emplace_back();
        ind.back().insert(ind.back().begin(), readyNodes.begin(), readyNodes.end());
        
        maxGroupSize = max((int)readyNodes.size(), maxGroupSize);
        
        if (numReady == nodes.size()) {
            valid = true;
            break;
        }

        step();
    }
}