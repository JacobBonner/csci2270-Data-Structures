#include <iostream>
#include "Stack.hpp"
#include "TreeTraversal.hpp"
using namespace std;

// Initializes an empty Binary Search Tree
TreeTraversal :: TreeTraversal(){
    root = NULL;
}


/**
 * Function Name: inOrderTreeTraversal
 * Purpose: print out the node values of a binary search in order from smallest to largest
 * @ param none
 * @ return none
 */
void TreeTraversal :: inOrderTreeTraversal(){
    if(root == NULL){
        cout << "The Binary Search Tree is empty." << endl;
    }
    else{
        Stack newStack; 
        Node* temp = root;        

        // Go as far left as possible in the tree, pushing nodes onto the stack as they are traversed
        while(temp != NULL){
            newStack.push(temp);
            if(temp->left != NULL){
                temp = temp->left;
            }else{
                break;
            }
        }

        // As long as the stack is not empty, pop the current top value of the stack, traverse right one, and continue to go left as far as possible
        while(!newStack.isEmpty()){
            temp = newStack.pop();
            cout << temp->val;
            temp = temp->right;
            while(temp != NULL){
                newStack.push(temp);
                temp = temp->left;
            }
            if(!newStack.isEmpty()){
                cout << ", ";
            }
        }
    }
}


void TreeTraversal :: insertNodeBST(int key){
    // Create new node and set the data for it
    Node* toAdd = new Node;
    toAdd->parent = NULL;
    toAdd->left = NULL;
    toAdd->right = NULL;
    toAdd->val = key;

    if(root == NULL){ // if BST is emtpy
        root = toAdd;
    }
    else{ // BST is already created
        Node * temp = root;
        Node * parent;
        while (temp != NULL) {
            parent = temp;
            if (key < temp->val)
                temp = temp->left;
            else 
                temp = temp->right;
        }
        toAdd->parent = parent;
        if (key < parent->val)
            parent->left = toAdd;
        else
            parent->right = toAdd;
    } 
}
