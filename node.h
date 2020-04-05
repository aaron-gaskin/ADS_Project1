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