#include "node.hpp"

Node::Node()
{
    this->key = 0;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->color = BLACK;
}

Node::Node(int key, std::string value)
{
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->color = BLACK;
    this->key = key;
    this->value = value;
}

Node::Node(int key, std::string value, Node* parent)
{
    this->parent = parent;
    this->right = nullptr;
    this->left = nullptr;
    this->color = RED;
    this->key = key;
    this->value = value;
}

Node::~Node() { }
