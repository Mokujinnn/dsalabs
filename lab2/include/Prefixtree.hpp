#pragma once
#include <string>
#include <iostream>
#include "Node.hpp"

class Prefixtree
{
private:
    Node *root;

    Node *lookupforremove(const std::string &key);

    void print(Node *node);

    void del(Node* node);

public:
    Prefixtree();
    ~Prefixtree();

    void insert(const std::string &key);

    Node *lookup(const std::string &key);

    void remove(const std::string &key);

    void print();
};

Prefixtree::Prefixtree()
    : root(new Node('\0'))
{
}

void Prefixtree::del(Node* node)
{
    for (auto &[key, value] : node->children)
    {
        if (value->children.size() != 0)
        {
            del(value);
        }
        delete value;
    }
}

Prefixtree::~Prefixtree()
{
    for (auto &[key, value] : this->root->children)
    {
        if (value->children.size() != 0)
        {
            del(value);
        }
        delete value;
    }

    delete root;
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

Node *Prefixtree::lookupforremove(const std::string &key)
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
    return node;
}

void Prefixtree::remove(const std::string &key)
{
    Node *node = lookup(key);
    if (!node)
        return;

    std::string str = key;
    char deletedchar;
    while (node->children.size() == 0)
    {
        deletedchar = node->ch;
        delete node;
        str.erase(str.size() - 1, 1);
        node = lookupforremove(str);
    }

    node->children.erase(deletedchar);
}

void Prefixtree::print()
{
    Node *node = this->root;
    for (const auto &[key, value] : node->children)
    {
        if (value->value != "")
            std::cout << value->value << std::endl;

        print(value);
    }
    std::cout << '\n';
}

void Prefixtree::print(Node *node)
{
    for (const auto &[key, value] : node->children)
    {
        if (value->value != "")
            std::cout << value->value << std::endl;

        print(value);
    }
}