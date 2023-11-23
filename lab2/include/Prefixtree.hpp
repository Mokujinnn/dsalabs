#pragma once
#include <string>
#include "Node.hpp"

class Prefixtree
{
private:
    Node *root;

public:
    Prefixtree();
    ~Prefixtree();

    void insert(const std::string &key);

    Node *lookup(const std::string &key);

    void remove(const std::string &key);
};

Prefixtree::Prefixtree()
    : root(new Node('\0'))
{
}

Prefixtree::~Prefixtree()
{
}

void Prefixtree::insert(const std::string &key)
{
    Node *node = this->root;
    for (const auto &c : key)
    {
        Node *child = node->GetChild(c);

        if (child == nullptr)
        {
            child = new Node(c);
            node->SetChild(child, c);
        }
        node = child;
    }
    node->value = key;
}

Node *Prefixtree::lookup(const std::string &key)
{
    Node *node = this->root;
    for (const auto &c : key)
    {
        Node *child = node->GetChild(c);
        if (child == nullptr)
        {
            return nullptr;
        }

        node = child;
    }

    if (node->value == "")
        return nullptr;
    
    return node;
}

void Prefixtree::remove(const std::string &key)
{
    
}