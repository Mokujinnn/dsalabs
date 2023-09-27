#include "rbtree.hpp"

Rbtree::Rbtree(int key, std::string value)
{
    this->right = nullptr;
    this->left  = nullptr;
    this->color = BLACK;
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

Rbtree::~Rbtree()
{

}

Rbtree* Rbtree::add(int key, std::string value)
{
    return nullptr;
}