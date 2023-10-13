#include <iostream>
#include <iomanip>
#include "rbtree.hpp"
#include "node.hpp"

Rbtree::Rbtree()
{
    this->Nil = new Node();
    this->root = this->Nil;
}

Rbtree::Rbtree(int key, std::string value)
{
    this->Nil = new Node();
    this->root = new Node(key, value, this->Nil);
}

Rbtree::~Rbtree()
{
    Node* node = this->root;

    free(node);
    delete Nil;
}

void Rbtree::free(Node* x)
{
    if (x->left != this->Nil)
        free(x->left);

    if (x->right != this->Nil)
        free(x->right);

    delete x;
}

void Rbtree::printInfo(Node* x)
{
    std::cout << std::boolalpha;
    std::cout << "This: " << x << " Color: "; if (x->color == BLACK) std::cout << "Black"; else std::cout << std::setw(5) << "Red";
    std::cout << " Key: " << std::setw(5) << x->key << "\tValue:" << std::setw(10) << "'" + x->value + "'";
    if (x->parent == this->Nil) 
        std::cout << " Parent: " << std::setw(15) << "NIL";
    else
        std::cout << " Parent: " << std::setw(15) << x->parent;
    if (x->left == Nil)
        std::cout << " Left: " << std::setw(15) << "NIL";
    else
        std::cout << " Left: " << std::setw(15) << x->left;
    if (x->right == Nil)
        std::cout << " Right: " << std::setw(15) << "NIL\n";
    else
        std::cout << " Right: " << std::setw(15) << x->right << '\n';
}

Node* Rbtree::create(int key, std::string value, Node* parent)
{
    Node* node = new Node(key, value, parent, this->Nil);
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

    if (y->right != this->Nil)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == this->Nil)
    {
        this->root = y;
    }
    else if (x == x->parent->left) //SIGFAULT
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

void Rbtree::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;

    if (y->left != this->Nil)
    {
        y->left->parent = y;
    }

    y->parent = x->parent;

    if (x->parent == this->Nil)
    {
        this->root = y;
    }
    else if (x == x->parent->left) //SIGFAULT
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void Rbtree::addFixup(Node* z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node* uncle = z->parent->parent->right;
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
    Node* parent = this->Nil;
    Node* node = this->root;

    while (node != this->Nil)
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
    if (parent == this->Nil)
    {
        this->root = node;
        this->root->color = BLACK;
        node->left = this->Nil;
        node->right = this->Nil;
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
    node->left = this->Nil;
    node->right = this->Nil;

    addFixup(node);
}

Node* Rbtree::lookup(int key)
{
    Node* node = root;

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

Node* Rbtree::min()
{
    Node* node = root;
    while (node->left != this->Nil)
    {
        node = node->left;
    }
    return node;
}

Node* Rbtree::min(Node* node)
{
    while (node->left != this->Nil)
    {
        node = node->left;
    }
    return node;
}

Node* Rbtree::max()
{
    Node* node = root;
    while (node->right != this->Nil)
    {
        node = node->right;
    }
    return node;
}

Node* Rbtree::max(Node* node)
{
    while (node->left != this->Nil)
    {
        node = node->left;
    }
    return node;
}

void Rbtree::print(Node* x)
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
    Node* x = root;

    std::cout << "Root: " << x << " Key: " << x->key <<   '\n';

    if (!x)
        return;

    if (x->left != this->Nil)
        print(x->left);

    printInfo(x);

    if (x->right != this->Nil)
        print(x->right);

    std::cout << '\n';
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
            x->parent = y;
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
        // t->left = this->Nil;
    }

    if (ycolor == BLACK)
    {
        delFixup(x);
    }

    delete z;
}

void Rbtree::transplant(Node* u, Node* v)
{
    if (u->parent == this->Nil)
        this->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}