#pragma once
#include <string>

#define RED true
#define BLACK false

struct Node
{
    bool        color;
    int         key;
    std::string value;
    Node* parent;
    Node* right;
    Node* left;

    Node();

    Node(int key, std::string value, Node * Nil);

    Node(int key, std::string value, Node* parent, Node * Nil);

    ~Node();
};
