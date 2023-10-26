#include "node.hpp"

Node::Node(int& key, std::string& value) : left(nullptr),
                                         right(nullptr),
                                         parent(nullptr),
                                         key(key),
                                         value(value),
                                         color(RED)
{
}

Node::~Node() {}
