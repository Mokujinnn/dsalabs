#pragma once

#include <string>

#include "node.hpp"

class Rbtree
{
private:
    Node *root;
    Node *Nil;

    Node *create(int key, std::string value, Node *parent);

    void addFixup(Node *z);//, Node *parent);

    void delFixup(Node *x);

    void printInfo(Node *x);

    void transplant(Node *u, Node *v);

    void print(Node *x);

    void free(Node *x);

    int blackHeight(Node* x);

    void RotateR(Node *parent);
    
    void RotateL(Node *parent);    
    
    Node *max(Node *node);    
    
    Node *min(Node *node);
    
public:
    Rbtree();

    Rbtree(int key, std::string value);

    ~Rbtree();

    void add(int key, std::string value);

    Node *lookup(int key);

    void del(int key);

    Node *min();

    Node *max();

    void print();

    bool isRbtree();

    int lookupCountOfNods(int key);
};

