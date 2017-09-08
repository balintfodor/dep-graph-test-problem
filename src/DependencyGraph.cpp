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

// void DependencyGraph::print()
// {
//     for (const auto &node : nodes) {
//         cout << node.second->getName() << " ->";
//         for (const auto &out : node.second->getOutputs()) {
//            cout << " " << out->getName();
//         }
//         cout << endl;
//     }
// }

void DependencyGraph::initialize()
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

bool DependencyGraph::isReady() const
{
    return numReady == nodes.size();
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

void DependencyGraph::run()
{
    for (int i = 0; i < nodes.size(); ++i) {
        step();
        if (isReady()) {
            return;
        }
    }
}

list<list<Node::ptr_t>> DependencyGraph::getParallelNodes()
{
    initialize();
    list<list<Node::ptr_t>> parallel;
    for (int i = 0; i < nodes.size(); ++i) {
        parallel.emplace_back();
        parallel.back().insert(parallel.back().begin(), readyNodes.begin(), readyNodes.end());
        step();
        if (isReady()) {
            return parallel;
        }
    }
    return parallel;
}

// void DependencyGraph::draw()
// {
//     auto p = getParallelNodes();
//     int n = max_element(p.begin(), p.end(), [](const decltype(p)::value_type &a, const decltype(p)::value_type &b)
//         {
//             return a.size() < b.size();
//         })->size();
//     cout << R"svg(<svg xmlns="http://www.w3.org/2000/svg" height="64" width="64">)svg" << endl;
//     for (int level = 0; level < p.size(); ++level) {
//         for (int i = 0; i < p[level].size(); ++i) {

//         }
//     }
//     cout << R"svg(</svg>)svg" << endl;
// }
