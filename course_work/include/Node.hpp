#pragma once
#include <vector>
#include <string>

// template<class K, class V>

struct Node
{
    int key;
    unsigned level;
    std::string value;
    std::vector<Node *> next;

    Node(const int &key, const std::string &value, int level);
    Node(int level);
};

Node::Node(const int &key, const std::string &value, int level)
    : key(key),
      value(value),
      level(level),
      next(level, nullptr)
{
}

Node::Node(int level)
    : key(0),
      value(""),
      level(level),
      next(level, nullptr)
{
}