#include "fibonacci_heap.h"

//Constructors and Destructors
FibonacciHeap::FibonacciHeap()
{
    maxNode = NULL;
    heapSize = 0;
}

FibonacciHeap::~FibonacciHeap()
{
    hashTable.empty();

    if (maxNode != NULL)
        delete maxNode;
}

void FibonacciHeap::DeleteNodes(Node *node)
{
    if (node != NULL)
    {
        Node *temp = node;
        do
        {
            Node *deleteNode = temp;
            temp = temp->next;
            DeleteNodes(deleteNode->child);
            delete deleteNode;

        } while (temp != node);
    }
}

/********* Check If Hashtag Exists *********/
//Either create key or perform IncreaseKey operation on existing node
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

/********* Insert*********/
//Add a node to the heap using a hash
void FibonacciHeap::Insert(Node *newNode)
{
    //Put new node into fibHeap and update maxNode if needed
    maxNode = LinkTrees(newNode, maxNode);

    //Increase heapSize
    heapSize++;
}

/********* IncreaseKey *********/
//Increase the value of the node and compare to maxNode
void FibonacciHeap::IncreaseKey(Node *node, int addCount)
{
    node->count = node->count + addCount;

    //Check if child->count is greater than parent->count and cut if needed
    if (node->parent != NULL && node->count > node->parent->count)
        CutNode(node);
    else if (node->count > maxNode->count)
        maxNode = node;
}

/********* Cut node *********/
void FibonacciHeap::CutNode(Node *node)
{
    Node *parent = node->parent;

    //End if parent is NULL, root list reached
    if (parent == NULL)
        return;

    //Update sibling pointers and parent->child if necessary
    if (node->next != node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (parent->child == node)
            parent->child = node->next;
    }
    else //Only child of parent so NULL parent->child
        parent->child = NULL;

    parent->degree = parent->degree - 1;

    //Reset node values then link to root list and update maxNode if needed
    node->parent = NULL;
    node->marked = false;
    node->next = node->prev = node;
    maxNode = LinkTrees(node, maxNode);

    CascadeCut(parent);
}

/********* Cascade Cut *********/
//Perform a cascde cut starting at input Node
void FibonacciHeap::CascadeCut(Node *node)
{
    if (!node->marked)
    {
        if (node->parent != NULL) //Check if in root list
            node->marked = true;
    }
    else
        CutNode(node);
}

/********* Print Out Maxes *********/
//Run removeMax n times then reinsert the removed maxes
string FibonacciHeap::PrintOutMaxes(int n)
{
    Node *removedMaxes[n] = {NULL};

    string csvMaxes = "";

    //RemoveMax() n times
    for (int i = 0; i < n; i++)
    {
        Node *temp = RemoveMax();
        removedMaxes[i] = new Node(temp->count, temp->hashtag);
        hashTable.erase(temp->hashtag);

        delete temp;

        //Format the string output
        if (removedMaxes[i] != NULL && i != n - 1)
            csvMaxes += removedMaxes[i]->hashtag + ",";
        else if (removedMaxes[i] != NULL)
            csvMaxes += removedMaxes[i]->hashtag;
    }

    //Reinsert removed nodes
    for (int i = 0; i < n; i++)
        CheckIfHashtagExists(removedMaxes[i]->hashtag, removedMaxes[i]->count);

    return csvMaxes;
}

/********* Remove Max *********/
//Remove the max node and update the tree
Node *FibonacciHeap::RemoveMax()
{
    Node *oldMax = RemoveNode(maxNode);
    return oldMax;
}

/********* Remove Node *********/
//Remove the node and merge children with root list
Node *FibonacciHeap::RemoveNode(Node *node)
{
    Node *oldNode = node;

    //Null check
    if (node == NULL)
        return NULL;

    //Check if node is the only node
    else if (node == node->next && node->child == NULL)
    {
        node = NULL;
        return node;
    }

    //Remove node from the tree and link children to siblings if needed
    if (node->next != node)
    {
        //If siblings, link with node children
        node->next->prev = node->prev;
        node->prev->next = node->next;

        //Update parent->child pointer if needed
        if (node->parent != NULL)
            if (node->parent->child == node)
                node->parent->child = node->next;

        if (node == maxNode)
            maxNode = LinkTrees(maxNode->next, maxNode->child);
    }
    else //Only child, merge children with top level
    {

        //Update parent->child pointer if needed
        if (node->parent != NULL)
            node->parent->child = NULL;

        if (node != maxNode)
            maxNode = LinkTrees(node->child, maxNode);
        else
            maxNode = maxNode->child;
    }

    //Update new root list nodes then merge
    UnmarkNodeAndSiblings(maxNode);

    SetParentPointerToNull(maxNode);

    PairWiseMerge(maxNode);

    heapSize--;

    return oldNode;
}

/********* UnmarkChildren *********/
//Unmark node and siblings, and children
void FibonacciHeap::UnmarkNodeAndSiblings(Node *node)
{
    //null check
    if (node == NULL)
        return;

    //Unmark siblings of node
    Node *temp = node;
    do
    {
        temp->marked = false;
        temp = temp->next;

    } while (temp != node);
}

/********* SetParentPointerToNull *********/
//Set node and siblings parent ptr to NULL
void FibonacciHeap::SetParentPointerToNull(Node *node)
{
    Node *current = node;
    do
    {
        current->parent = NULL;
        current = current->next;

    } while (current != node);
}

/********* Pair Wise Merge *********/
//Pairwise merge all the trees in the root list
//***Note: tried many variations but only succeeded with below version
void FibonacciHeap::PairWiseMerge(Node *node)
{
    //Calculate the max degree a node can have
    int maxDegrees = ceil(log2(heapSize));
    Node *degArr[maxDegrees + 1] = {NULL};

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
                //Remove treeNode from root list
                (treeNode->prev)->next = treeNode->next;
                (treeNode->next)->prev = treeNode->prev;

                //if only one tree in heap
                if (node->next == node)
                {
                    //Link to self
                    treeNode->next = treeNode;
                    treeNode->prev = treeNode;
                }
                else //more than one
                {
                    //Replace node with treeNode
                    node->prev->next = treeNode;
                    node->next->prev = treeNode;
                    treeNode->next = node->next;
                    treeNode->prev = node->prev;
                }
                AddChild(treeNode, node);
                node = treeNode;
            }

            //Past attempt
            // //Remove treeNode from root list
            // if (node->count > treeNode->count)
            // {
            //     Node *temp = treeNode;
            //     treeNode = node;
            //     node = temp;
            // }
            // (treeNode->prev)->next = treeNode->next;
            // (treeNode->next)->prev = treeNode->prev;

            // //if only one tree in heap
            // if (node->next == node)
            // {
            //     //Link to self
            //     treeNode->next = treeNode;
            //     treeNode->prev = treeNode;
            // }
            // else //more than one
            // {
            //     //Replace node with treeNode
            //     node->prev->next = treeNode;
            //     node->next->prev = treeNode;
            //     treeNode->next = node->next;
            //     treeNode->prev = node->prev;
            // }
            // AddChild(treeNode, node);
            // node = treeNode;

            continue;
        }
        else //Add node to empty degree spot in array
            degArr[node->degree] = node;

        //Update maxNode as we merge the tree
        if (maxNode->count < node->count)
            maxNode = node;

        node = node->next;
    }
}

/********* Add Child *********/
//Merge the two nodes by making one the child of the other
void FibonacciHeap::AddChild(Node *parent, Node *child)
{
    //Change child pointers
    child->parent = parent;
    child->next = child;
    child->prev = child;

    //Link children and increase parent degrees
    parent->child = LinkTrees(child, parent->child);
    parent->degree = parent->degree + 1;
}

/********* Link Trees *********/
//Link the two nodes along their next/prev pointers and return larger node
Node *FibonacciHeap::LinkTrees(Node *nodeOne, Node *nodeTwo)
{
    //Null check both nodes
    if (nodeTwo == NULL)
        return nodeOne;

    if (nodeOne == NULL)
        return nodeTwo;

    //Link the two nodes and their lists
    nodeTwo->next->prev = nodeOne->prev;
    nodeOne->prev->next = nodeTwo->next;
    nodeTwo->next = nodeOne;
    nodeOne->prev = nodeTwo;

    //Compare counts, return larger node
    if (nodeTwo->count < nodeOne->count)
        return nodeOne;
    else
        return nodeTwo;
}

/********* Get Max *********/
int FibonacciHeap::GetMax()
{
    return maxNode->count;
}

/********* TEST METHODS *********/
void FibonacciHeap::Print()
{
    Print(maxNode, 0);
}

void FibonacciHeap::Print(Node *node, int depth)
{
    //Print out siblings
    Node *temp = node;

    do
    {
        //space based on depth
        for (int i = 0; i < depth; i++)
            cout << "  ";

        cout << temp->hashtag << endl;

        ChildPrint(temp, depth);

        temp = temp->next;

    } while (temp != node && temp != NULL);
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