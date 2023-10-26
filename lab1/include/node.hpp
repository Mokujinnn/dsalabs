#pragma once
#include <string>

#define RED true
#define BLACK false

struct Node
{
    
    std::string value;
    Node*       parent;
    Node*       right;
    Node*       left;
    int         key;
    bool        color;

    Node(int& key, std::string& value);

    ~Node();
};
