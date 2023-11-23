#pragma once
#include <string>
#include "Node.hpp"

class Prefixtrie
{
private:
    Node *root;

public:
    Prefixtrie();
    ~Prefixtrie();

    void insert(const std::string &key);

    Node *lookup(const std::string &key);
};

Prefixtrie::Prefixtrie()
    : root(new Node('\0'))
{
}

Prefixtrie::~Prefixtrie()
{
}

void Prefixtrie::insert(const std::string &key)
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

Node *Prefixtrie::lookup(const std::string &key)
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


}