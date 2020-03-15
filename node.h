#include <iostream>
using namespace std;

class Node {
    public:
        Node* parent;
        Node* left;
        Node* right;
        Node* child;
        int degree;

        int count;
        String hashtag;
        bool cut;
};