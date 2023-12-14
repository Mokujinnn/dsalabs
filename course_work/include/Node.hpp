#pragma once
#include <string>

struct Node
{
    int key;
    unsigned level;
    std::string value;
    Node **next;

    Node(const int &key, const std::string &value, int level);
    Node(int level);
    ~Node();
};

Node::Node(const int &key, const std::string &value, int level)
    : key(key),
      value(value),
      level(level),
      next(new Node *[level])
{
    for (int i = 0; i < level; ++i)
    {
        this->next[i] = nullptr;
    }
}

Node::Node(int level)
    : key(0),
      value(""),
      level(level),
      next(new Node *[level])
{
    for (int i = 0; i < level; ++i)
    {
        this->next[i] = nullptr;
    }
}

Node::~Node()
{
    delete [] this->next;
}