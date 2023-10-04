#pragma once

#include <string>

#include "Rbtree.hpp"

#define RED true
#define BLACK false

class Rbtree
{
private:

    bool        color;
    int         key;
    std::string value;
    Rbtree *    root;
    Rbtree *    parent;
    Rbtree *    right;
    Rbtree *    left;

    Rbtree* create(int key, std::string value, Rbtree * parent);

    void leftRotate(Rbtree* x);

    void rightRotate(Rbtree* x);

    void fixup(Rbtree * z);

    void printInfo(Rbtree * x);

    Rbtree(int key, std::string value, Rbtree * parent);
    
public:

    Rbtree();

    Rbtree(int key, std::string value);

    ~Rbtree();

    void add(int key, std::string value);

    Rbtree* lookup(int key);

    void del(int key);

    Rbtree* min();

    Rbtree* max();

    void print(Rbtree *x);

    // bool getColor() const;

    // void setColor(bool clr);

    // int getKey() const;

    // void setKey(int k);

    // std::string getValue() const;

    // void setValue(std::string v);

};