#include <iostream>
#include <iomanip>
#include "rbtree.hpp"
#include "node.hpp"

Rbtree::Rbtree()
{
    this->root = nullptr;
}

Rbtree::Rbtree(int key, std::string value)
{
    this->root = new Node(key, value);
}

Rbtree::~Rbtree()
{
    Node* node = this->root;

    free(node);
}

void Rbtree::free(Node* x)
{
    if (x->left)
        free(x->left);

    if (x->right)
        free(x->right);

    delete x;
}

void Rbtree::printInfo(Node* x)
{
    std::cout << std::boolalpha;
    std::cout << "This: " << x << " Color: "; if (x->color == BLACK) std::cout << "Black"; else std::cout << std::setw(5) << "Red";
    std::cout << " Key: " << std::setw(5) << x->key << "\tValue:" << std::setw(10) << "'" + x->value + "'"
         << " Parent: " << std::setw(15) << x->parent  << " Left: " << std::setw(15) << x->left  <<
        " Right: " << x->right << std::setw(15) << '\n';
}

Node* Rbtree::create(int key, std::string value, Node* parent)
{
    Node* node = new Node(key, value, parent);
    if (!node)
    {
        std::cout << "Allocation failed. key ={" << key << "}, value = {" << value << "}\n";
        return nullptr;
    }

    return node;
}

void Rbtree::rightRotate(Node* x)
{
    Node* y = x->left;
    x->left = y->right;

    if (y->right != nullptr)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;


    if (x->parent)
    {
        if (x == x->parent->left) //SIGFAULT
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    else
    {
        this->root = y;
    }

    y->right = x;
    x->parent = y;
}

void Rbtree::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
    {
        y->left->parent = y;
    }

    y->parent = x->parent;


    if (x->parent)
    {
        if (x == x->parent->left) //SIGFAULT
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    else
    {
        this->root = y;
    }

    y->left = x;
    x->parent = y;
}

void Rbtree::addFixup(Node* z)
{
    while ((z->parent) && (z->parent->color == RED))
    {
        if (z->parent == z->parent->parent->left)
        {
            Node* uncle = z->parent->parent->right;
            if ((uncle) && (uncle->color == RED))
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
                    leftRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node* uncle = z->parent->parent->left;
            if ((uncle) && (uncle->color == RED))
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
                    rightRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }

    this->root->color = BLACK;
}

void Rbtree::add(int key, std::string value)
{
    Node* parent = nullptr;
    Node* node = root;

    while (node != nullptr)
    {
        parent = node;
        if (node->key < key)
        {
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            return;
        }
    }

    node = create(key, value, parent);
    if (parent == nullptr)
    {
        this->root = node;
        this->root->color = BLACK;
        return;
    }
    else
    {
        if (parent->key > key)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
    }

    addFixup(node);
}

Node* Rbtree::lookup(int key)
{
    Node* node = root;

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

Node* Rbtree::min()
{
    Node* node = root;
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* Rbtree::min(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node* Rbtree::max()
{
    Node* node = root;
    while (node->right != nullptr)
    {
        node = node->right;
    }
    return node;
}

Node* Rbtree::max(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

void Rbtree::print(Node* x)
{
    if (!x)
        return;

    if (x->left)
        print(x->left);

    printInfo(x);

    if (x->right)
        print(x->right);

}

void Rbtree::print()
{
    Node* x = root;

    std::cout << "Root: " << x << '\n';

    if (!x)
        return;

    if (x->left)
        print(x->left);

    printInfo(x);

    if (x->right)
        print(x->right);

    
}

void Rbtree::delFixup(Node* x)
{
    while (x != this->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
            }
        }
        else
        {
            Node* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
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
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
            }
        }
    }
    x->color = BLACK;
}

void Rbtree::del(int key)
{
    Node* z = lookup(key);
    if (!z)
    {
        std::cout << "No node with key{" << key << "}\n";
        return;
    }

    Node* y = z;
    bool ycolor = y->color;
    Node* x = nullptr;

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
            x->parent = y;
        else
        {
            if (y->right) //sakjsasajk
                transplant(y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        Node* t = y->parent;

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        t->left = nullptr;
    }

    if (ycolor == BLACK)
    {
        if (x) // хз
        {
            delFixup(x);
        }
        else if (y == y->parent->left)
        {
            delFixup(y->parent->right);
        }
        else
        {
            delFixup(y->parent->left);
        }
    }

    delete z;
}

void Rbtree::transplant(Node* u, Node* v)
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