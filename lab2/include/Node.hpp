#pragma once
#include <map>

struct Node
{   
    char ch;
    std::string value;
    std::map<char, Node *> children;

    Node(char ch, std::string value = "")
        : value(value),
          ch(ch)
    {
    }

    Node *GetChild(char ch)
    {
        auto it = this->children.find(ch);

        if (it == this->children.end())
            return nullptr;

        return it->second;
    }

    void SetChild(Node *child, char ch)
    {
        this->children.emplace(ch, child);
    }
};
