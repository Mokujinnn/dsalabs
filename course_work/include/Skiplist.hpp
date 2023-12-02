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
    void insert(const int key, const std::string &value);
    void remove(const int key);
    bool search(const int key);
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

void Skiplist::insert(const int key, const std::string &value)
{
    Node **update = new Node *[maxLevel];
    Node *node = this->header;

    for (int i = node->level - 1; i >= 0; --i)
    {
        while (node->next[i] != this->Nil && node->next[i]->key < key)
        {
            node = node->next[i];
        }

        update[i] = node;
    }

    node = node->next[0];

    if (node == this->Nil || node->key != key)
    {
        int newlvl = 0;

        while (newlvl < this->maxLevel - 1 && (float(rand()) / RAND_MAX) < this->probability)
        {
            ++newlvl;
        }

        Node *newnode = new Node(key, value, newlvl + 1);

        for (int i = 0; i < newlvl + 1; ++i)
        {
            newnode->next[i] = update[i]->next[i];
            update[i]->next[i] = newnode;
        }

        std::cout << key << ": inserted successfully\n";
    }
    else
    {
        std::cout << key << ": already exist\n";
    }
}

void Skiplist::remove(const int key)
{
    Node **update = new Node*[this->maxLevel];
    Node *node = this->header;

    for (int i = node->level - 1; i >= 0; --i)
    {
        while (node->next[i] != this->Nil && node->next[i]->key < key)
        {
            node = node->next[i];
        }

        update[i] = node;
    }

    node = node->next[0];

    if (node != this->Nil && node->key == key)
    {
        for (int i = 0; i < this->maxLevel; ++i)
        {
            if (update[i]->next[i] != node)
            {
                break;
            }
            else
            {
                update[i]->next[i] = node->next[i];
            }
        }
        
        delete node;

        std::cout << key << ": deleted successfully\n";
    }
    else
    {
        std::cout << key << ": not found\n";
    }
}

bool Skiplist::search(const int key)
{
    Node *node = this->header;

    for (int i = node->level - 1; i >= 0; --i)
    {
        while (node->next[i] != this->Nil && node->next[i]->key < key)
        {
            node = node->next[i];
        }
    }

    node = node->next[0];

    if (node != this->Nil && node->key == key)
    {
        return true;
    }
    else
    {
        return false;
    }
}