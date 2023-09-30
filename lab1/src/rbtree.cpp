#include <iostream>

#include "rbtree.hpp"

Rbtree::Rbtree()
{
    this->parent = nullptr;
    this->root   = nullptr;
    this->right  = nullptr;
    this->left   = nullptr;
}

Rbtree::Rbtree(int key, std::string value)
{
    this->parent = nullptr;
    this->root   = this;
    this->right  = nullptr;
    this->left   = nullptr;
    this->color  = BLACK;
    this->key    = key;
    this->value  = value;
}

Rbtree::Rbtree(int key, std::string value, Rbtree * parent)
{
    this->parent = parent;
    
    if (parent == nullptr)
    {
        this->root = this;
    }
    else
    {
        this->root = parent->root;
    }

    this->right  = nullptr;
    this->left   = nullptr;
    this->color  = RED;
    this->key    = key;
    this->value  = value;
}

Rbtree::~Rbtree()
{

}

Rbtree* Rbtree::create(int key, std::string value, Rbtree * parent)
{
    Rbtree *node = new Rbtree(key, value, parent);
    if (node == nullptr)
    {
        std::cout << "Allocation failed. key ={" << key << "}, value = {" << value << "}\n";
        return nullptr;
    }

    return node;
}

void Rbtree::add(int key, std::string value)
{
    Rbtree *parent = nullptr;
    Rbtree *node = this->root;

    while(node != nullptr)
    {
        parent = node;
        if(node->key < key)
        {
            node = node->right;
        }
        else if(node->key > key)
        {
            node = node->left;
        }
        else
        {
            return;
        }
    }

    node = create(key, value, parent);
    if (this->root == nullptr)
    {
        this->root = node;
    }
    else
    {
        if (parent->key > key)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
    }
    
    
}

Rbtree *Rbtree::lookup(int key)
{
    Rbtree *node = this->root;

    while(node != nullptr)
    {
        if(node->key == key)
        {
            return node;
        }
        else if(key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

Rbtree* Rbtree::min()
{
    Rbtree* node = this;
    while(node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Rbtree* Rbtree::max()
{
    Rbtree* node = this;
    while(node->right != nullptr)
    {
        node = node->right;
    }
    return node;
}