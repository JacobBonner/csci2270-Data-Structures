#include <iostream>
using namespace std;


struct Node
{
    int val; // value in both BST and Stack
    Node* parent; // parent pointer in BST
    Node* left; // left pointer in BST
    Node* right; // right ponter in BST
    Node* next; // next pointer in stack
    Node* prev; // previous pointer in stack
};


class Stack
{
    private:
        Node* head; 
        Node* tail;

    public:
        Stack();
        void push(Node* node);
        Node* pop();
        bool isEmpty();
};