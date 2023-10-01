#include <iostream>
#include <iomanip>
#include "rbtree.hpp"

Rbtree::Rbtree()
{
    this->parent = nullptr;
    this->root   = nullptr;
    this->right  = nullptr;
    this->left   = nullptr;
    this->color  = BLACK;
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

void Rbtree::printInfo(Rbtree * x)
{
    std::cout << std::boolalpha;
    std::cout << " Color: " << x->color << "\tKey: " << std::setw(5) << x->key << std::setw(5) << "\tValue:" << std::setw(10) << "'" + x->value + "'" << std::setw(10)
    << " Root: " << std::setw(7) << x->root << std::setw(15) << " Parent: " << std::setw(15) << x->parent << std::setw(7) << " Left: " << std::setw(15) << x->left << std::setw(7) << 
    " Right: " << std::setw(15) << x->right << std::setw(7) << '\n';
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

void Rbtree::rightRotate(Rbtree* x)
{
    Rbtree* y = x->left;
    x->left = y->right;

    if(y->right != nullptr)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void Rbtree::leftRotate(Rbtree* x)
{
    Rbtree* y = x->right;
    x->right = y->left;

    if(y->left != nullptr)
    {
        y->left->parent = y;
    }

    y->parent = x->parent;

    if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Rbtree::fixup()
{
    
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
    if (parent == nullptr)
    {
        this->color = BLACK;
        this->key = node->key;
        this->value = node->value;
        this->root = this;
        this->parent = node->parent;
        delete node;
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

    
    // std::cout << "This: " << this; printInfo(this);
    // if(parent)
    // {
    //     std::cout << "This: " << node; printInfo(node);
    //     std::cout << "This: " << parent; printInfo(parent);
    // }
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
