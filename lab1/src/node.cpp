#include "node.hpp"

Node::Node()
{
    this->color = RED;
    this->left = new Node;
    this->right = new Node;
}

bool Node::getColor() const
{
    return this->color;
}

void Node::setColor(bool clr)
{
    this->color = clr;
}

int Node::getKey() const
{
    return this->key;
}

void Node::setKey(int k)
{
    this->key = key;
}

std::string Node::getValue() const
{
    return this->value;
}

void Node::setValue(std::string v)
{
    this->value = v;
}

