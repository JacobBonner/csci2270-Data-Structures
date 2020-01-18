// Recitation 3 Assignment
// Author: Jake Bonner
// CSCI 2270 Summer 2019
// Recitation: 311

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Struct for a node to store the value, pointer to the next node, and pointer to the previous node
struct Node
{
    int value;
    Node* next;
    Node* prev;
};


// Class to represent a stack, where the head is the bottom of the stack, and the tail is the top
class DoublyLinkedList
{
    private:
        Node* head;
        Node* tail;

    public:

        // Initializes the stack as empty
        DoublyLinkedList(){
            head = NULL;
            tail = NULL;
        }

        // Adds a node with a given value to the top of the stack
        void push(int val){
            // Create new node to add and set its value, next, and prev
            Node* newNode = new Node;
            newNode->value = val;
            newNode->next = NULL;
            newNode->prev = tail;
            
            if(head == NULL){ // if the stack is empty
                head = newNode;
                tail = newNode;
            }
            else{
                tail->next = newNode;
                tail = newNode;
            }
             
        }

        // Removes the top node of the stack
        int pop(){

            // Checks if the stack is empty
            if(head == NULL){
                return -1;
            }

            // Stores the value of the tail node
            int temp = tail->value;

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

        // Prints the value on the top of the stack
        int peek(){
            if(tail == NULL){
                return -1;
            }

            return tail->value;
        }

        // Prints the stack out one value per line from bottom to top
        void printBottToTop(){

            // if(head == NULL){
            //     cout << "The stack is empty." << endl;
            // }

            Node* currentNode = head;
            while(currentNode!=NULL){
                cout << currentNode->value << endl;
                currentNode = currentNode->next;
            }
        }

        // Prints the stack out one value per line from top to bottom
        void printTopToBott(){

            // if(tail == NULL){
            //     cout << "The stack is empty." << endl;
            // }
            
            Node* currentNode = tail;
            while(currentNode!=NULL){
                cout << currentNode->value << endl;
                currentNode = currentNode->prev;
            }
        }

};

/**
 * Function Name: isolateNumbers
 * Purpose: to extract the number characters in a string and copy them into a new string
 * @ param line - a string that will have the character from 0-9 copied from it and placed in a new string
 * @ return newString - a string with only number characters 0-9
 */
string isolateNumbers(string line){
    string newString;
    for(int i=0; i<line.length(); i++){
        if(line[i] <= '9' && line[i] >= '0'){
            newString += line[i];
        }
    }
    return newString;
}


/**
 * Function Name: readFile
 * Purpose: to read a file line by line and perform different commands on a stack based on the information on each line
 * @ param fileName - the name of a file to open given as a string
 * @ param stack - a pointer to a DoublyLinkedList stack
 * @ return true if the file is opened, or false otherwise
 */
bool readFile(char* fileName, DoublyLinkedList* stack){
    // Declaration of local variables
    string line, val;

    cout << "\n";

    // Reading the file line by line
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            if(line.length() > 4){
                if(line.substr(0,4) == "push"){
                    // Isolating the number to push
                    val = isolateNumbers(line);
                    // Pushing the value on to the stack
                    stack->push(stoi(val));
                    cout << "pushed " << val << " onto stack" << endl;
                }
            }
            else if(line == "peek"){
                cout << stack->peek() << " is on the top of the stack" << endl;
            }
            else if(line == "pop"){
                cout << "popped " << stack->pop() << " off of stack" << endl;
            }
        }
        return true;
    }
    else{
        return false;
    }
}


int main(int argc, char* argv[]){
    // Initialization of a new stack
    DoublyLinkedList Stack;

    // Read the file and carry out the commands
    bool success = readFile(argv[1],&Stack);

    // Checks if the file was opened successfully
    if(success){
        Stack.printBottToTop();
        cout << "\n";
        Stack.printTopToBott();
    }
    else{
        cout << "ERROR: The file was not opened." << endl;
    }

    return 0;
}