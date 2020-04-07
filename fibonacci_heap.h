/*
Name: Aaron Gaskin
Section: 11153
UFID: 9930-5710
References used:
https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/?ref=rp
https://github.com/robinmessage/fibonacci/blob/master/test.cpp
*/

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
    string PrintOutMaxes(int n);

    //TEST method
    void Print();

private:
    //Variables
    Node *maxNode;
    map<string, Node *> hashTable;
    int heapSize;

    //Methods
    void DeleteNodes(Node *node);
    void Insert(Node *newNode);
    void IncreaseKey(Node *node, int addCount);
    void CutNode(Node *node);
    void CascadeCut(Node *node);
    Node *RemoveMax();
    Node *RemoveNode(Node *node);
    void UnmarkNodeAndSiblings(Node *node);
    void SetParentPointerToNull(Node *node);
    void PairWiseMerge(Node *node);
    void AddChild(Node *parent, Node *child);
    Node *LinkTrees(Node *newNode, Node *nodeTwo);
    void UnlinkNodeFromSiblingList(Node *node);
    int GetMax();

    void Print(Node *node, int depth);
    void ChildPrint(Node *parentNode, int depth);
};