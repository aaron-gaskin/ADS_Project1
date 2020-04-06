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
    if (node == NULL)
    {
        cout << "\nNode doesn't exist: IncreaseKey" << endl;
        return;
    }
    node->count = node->count + addCount;

    //Check if child->count is greater than parent->count
    if (node->parent != NULL && node->count > node->parent->count)
        CutNode(node);
    else if (node->count > maxNode->count)
        maxNode = node;

    ////TODO: perform cascade cut and check if new maxNode
}

/********* Cut node *********/
void FibonacciHeap::CutNode(Node *node)
{
    Node *parent = node->parent;

    if (node == NULL)
    {
        cout << "\nNode is null: CutNode" << endl;
        return;
    }

    //End if parent is NULL, root list reached
    if (parent == NULL)
        return;

    //Update sibling pointers and parent->child if necessary
    if (node->next != node)
    {
        if (parent->degree == 0)
        {
            cout << "\nMultiple children: " << parent->hashtag << " and " << node->hashtag << endl;
            Print(maxNode, 0);
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (parent->child == node)
            parent->child = node->next;
    }
    else //Only child of parent so NULL parent->child
    {
        if (parent->degree == 0)
        {
            cout << "\nOne child: " << parent->hashtag << " and " << node->hashtag << endl;
            Print(maxNode, 0);
        }

        parent->child = NULL;
    }

    // if (parent->degree == 0)
    // {
    //     cout << "\nHeapSize = " << heapSize << endl;
    //     cout << parent->hashtag << ": " << parent->degree << endl;
    //     if (node->next == node)
    //         cout << "one child" << endl;
    //     // if (parent->parent == NULL)
    //     //     cout << "parent: NULL" << parent->parent << endl;
    //     // if (parent->child == NULL)
    //     //     cout << "  Child: NULL" << parent->child << endl;
    //     Print(parent, 0);
    // }

    parent->degree = parent->degree - 1;

    // if (parent->degree == -1)
    //     cout << parent->hashtag << ": " << parent->degree << endl;

    //Reset node values then link to root list and update maxNode if needed
    node->parent = NULL;
    node->marked = false;
    node->next = node->prev = node;
    maxNode = LinkTrees(node, maxNode);

    CascadeCut(parent);
}

/********* Cascade Cut *********/
////TODO: Perform a cascde cut starting at input Node
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
////TODO: run removeMax n times then reinsert the removed maxes
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
    // cout << "\nRemoveMax" << endl;
    Node *oldMax = maxNode;

    //Null check
    if (maxNode == NULL)
        return NULL;

    //Check if maxNode is the only node
    else if (maxNode == maxNode->next && maxNode->child == NULL)
    {
        maxNode = NULL;
        return maxNode;
    }

    UnmarkChildren(maxNode->child);

    //Remove maxNode from the tree and link children to siblings if needed
    if (maxNode->next == maxNode)
    {
        //If no siblings, make child maxNode
        maxNode = maxNode->child;
        maxNode->parent = NULL;
    }
    else
    {
        //If siblings, link with maxNode children
        maxNode->next->prev = maxNode->prev;
        maxNode->prev->next = maxNode->next;
        maxNode = LinkTrees(maxNode->next, maxNode->child);
    }

    PairWiseMerge(maxNode);

    heapSize--;

    return oldMax;
}

/********* UnmarkChildren *********/
////TODO: test unmark
//Unmark node, siblings, and children
void FibonacciHeap::UnmarkChildren(Node *node)
{
    // cout << "\nUnmark children" << endl;
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

/********* Pair Wise Merge *********/
//Pairwise merge all the trees in the root list
void FibonacciHeap::PairWiseMerge(Node *node)
{
    // cout << "\nMerge" << endl;
    // cout << "\nMerge" << endl;
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
                // cout << "\nMergeWhile: degArr: node>" << endl;
                //Remove treeNode from root list

                ////TODO: node is referencing incorrect data
                //////    pointer was not properly assigned
                cout << endl
                     << node->degree << endl;
                // cout << "\nTreeNode = " << treeNode << endl;

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
            //degArr[node->degree] = node;
            ////TODO: check if continue is needed
            continue;
        }
        else //Add node to empty degree spot in array
            degArr[node->degree] = node;

        //Update maxNode as we merge the tree
        if (maxNode->count < node->count)
            maxNode = node;

        node = node->next;
    }
    // cout << "\nMerge 2.0" << endl;

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

/********* Add Child *********/
//Merge the two nodes by making one the child of the other
void FibonacciHeap::AddChild(Node *parent, Node *child)
{
    // cout << "\nAddChild" << endl;
    ////TODO:
    //Remove child from tree
    // child->prev->next = child->next;
    // child->next->prev = child->prev;

    //Change child pointers
    child->parent = parent;
    child->next = child;
    child->prev = child;

    //Link children and increase parent degrees
    // cout << "\nDegree = " << parent->degree << endl;
    parent->child = LinkTrees(child, parent->child);
    parent->degree = parent->degree + 1;
    if (parent->degree == -1)
        cout << "\nAddchild: " << parent->hashtag << endl;
    // cout << "\nDegree = " << parent->degree << endl;
    // cout << "\nAddChild 2.0" << endl;
}

/********* Link Trees *********/
//Link the two nodes along their next/prev pointers and return larger node
Node *FibonacciHeap::LinkTrees(Node *nodeOne, Node *nodeTwo)
{
    // cout << "\nLinkTrees" << endl;
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
//TEST methods
void FibonacciHeap::Print()
{
    cout << "\nStart Print" << endl;
    Print(maxNode, 0);
    cout << "\nEnd Print" << endl;
}

void FibonacciHeap::Print(Node *node, int depth)
{
    //Print out siblings
    Node *temp = node->next;

    //space based on depth
    for (int i = 0; i < depth; i++)
        cout << "  ";
    cout << node->hashtag << ": " << node->degree << ": " << node->count << endl;

    ChildPrint(node, depth);

    while (temp != node && temp != NULL)
    {

        //space based on depth
        for (int i = 0; i < depth; i++)
            cout << "  ";

        cout << temp->hashtag << ": " << temp->degree << ": " << temp->count << endl;

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