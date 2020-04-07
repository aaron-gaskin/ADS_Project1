/*
Name: Aaron Gaskin
Section: 11153
UFID: 9930-5710
References used:
https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/?ref=rp
https://github.com/robinmessage/fibonacci/blob/master/test.cpp
*/

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