#include "fibonacci_heap.h"



    //Constructors and Destructors
    Node::Node(int count, string hashtag)
    {
        count = count;
        hashtag = hashtag;
    }

    Node::~Node()
    {
        if (right != NULL)
            delete right;

        if (child != NULL)
            delete child;
    }

    FibonacciHeap::FibonacciHeap()
    {
        maxNode = NULL;
    }

    FibonacciHeap::~FibonacciHeap()
    {
        if(maxNode != NULL)
            delete maxNode;
    }

    //Node* FibonacciHeap::Insert(int tagCount, string hashtag);

    //void FibonacciHeap::Merge(Node* otherHeap);

    //int FibonacciHeap::GetMax();

    //Node* FibonacciHeap::RemoveMax();

    //void FibonacciHeap::IncreaseCount(Node* node, int addCount);


    //TEST method
    //Node* FibonacciHeap::Find(Node* node, int tagCount);