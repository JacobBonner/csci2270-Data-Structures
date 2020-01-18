/** CSCI 2270 - Recitation Assignment 6 
 * Author: Jake Bonner
 * Section: 310 / 311
 * Instructor: Christopher Godley
 * TA: Andrew Guttman
 */ 

#include<iostream>

using namespace std;

struct Node{
	int data;
	Node* left;
	Node* right;
	Node* parent;
	Node* secondLastPtr;

	Node(int value){
		data = value;
		left = NULL;
		right = NULL;
		parent = NULL;
		secondLastPtr = NULL;
	}
};

class MinHeap{
	private:
		Node* root;
		Node* lastPtr;
	public:
		MinHeap();
		int getMin();
		Node* getRoot();
		void insert(int);
		void removeMin();
		void printHeap(Node*);
		void setLastPtr(Node*);

};

MinHeap::MinHeap(){
	root = NULL;
	lastPtr = NULL;
}

Node* MinHeap::getRoot(){
	return root;
}

void MinHeap::setLastPtr(Node* node){
	if(node->parent == NULL){
		lastPtr = node;
		while(lastPtr->left != NULL){
			lastPtr = lastPtr->left;
		}
	} else if(node->parent->left == node){
		lastPtr = node->parent->right;
		while(lastPtr->left != NULL){
			lastPtr = lastPtr->left;
		}
	} else if(node->parent->right == node){
		setLastPtr(node->parent);
	}
}


void swapData(Node* first, Node* second){
	int temp = first->data;
	first->data = second->data;
	second->data = temp;
}

void minHeapifyDown(Node* node){
	if(node == NULL || node->parent == NULL){
		return;
	}

	// if the data of the prent node is greater than the data of the current node, swap the data of the two, and call the function again with the parent
	if(node->data < node->parent->data){
		swapData(node,node->parent);
		minHeapifyDown(node->parent);
	}
}

void minHeapifyUp(Node* node){
	if(node == NULL || node->left == NULL){
		return;
	} 
	Node* small = node->left;
	if(node->right != NULL && small->data > node->right->data){
		small = node->right;
	}
	if(small->data < node->data){
		swapData(node, small);
		minHeapifyUp(small);
	}
}


int MinHeap::getMin(){
	return root->data;
}

void MinHeap::insert(int data){

	cout << "Inserting: " << data;

	Node* newNode = new Node(data);
	if(root == NULL){
		root = newNode;
		lastPtr = root;
	} else if(lastPtr->left == NULL){
		lastPtr->left = newNode;
		lastPtr->left->parent = lastPtr;
		minHeapifyDown(lastPtr->left);
	} else {
		lastPtr->right = newNode;
		lastPtr->right->parent = lastPtr;
		minHeapifyDown(lastPtr->right);
		Node* secondLastPtr = lastPtr;
		setLastPtr(lastPtr);
		lastPtr->secondLastPtr = secondLastPtr;
	}
}

void MinHeap::printHeap(Node* node){
	
	// if(node == NULL){
	// 	return;
	// }

	// cout << node->data << " ";

	// if(node->left != NULL && node->right != NULL){
	// 	if(node->left->data < node->right->data){
	// 		printHeap(node->left);
	// 		printHeap(node->right);
	// 	}
	// 	else{
	// 		printHeap(node->right);
	// 		printHeap(node->left);
	// 	}
	// }
	// else if(node->left == NULL && node->right != NULL){
	// 	printHeap(node->right);
	// }
	// else if(node->right == NULL && node->left != NULL){
	// 	printHeap(node->left);
	// }

	if(!node) return;

	if(node->left) printHeap(node->left);

	cout << node->data << " ";

	if(node->right) printHeap(node->right);

}

void MinHeap::removeMin(){
	if(root == NULL){
		cout << "Empty Heap" << endl;
		return;
	}
	if(root->left == NULL && root->right == NULL){
		lastPtr = NULL;
		root = NULL;
	} else {
		if(lastPtr->right != NULL){
			swapData(lastPtr->right, root);
			lastPtr->right = NULL;
			minHeapifyUp(root);
		} else if(lastPtr->left != NULL){
			swapData(lastPtr->left, root);
			lastPtr->left = NULL;
			minHeapifyUp(root);
		} else {
			lastPtr = lastPtr->secondLastPtr;
			removeMin();
		}
	}
}

int main(){
	MinHeap mh;
	mh.insert(3);
	mh.insert(17);
	mh.insert(99);

	cout << "print heap" << endl;
	Node* node = mh.getRoot();
	mh.printHeap(node);
	cout << endl;
	
	cout << "remove min" << endl;
	mh.removeMin();
	cout << "print after delete" << endl;
	node = mh.getRoot();
	mh.printHeap(node);
	cout << endl;

	cout << "remove min" << endl;
	mh.removeMin();
	cout << "print after delete" << endl;
	node = mh.getRoot();
	mh.printHeap(node);
	cout << endl;

	cout << "remove min" << endl;
	mh.removeMin();
	cout << "print after delete" << endl;
	node = mh.getRoot();
	mh.printHeap(node);
	cout << endl;
}