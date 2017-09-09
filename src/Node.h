#ifndef __Node_h__
#define __Node_h__

#include <string>
#include <memory>
#include <list>

// note that we don't need the backward connection to the nodes,
// so the inputs are just counted instead of referenced

class Node {
public:
    typedef std::shared_ptr<Node> ptr_t;
public:
    Node(std::string name);
    std::string getName() const;
    void addInput();
    void addOutput(ptr_t node);
    void notifyInputReady();
    bool isReady() const;
    void reset();
    const std::list<ptr_t>& getOutputs() const;
private:
    std::string name;
    int numInputs = 0;
    int numInputsReady = 0;
    bool ready = true;
    std::list<ptr_t> outputs;
};

#endif // __Node_h__
