#include "rbtree.hpp"

Rbtree::Rbtree(int key, std::string value)
{
    this->root = new Node;
    this->root->setKey(key);
    this->root->setValue(value);
}

Rbtree::~Rbtree()
{

}

Node* Rbtree::add(int key, std::string value)
{
    return nullptr;
}