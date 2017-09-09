#ifndef _IndGroupsVisitor_h_
#define _IndGroupsVisitor_h_

#include <vector>
#include "Visitor.h"

// Independent Groups Visitor
class IndGroupsVisitor : public Visitor {
public:
    typedef std::vector<std::vector<Node::ptr_t>> IndGroups;
    void accept(const Node::ptr_t &node, int level, int which) override;
    const IndGroups& getIndGroups() const;
protected:
     IndGroups groups;
};

#endif
