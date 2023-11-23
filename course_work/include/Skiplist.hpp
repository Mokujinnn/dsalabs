#pragma once
#include <iostream>
#include "Node.hpp"

class Skiplist
{
private:
    Node *header;
    Node *Nil;
    unsigned maxLevel;
    float probability;

public:
    Skiplist();
    Skiplist(unsigned maxLevel, float probability);
    void insert(const int key, const std::string& value);
    ~Skiplist();
};

Skiplist::Skiplist()
    : maxLevel(16),
      probability(0.5),
      header(new Node(16)),
      Nil(new Node(16))
{
    for (int i = 0; i < maxLevel; i++)
    {
        this->header->next[i] = this->Nil;
    }
}

Skiplist::Skiplist(unsigned maxLevel, float probability)
    : maxLevel(maxLevel),
      probability(probability),
      header(new Node(maxLevel)),
      Nil(new Node(maxLevel))
{
    if (this->probability >= 1)
    {
        this->probability = 0.5;
    }

    for (int i = 0; i < maxLevel; i++)
    {
        this->header->next[i] = this->Nil;
    }
}

Skiplist::~Skiplist()
{
}

void Skiplist::insert(const int key, const std::string& value)
{
    std::vector<Node *> update(maxLevel, this->header);
    Node* node = this->header;

    for (int i = node->level; i >= 0; --i)
    {
        while (node->next[i] != this->Nil && node->next[i]->value < value)
        {
            update[i] = node;
            node = node->next[i];
        }
    }
}