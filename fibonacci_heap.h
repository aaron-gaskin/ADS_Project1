#include <iostream>
#include <string>
#include <map>
#include <cmath>

#include "node.h"
using namespace std;

class FibonacciHeap
{
public:
    FibonacciHeap();
    ~FibonacciHeap();
    void CheckIfHashtagExists(string hashtag, int count);
    void Insert(Node *newNode);
    Node *LinkTrees(Node *newNode, Node *nodeTwo);
    void IncreaseKey(Node *node, int addCount);
    Node *RemoveMax();
    void UnmarkSiblingsAndChildren(Node *node);
    void PairWiseMerge(Node *node);
    void AddChild(Node *parent, Node *child);
    void CascadeCut(Node *node);
    int GetMax();

    //TEST method
    Node *Find(Node *node, int tagCount);
    void Print();
    void Print(Node *node, int depth);
    void ChildPrint(Node *parentNode, int depth);

private:
    Node *maxNode;
    map<string, Node *> hashTable;
    int heapSize;
};