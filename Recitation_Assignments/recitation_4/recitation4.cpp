// Recitation 4 Assignment
// Author: Jake Bonner
// CSCI 2270 Summer 2019
// Recitation: 311

#include <iostream>
#include <fstream>
#include <string>
#include "Stack.hpp"
#include "TreeTraversal.hpp"
using namespace std;


/**
 * Function Name: readFile
 * Purpose: read a file of numbers and fill a binary seaech tree
 * @ param fileName - the name of the file to read numbers from and insert into the Binary Search Tree
 * @ param Tree - a binary search tree object to hold the numbers in the file
 * @ return nodeCount - the number of nodes in the binary search tree after reading the entire file
 */
int readFile(char* fileName, TreeTraversal* Tree){
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){
        string line;
        bool isNumber;
        int nodeCount = 0;
        while(getline(myfile,line)){

            // check that the line is a valid number
            isNumber = true;
            for(int i=0; i<line.length(); i++){
                if(line[i]>'9' || line[i]<'0'){
                    isNumber = false;
                }
            }
            if(line.length() > 1 && line[0] == '0'){
                isNumber = false;
            }

            // if the current line is a number
            if(isNumber){
                
                // add the value to the Binary Search Tree
                Tree->insertNodeBST(stoi(line));
                nodeCount++;
            }
        }
        return nodeCount;
    }
    else{
        return -1;
    }
}


int main(int argc, char* argv[]){
    // Initialize Binary Search Tree
    TreeTraversal searchTree;

    // Read the given text file and fill the Binary Search Tree, and return the number of nodes that were made to create the tree
    int numNodes = readFile(argv[1],&searchTree);

    // If the file was not opened
    if(numNodes == -1){
        cout << "The file was not opened." << endl;
    }
    else{ // print out the number of nodes and the tree values in order
        cout << "Built the BST with " << numNodes << " nodes" << endl;
        cout << "In-order Traversal: ";
        searchTree.inOrderTreeTraversal();
    }
    
    return 0;
}