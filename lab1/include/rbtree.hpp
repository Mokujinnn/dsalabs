#pragma once

#include <string>

#include "node.hpp"


class Rbtree
{
private:

    Node * root;
    Node * Nil;

    Node* create(int key, std::string value, Node* parent);

    void leftRotate(Node* x);

    void rightRotate(Node* x);

    void addFixup(Node* z);

    void delFixup(Node* x);

    void printInfo(Node* x);

    void transplant(Node* u, Node* v);

    void print(Node* x);

    void free(Node* x);

public:

    Rbtree();

    Rbtree(int key, std::string value);

    ~Rbtree();

    void add(int key, std::string value);

    Node* lookup(int key);

    void del(int key);

    Node* min();

    Node* min(Node* node);

    Node* max();

    Node* max(Node* node);

    void print();

    // bool getColor() const;

    // void setColor(bool clr);

    // int getKey() const;

    // void setKey(int k);

    // std::string getValue() const;

    // void setValue(std::string v);

};