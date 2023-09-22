#pragma once

#include <string>

#define RED true
#define BLACK false

class Node
{
private:
    bool color;
    int key;
    Node *right;
    Node *left;
    std::string value;

public:
    Node();

    ~Node();

    bool getColor() const;

    void setColor(bool clr);

    int getKey() const;

    void setKey(int k);

    std::string getValue() const;

    void setValue(std::string v);
};