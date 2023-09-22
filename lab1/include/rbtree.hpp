#pragma once

#include "node.hpp"


class Rbtree
{
private:

    Node* root;

public:

    Rbtree(int key, std::string value);

    ~Rbtree();

    Node* add(int key, std::string value);

    Node* lookup(int key);

    void del(int key);

    Node* min();

    Node* max();

};