#include <iostream>
#include "Stack.hpp"
using namespace std;


Stack :: Stack(){
    head = NULL;
    tail = NULL;
}


bool Stack :: isEmpty(){
    if(head == NULL){
        return true;
    }
    return false;
}


void Stack :: push(Node* tmp){
    Node* newNode = new Node;
    newNode->val = tmp->val;
    newNode->next = NULL;
    newNode->prev = tail;
    newNode->left = tmp->left;
    newNode->right = tmp->right;
    
    if(head == NULL){ // if the stack is empty
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
}


Node* Stack :: pop(){
    // Checks if the stack is empty
    if(head == NULL){
        return NULL;
    }

    // Stores the value of the tail node
    Node* temp = tail;

    if(head == tail){ // if there is only 1 node in the stack
        delete head;
        head = NULL;
        tail = NULL;
    }
    else{ // otherwise
        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
    }
    return temp;
}