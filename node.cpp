#include "node.h"

//Constructors and Destructors
Node::Node(int count, string hashtag)
{
    this->count = count;
    this->hashtag = hashtag;
    parent = NULL;
    prev = NULL;
    next = NULL;
    child = NULL;
    degree = 0;
    marked = false;
}

Node::~Node()
{
}