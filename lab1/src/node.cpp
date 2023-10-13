#include "node.hpp"

Node::Node()
{
    // this->key = 0;
    this->parent = this;
    this->right = this;
    this->left = this;
    this->color = BLACK;
}

Node::Node(int key, std::string value, Node * Nil)
{
    this->parent = Nil;
    this->right = Nil;
    this->left = Nil;
    this->color = BLACK;
    this->key = key;
    this->value = value;
}

Node::Node(int key, std::string value, Node* parent, Node * Nil)
{
    this->parent = parent;
    this->right = Nil;
    this->left = Nil;
    this->color = RED;
    this->key = key;
    this->value = value;
}

Node::~Node() { }
