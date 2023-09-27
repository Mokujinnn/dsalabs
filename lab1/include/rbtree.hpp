#pragma once

#include <string>

#include "Rbtree.hpp"


#define RED true
#define BLACK false

class Rbtree
{
private:
    bool color;
    int key;
    Rbtree *right;
    Rbtree *left;
    std::string value;

public:

    Rbtree(int key, std::string value);

    ~Rbtree();

    Rbtree* add(int key, std::string value);

    Rbtree* lookup(int key);

    void del(int key);

    Rbtree* min();

    Rbtree* max();

    bool getColor() const;

    void setColor(bool clr);

    int getKey() const;

    void setKey(int k);

    std::string getValue() const;

    void setValue(std::string v);

};