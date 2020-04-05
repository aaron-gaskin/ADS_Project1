#include "fibonacci_heap.h"

//Constructors and Destructors
FibonacciHeap::FibonacciHeap()
{
    maxNode = NULL;
}

FibonacciHeap::~FibonacciHeap()
{
    if (maxNode != NULL)
        delete maxNode;
}

//Check if hashtag already exists and either create key
// or perform IncreaseKey operation
void FibonacciHeap::CheckIfHashtagExists(string hashtag, int count)
{
    //No key exists, create key perform Insert operation
    if (hashTable.find(hashtag) == hashTable.end())
    {
        Node *newNode = new Node(count, hashtag);
        newNode->prev = newNode;
        newNode->next = newNode;
        hashTable[hashtag] = newNode;
        Insert(newNode);
    }
    else //key exists, perform IncreaseKey operation
    {
        Node *incNode = hashTable[hashtag];
        IncreaseKey(incNode, count);
    }
}

//Add a node to the heap using a hash
void FibonacciHeap::Insert(Node *newNode)
{
    //Null check max and new node
    if (maxNode == NULL)
    {
        maxNode = newNode;
        return;
    }
    if (newNode == NULL)
        return;

    //Compare counts, switch so maxNode is maximum
    if (maxNode->count < newNode->count)
    {
        Node *temp = maxNode;
        maxNode = newNode;
        newNode = temp;
    }

    //Link maxNode and newNode
    Node *maxNext = maxNode->next;
    Node *newPrev = newNode->prev;
    maxNode->next = newNode;
    newNode->prev = maxNode;

    //Relink disconnected nodes
    maxNext->prev = newPrev;
    newPrev->next = maxNext;
}

//Increase the value of the node and update maxNode
void FibonacciHeap::IncreaseKey(Node *node, int addCount)
{
    node->count = node->count + addCount;
    ////TODO: perform cascade cut and check if new maxNode
}

////TODO: Perform a cascde cut starting at input Node
//void FibonacciHeap::CascadeCut(Node *node)

////TODO:Remove the max node and update the tree
//Node* FibonacciHeap::RemoveMax();

//Return the max value
int FibonacciHeap::GetMax()
{
    return maxNode->count;
}

//TEST method
//Node* FibonacciHeap::Find(Node* node, int tagCount);
void FibonacciHeap::Print()
{
    Node *temp = maxNode->next;

    cout << maxNode->hashtag << ": " << maxNode->count << endl;

    while (temp != maxNode)
    {
        cout << temp->hashtag << ": " << temp->count << endl;
        temp = temp->next;
    }
}