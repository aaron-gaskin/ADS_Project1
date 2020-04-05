#include "node.h"

//Constructors and Destructors
Node::Node(int count, string hashtag)
{
    this->count = count;
    this->hashtag = hashtag;
    parent = NULL;
    child = NULL;
    degree = 0;
    cut = false;
}

Node::~Node()
{
    if (right != NULL)
        delete next;

    if (child != NULL)
        delete child;
}