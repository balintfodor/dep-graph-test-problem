#ifndef _Visitor_h_
#define _Visitor_h_

#include "Node.h"

class Visitor {
public:
    virtual void accept(const Node::ptr_t &node, int level, int which) = 0;
    virtual ~Visitor() {}
};

#endif
