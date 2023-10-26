#include <iostream>
#include <iomanip>
#include "rbtree.hpp"
#include "node.hpp"

Rbtree::Rbtree() : root(nullptr)
{
}

Rbtree::Rbtree(int key, std::string value)
{
    this->root = new Node(key, value);
}

Rbtree::~Rbtree()
{
    Node *node = this->root;
    free(node);
}

void Rbtree::free(Node *x)
{
    if (x->left != nullptr)
        free(x->left);

    if (x->right != nullptr)
        free(x->right);

    delete x;
}

void Rbtree::printInfo(Node *x)
{
    std::cout << std::boolalpha;
    std::cout << "This: " << std::setw(15) << x << " Color: ";
    if (x->color == BLACK)
        std::cout << "Black";
    else
        std::cout << std::setw(5) << "Red";
    std::cout << " Key: " << std::setw(5) << x->key << "\tValue:" << std::setw(10) << "'" + x->value + "'";
    if (x->parent == nullptr)
        std::cout << " Parent: " << std::setw(15) << "NIL";
    else
        std::cout << " Parent: " << std::setw(15) << x->parent;
    if (x->left == nullptr)
        std::cout << " Left: " << std::setw(15) << "NIL";
    else
        std::cout << " Left: " << std::setw(15) << x->left;
    if (x->right == nullptr)
        std::cout << " Right: " << std::setw(15) << "NIL\n";
    else
        std::cout << " Right: " << std::setw(15) << x->right << '\n';
}

Node *Rbtree::create(int key, std::string value, Node *parent)
{
    Node *node = new Node(key, value);
    if (!node)
    {
        std::cout << "Allocation failed. key ={" << key << "}, value = {" << value << "}\n";
        return nullptr;
    }

    return node;
}

void Rbtree::RotateR(Node *parent)
{
    Node *subL = parent->left;
    Node *subLR = subL->right;
    Node *ppNode = parent->parent;
    parent->left = subLR;
    if (subLR)
    {
        subLR->parent = parent;
    }
    subL->right = parent;
    parent->parent = subL;
    if (!ppNode)
    {
        root = subL;
        subL->parent = nullptr;
    }
    else if (ppNode->left == parent)
    {
        ppNode->left = subL;
        subL->parent = ppNode;
    }
    else
    {
        ppNode->right = subL;
        subL->parent = ppNode;
    }
    parent->color = RED;
    subL->color = BLACK;
    parent = subL;
}

void Rbtree::RotateL(Node *parent)
{
    Node *subR = parent->right;
    Node *subRL = subR->left;
    Node *ppNode = parent->parent;
    parent->right = subRL;
    if (subRL)
    {
        subRL->parent = parent;
    }
    subR->left = parent;
    parent->parent = subR;
    if (!ppNode)
    {
        root = subR;
        subR->parent = nullptr;
    }
    else if (ppNode->left == parent)//
    {
        ppNode->left = subR;
        subR->parent = ppNode;
    }
    else
    {
        ppNode->right = subR;
        subR->parent = ppNode;
    }
    parent->color = RED;
    subR->color = BLACK;
    parent = subR;
}

void Rbtree::addFixup(Node *cur, Node *parent) 
{
    while (parent && parent->color == RED)
    {
        Node *grandfather = parent->parent;
        if (parent == grandfather->left)
        {
            Node *uncle = grandfather->right;
            if (uncle && uncle->color == RED)
            {
                parent->color = uncle->color = BLACK;
                grandfather->color = RED;
                cur = grandfather;
                parent = cur->parent;
            }
            else
            {
                if (cur = parent->right)
                {
                    RotateL(parent);
                }
                RotateR(grandfather);
            }
        }
        else
        {
            Node *uncle = grandfather->left;
            if (uncle && uncle->color == RED)
            {
                parent->color = uncle->color = BLACK;
                grandfather->color = RED;
                cur = grandfather;
                parent = cur->parent;
            }
            else
            {
                if (cur = parent->left)
                {
                    RotateR(parent);
                }
                RotateL(grandfather);
            }
        }
    }

    this->root->color = BLACK;
}

void Rbtree::add(int key, std::string value)
{
    if (root == nullptr)
    {
        root = new Node(key, value);
        root->left = nullptr;
        root->right = nullptr;
        root->color = BLACK;
        return;
    }
    Node *cur = root;
    Node *parent = nullptr;
    while (cur)
    {
        if (cur->key > key)
        {
            parent = cur;
            cur = cur->left;
        }
        else if (cur->key < key)
        {
            parent = cur;
            cur = cur->right;
        }
        else
        {
            return;
        }
    }

    cur = new Node(key, value);
    if (parent->key > key)
    {
        parent->left = cur;
        cur->parent = parent;
    }
    else
    {
        parent->right = cur;
        cur->parent = parent;
    }

    addFixup(cur, parent);
}

Node *Rbtree::lookup(int key)
{
    Node *node = root;

    while (node != nullptr)
    {
        if (node->key == key)
        {
            return node;
        }
        else if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

Node *Rbtree::min()
{
    Node *node = root;
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node *Rbtree::min(Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node *Rbtree::max()
{
    Node *node = root;
    while (node->right != nullptr)
    {
        node = node->right;
    }
    return node;
}

Node *Rbtree::max(Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

void Rbtree::print(Node *x)
{
    if (!x)
        return;

    if (x->left != nullptr)
        print(x->left);

    printInfo(x);

    if (x->right != nullptr)
        print(x->right);
}

void Rbtree::print()
{
    Node *x = root;

    std::cout << "Root: " << x << " Key: " << x->key << '\n';

    if (!x)
        return;

    if (x->left != nullptr)
        print(x->left);

    printInfo(x);

    if (x->right != nullptr)
        print(x->right);

    std::cout << '\n';
}

void Rbtree::delFixup(Node *x)
{
    while (x != this->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED) // case 1
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateL(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) // case 2
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK) // case 3
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RotateR(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color; // case 4
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RotateL(x->parent);
                x = this->root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateR(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    RotateL(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RotateR(x->parent);
                x = this->root;
            }
        }
    }
    x->color = BLACK;
}

void Rbtree::del(int key)
{
    Node *z = lookup(key);
    if (!z)
    {
        std::cout << "No node with key{" << key << "}\n";
        return;
    }

    Node *y = z;
    bool ycolor = y->color;
    Node *x = nullptr;

    if (z->left == nullptr)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = min(z->right);
        ycolor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            if (x)
                x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        // Node* t = y->parent;

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        // t->left = nullptr;
    }

    if (ycolor == BLACK)
    {
        if (x)
            delFixup(x);
    }

    delete z;
}

void Rbtree::transplant(Node *u, Node *v)
{
    if (u->parent == nullptr)
        this->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

int Rbtree::blackHeight(Node *x)
{
    int left = 0;
    int right = 0;

    if (x->left)
    {
        left = blackHeight(x->left);
    }

    if (x->right)
    {
        right = blackHeight(x->right);
    }

    return std::max(left, right);
}

bool Rbtree::isRbtree()
{
    int left = 0;
    int right = 0;

    if (this->root)
    {
        left = blackHeight(this->root->left);
        right = blackHeight(this->root->right);
    }

    if (left == right)
    {
        return true;
    }
    else
    {
        return false;
    }
}