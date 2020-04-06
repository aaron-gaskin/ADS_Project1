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
    //Put new node into fibHeap and update maxNode if needed
    maxNode = LinkTrees(newNode, maxNode);

    //Increase heapSize
    heapSize++;
}

//Increase the value of the node and compare to maxNode
void FibonacciHeap::IncreaseKey(Node *node, int addCount)
{
    node->count = node->count + addCount;
    ////TODO: perform cascade cut and check if new maxNode
}

////TODO: Perform a cascde cut starting at input Node
void FibonacciHeap::CascadeCut(Node *node)
{
    if (node->marked)
        node->marked = true;
    else
    {
        /* code */
    }
}

////TODO: run removeMax n times then reinsert the removed maxes
void FibonacciHeap::PrintOutMaxes(int n)
{
    Node *removedMaxes[n];

    for (int i = 0; i < n; i++)
    {
        removedMaxes[i] = RemoveMax();
    }
}

//Remove the max node and update the tree
Node *FibonacciHeap::RemoveMax()
{
    Node *oldMax = maxNode;

    //Null check
    if (maxNode == NULL)
    {
        cout << "The heap is empty." << endl;
        return NULL;
    }
    //Check if maxNode is the only node
    else if (maxNode == maxNode->next && maxNode->child == NULL)
    {
        maxNode = NULL;
        return maxNode;
    }

    //Remove maxNode from the tree and link children to siblings if needed
    if (maxNode->next == maxNode)
    {
        maxNode = maxNode->child;
        maxNode->parent = NULL;
    }
    else
    {
        maxNode->next->prev = maxNode->prev;
        maxNode->prev->next = maxNode->next;
        maxNode = LinkTrees(maxNode->next, maxNode->child);
    }

    PairWiseMerge(maxNode);

    heapSize--;

    return oldMax;
}

//Pairwise merge all the trees in the root list
void FibonacciHeap::PairWiseMerge(Node *node)
{
    //Calculate the max degree a node can have
    int maxDegrees = log2(heapSize);
    Node *degArr[maxDegrees + 1] = {NULL};

    ////TODO: make do while
    //Perform the pairwise merging
    while (true)
    {
        if (degArr[node->degree] != NULL) //Merge node and treeNode
        {
            Node *treeNode = degArr[node->degree];

            //If same node in array, we looped and are done
            if (treeNode == node)
                break;

            //Reset array node
            degArr[node->degree] = NULL;

            //Compare node counts
            if (node->count > treeNode->count) //treeNode is less so make
            {
                //Remove treeNode from root list
                (treeNode->prev)->next = treeNode->next;
                (treeNode->next)->prev = treeNode->prev;
                AddChild(node, treeNode);
            }
            else //node is less so make child
            {
                ////TODO: change to remove Node from list instead of treeNode
                //Remove treeNode from root list
                (treeNode->prev)->next = treeNode->next;
                (treeNode->next)->prev = treeNode->prev;

                //if only one tree in heap
                if (node->next == node)
                {
                    //Only treeNode in heap so link to self
                    treeNode->next = treeNode;
                    treeNode->prev = treeNode;
                    AddChild(treeNode, node);
                }
                else //more than one
                {
                    //Replace node with treeNode
                    node->prev->next = treeNode;
                    node->next->prev = treeNode;
                    treeNode->next = node->next;
                    treeNode->prev = node->prev;
                    AddChild(treeNode, node);
                }
                node = treeNode;
            }
            degArr[node->degree] = node;
            ////TODO: check if continue is needed
            //continue;
        }
        else //Add node to empty degree spot in array
            degArr[node->degree] = node;

        //Update maxNode as we merge the tree
        if (maxNode->count < node->count)
            maxNode = node;

        node = node->next;
    }

    ////TODO: verify that maxNode is always selected
    //Loop through the top list and update maxNode
    // Node *start = maxNode;
    // Node *current = maxNode->next;
    // while (current != start)
    // {
    //     if (current->count > maxNode->count)
    //         maxNode = current;

    //     current = current->next;
    // }
}

//Merge the two nodes by making one the child of the other
void FibonacciHeap::AddChild(Node *parent, Node *child)
{
    //Remove child from tree
    // child->prev->next = child->next;
    // child->next->prev = child->prev;

    //Change child pointers
    child->parent = parent;
    child->next = child;
    child->prev = child;

    //Link children and increase parent degrees
    parent->child = LinkTrees(child, parent->child);
    parent->degree = parent->degree + 1;
}

//Link the two nodes along their next/prev pointers and return larger node
Node *FibonacciHeap::LinkTrees(Node *nodeOne, Node *nodeTwo)
{
    //Null check both nodes
    if (nodeTwo == NULL)
        return nodeOne;

    if (nodeOne == NULL)
        return nodeTwo;

    //Assume both nodes are part of a list
    //Break the list at input nodes and then combine them
    Node *twoNext = nodeTwo->next;
    Node *onePrev = nodeOne->prev;

    nodeTwo->next = nodeOne;
    nodeOne->prev = nodeTwo;
    twoNext->prev = onePrev;
    onePrev->next = twoNext;

    //Compare counts, return larger node
    if (nodeTwo->count < nodeOne->count)
        return nodeOne;
    else
        return nodeTwo;
}

////TODO: test unmark
//Unmark node, siblings, and children
void FibonacciHeap::UnmarkSiblingsAndChildren(Node *node)
{
    //null check
    if (node == NULL)
        return;

    //Unmark nodes
    Node *temp = node;
    do
    {
        temp->marked = false;
        UnmarkSiblingsAndChildren(temp->child);
        temp = temp->next;

    } while (temp != node);
}

//Return the max value
int FibonacciHeap::GetMax()
{
    return maxNode->count;
}

//TEST methods
void FibonacciHeap::Print()
{
    Print(maxNode, 0);
}

void FibonacciHeap::Print(Node *node, int depth)
{
    //Print out siblings
    Node *temp = node->next;

    //space based on depth
    for (int i = 0; i < depth; i++)
        cout << "  ";
    cout << node->hashtag << ": " << node->count /*<< ": " << node->marked*/ << endl;

    ChildPrint(node, depth);

    while (temp != node && temp != NULL)
    {

        //space based on depth
        for (int i = 0; i < depth; i++)
            cout << "  ";

        cout << temp->hashtag << ": " << temp->count /*<< ": " << temp->marked*/ << endl;

        ChildPrint(temp, depth);

        temp = temp->next;
    }
}

//TEST
//Print out the nodes children
void FibonacciHeap::ChildPrint(Node *parentNode, int depth)
{
    Node *child = parentNode->child;
    if (child != NULL)
    {
        Print(child, depth + 1);
    }
}