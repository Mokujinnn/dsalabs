#include <iostream>

#include "rbtree.hpp"

Rbtree::Rbtree(int key, std::string value)
{
    this->right = nullptr;
    this->left  = nullptr;
    this->color = BLACK;
    this->key   = key;
    this->value = value;
}

Rbtree::~Rbtree()
{
    
}

Rbtree* Rbtree::create(int key, std::string value)
{
    Rbtree *node = new Rbtree(key, value);
    if (node == nullptr)
    {
        std::cout << "Allocation failed. key ={" << key << "}, value = {" << value << "}\n";
        return nullptr;
    }

    return node;
}

bool Rbtree::getColor() const
{
    return this->color;
}

void Rbtree::setColor(bool clr)
{
    this->color = clr;
}

int Rbtree::getKey() const
{
    return this->key;
}

void Rbtree::setKey(int k)
{
    this->key = key;
}

std::string Rbtree::getValue() const
{
    return this->value;
}

void Rbtree::setValue(std::string v)
{
    this->value = v;
}

void Rbtree::add(int key, std::string value)
{
    Rbtree *parent;
    Rbtree *node = this;

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

    node = create(key, value);
    if (parent->key > key)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
}

Rbtree *Rbtree::lookup(int key)
{
    Rbtree *node = this;

    while(this != nullptr)
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