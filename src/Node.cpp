#include "Node.h"

using namespace std;

Node::Node(string name): name(name)
{}

void Node::addInput()
{
    ++numInputs; 
    ready = false;
}

void Node::addOutput(Node::ptr_t node)
{
    outputs.push_back(node);
}

bool Node::isReady() const
{
    return ready;
}

void Node::notifyInputReady()
{
    if (++numInputsReady == numInputs) {
        ready = true;
    }
}

string Node::getName() const
{
    return name;
}

const list<Node::ptr_t>& Node::getOutputs() const
{
    return outputs;
}

void Node::reset()
{
    numInputsReady = 0;
    ready = numInputs == 0;
}
