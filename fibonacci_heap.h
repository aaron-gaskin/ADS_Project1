#include <iostream>
#include <string>
using namespace std;

//Node declaration
class Node {
    public:
        Node(int count, string hashtag);
        ~Node();
        Node* parent;
        Node* left;
        Node* right;
        Node* child;
        int degree;

        int count;
        string hashtag;
        bool cut;
};

class FibonacciHeap {
    public:
        FibonacciHeap();
        ~FibonacciHeap();
        Node* Insert(int tagCount);
        int GetMax();
        Node* RemoveMax();
        void IncreaseCount(Node* node, int addCount);
        void Merge(Node* otherHeap);

        //TEST method
        Node* Find(Node* node, int tagCount);


    private:
        Node* maxNode;
    
};