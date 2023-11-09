#include <iostream>
#include <iomanip>
#include "rbtree.hpp"
#include "node.hpp"

Rbtree::Rbtree()
    : Nil(new Node(0, ""))
{
    this->Nil->color = BLACK;
    this->root = this->Nil;
}

Rbtree::Rbtree(int key, std::string value)
    : Nil(new Node(0, "")),
      root(new Node(key, value))
{
    this->root->left = this->Nil;
    this->root->right = this->Nil;
    this->root->parent = this->Nil;
}

Rbtree::~Rbtree()
{
    Node *node = this->root;
    free(node);
    delete this->Nil;
}

void Rbtree::free(Node *x)
{
    if (x->left != this->Nil)
        free(x->left);

    if (x->right != this->Nil)
        free(x->right);

    delete x;
}

void Rbtree::printInfo(Node *x)
{
    std::cout << "This: " << std::setw(15) << x << " Color: ";
    if (x->color == BLACK)
        std::cout << "Black";
    else
        std::cout << std::setw(5) << "Red";
    std::cout << " Key: " << std::setw(5) << x->key << "\tValue:" << std::setw(10) << "'" + x->value + "'";
    if (x->parent == this->Nil)
        std::cout << " Parent: " << std::setw(15) << "NIL";
    else
        std::cout << " Parent: " << std::setw(15) << x->parent->key;
    if (x->left == this->Nil)
        std::cout << " Left: " << std::setw(15) << "NIL";
    else
        std::cout << " Left: " << std::setw(15) << x->left->key;
    if (x->right == this->Nil)
        std::cout << " Right: " << std::setw(15) << "NIL\n";
    else
        std::cout << " Right: " << std::setw(15) << x->right->key << '\n';
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

// void Rbtree::RotateR(Node *parent)
// {
//     Node *subL = parent->left;
//     Node *subLR = subL->right;
//     Node *ppNode = parent->parent;
//     parent->left = subLR;
//     if (subLR)
//     {
//         subLR->parent = parent;
//     }
//     subL->right = parent;
//     parent->parent = subL;
//     if (ppNode != this->Nil)
//     {
//         root = subL;
//         subL->parent = nullptr;
//     }
//     else if (ppNode->left == parent)
//     {
//         ppNode->left = subL;
//         subL->parent = ppNode;
//     }
//     else
//     {
//         ppNode->right = subL;
//         subL->parent = ppNode;
//     }
//     parent->color = RED;
//     subL->color = BLACK;
//     parent = subL;
// }

// void Rbtree::RotateL(Node *parent)
// {
//     Node *subR = parent->right;
//     Node *subRL = subR->left;
//     Node *ppNode = parent->parent;
//     parent->right = subRL;
//     if (subRL)
//     {
//         subRL->parent = parent;
//     }
//     subR->left = parent;
//     parent->parent = subR;
//     if (ppNode != this->Nil)
//     {
//         root = subR;
//         subR->parent = nullptr;
//     }
//     else if (ppNode->left == parent)//
//     {
//         ppNode->left = subR;
//         subR->parent = ppNode;
//     }
//     else
//     {
//         ppNode->right = subR;
//         subR->parent = ppNode;
//     }
//     parent->color = RED;
//     subR->color = BLACK;
//     parent = subR;
// }

void Rbtree::RotateL(Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    // if (y->left != this->Nil)
    // {
    //     y->left->parent = x;
    // }
    if (x->right != this->Nil)
    {
        x->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == this->Nil)
    {
        this->root = y;
    }
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void Rbtree::RotateR(Node *x)
{
    Node *y = x->left;
    x->left = y->right;

    // if (y->right != this->Nil)
    // {
    //     y->right->parent = x;
    // }
    if (x->left != this->Nil)
    {
        x->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == this->Nil)
    {
        this->root = y;
    }
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

// void Rbtree::addFixup(Node *cur, Node *parent) //
// {
//     while (parent->color == RED)
//     {
//         Node *grandfather = parent->parent;
//         if (parent == grandfather->left)
//         {
//             Node *uncle = grandfather->right;
//             if (uncle->color == RED)
//             {
//                 parent->color = uncle->color = BLACK;
//                 grandfather->color = RED;
//                 cur = grandfather;
//                 parent = cur->parent;
//             }
//             else
//             {
//                 if (cur = parent->right)
//                 {
//                     RotateL(parent);
//                 }
//                 RotateR(grandfather);
//             }
//         }
//         else
//         {
//             Node *uncle = grandfather->left;
//             if (uncle->color == RED)
//             {
//                 parent->color = uncle->color = BLACK;
//                 grandfather->color = RED;
//                 cur = grandfather;
//                 parent = cur->parent;
//             }
//             else
//             {
//                 if (cur = parent->left)
//                 {
//                     RotateR(parent);
//                 }
//                 RotateL(grandfather);
//             }
//         }
//     }

//     this->root->color = BLACK;
// }

void Rbtree::addFixup(Node *z)
{
    Node *uncle = nullptr;
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            uncle = z->parent->parent->right;
            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    RotateL(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RotateR(z->parent->parent);
            }
        }
        else
        {
            uncle = z->parent->parent->left;
            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    RotateR(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RotateL(z->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}

void Rbtree::add(int key, std::string value) //
{
    if (root == this->Nil)
    {
        root = new Node(key, value);
        root->parent = this->Nil;
        root->left = this->Nil;
        root->right = this->Nil;
        root->color = BLACK;
        return;
    }

    Node *cur = root;
    Node *parent = this->Nil;
    while (cur != this->Nil)
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
        cur->left = this->Nil;
        cur->right = this->Nil;
    }
    else
    {
        parent->right = cur;
        cur->parent = parent;
        cur->left = this->Nil;
        cur->right = this->Nil;
    }

    addFixup(cur);
}

Node *Rbtree::lookup(int key)
{
    Node *node = root;

    while (node != this->Nil)
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
    while (node->left != this->Nil)
    {
        node = node->left;
    }
    return node;
}

Node *Rbtree::min(Node *node)
{
    while (node->left != this->Nil)
    {
        node = node->left;
    }
    return node;
}

Node *Rbtree::max()
{
    Node *node = root;
    while (node->right != this->Nil)
    {
        node = node->right;
    }
    return node;
}

Node *Rbtree::max(Node *node)
{
    while (node->left != this->Nil)
    {
        node = node->left;
    }
    return node;
}

void Rbtree::print(Node *x)
{
    if (!x)
        return;

    if (x->left != this->Nil)
        print(x->left);

    printInfo(x);

    if (x->right != this->Nil)
        print(x->right);
}

void Rbtree::print()
{
    Node *x = root;

    std::cout << "Root: " << x << " Key: " << x->key << '\n';

    if (!x)
        return;

    if (x->left != this->Nil)
        print(x->left);

    printInfo(x);

    if (x->right != this->Nil)
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

    if (z->left == this->Nil)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == this->Nil)
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
            if (x != this->Nil)
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
        if (x != this->Nil)
            delFixup(x);
    }

    delete z;
}

void Rbtree::transplant(Node *u, Node *v)
{
    if (u->parent == this->Nil)
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

    if (x->left != this->Nil)
    {
        left = blackHeight(x->left);
    }

    if (x->right != this->Nil)
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

int Rbtree::lookupCountOfNods(int key)
{
    Node *node = root;
    int count = 1;

    while (node != this->Nil)
    {
        if (node->key == key)
        {
            return count;
        }
        else if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
        count++;
    }
    return -1;
}