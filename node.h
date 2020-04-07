/*
Name: Aaron Gaskin
Section: 11153
UFID: 9930-5710
References used:
https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/?ref=rp
https://github.com/robinmessage/fibonacci/blob/master/test.cpp
*/

#include <iostream>
using namespace std;

//Node declaration
class Node
{
public:
    Node(int count, string hashtag);
    ~Node();
    Node *parent;
    Node *prev;
    Node *next;
    Node *child;
    int degree;

    int count;
    string hashtag;
    bool marked;
};