#include <iostream>
#include <string>
#include <map>

#include "node.h"
using namespace std;

class FibonacciHeap
{
public:
    FibonacciHeap();
    ~FibonacciHeap();
    void CheckIfHashtagExists(string hashtag, int count);
    void Insert(Node *newNode);
    void IncreaseKey(Node *node, int addCount);
    Node *RemoveMax();
    void CascadeCut(Node *node);
    int GetMax();

    //TEST method
    Node *Find(Node *node, int tagCount);
    void Print();

private:
    Node *maxNode;
    map<string, Node *> hashTable;
};