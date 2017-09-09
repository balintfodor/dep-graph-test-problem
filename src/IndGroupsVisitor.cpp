#include "IndGroupsVisitor.h"

#include <utility>

using namespace std;

void IndGroupsVisitor::accept(const Node::ptr_t &node, int level, int which)
{
    groups.resize(max(groups.size(), (size_t)level + 1));
    groups[level].resize(max(groups[level].size(), (size_t)which + 1));
    groups[level][which] = node;
}

const IndGroupsVisitor::IndGroups& IndGroupsVisitor::getIndGroups() const
{
    return groups;
}