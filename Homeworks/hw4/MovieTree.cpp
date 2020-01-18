/** CSCI 2270 - Homework 4
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream>
#include <fstream>
#include <string>
#include "MovieTree.hpp"


//////////////////// CONSTRUCTOR/DESTRUCTOR ////////////////////

MovieTree :: MovieTree(){
    root = NULL;
}

MovieTree :: ~MovieTree(){
    // Delete the entire BST and all Linked Lists
    postOrderDelete(root);
}

///////////////////////////////////////////////////////////////


//////////////////////////////////////// INSERTING ////////////////////////////////////////

/**
 * Function Name: split
 * Purpose: splits a string on a given delimeter
 * @ param toSplit - a string to be split on a given delimeter
 * @ param delimeter - the character to split the given string on
 * @ param arr - an array of strings that will be filled with the split segments of the given string
 * @ return none
 */
void MovieTree :: split(string toSplit, char delimeter, string arr[4]){
    string word;
    toSplit += delimeter;
    int j=0;
    for(int i=0; i<toSplit.length(); i++){
        if(toSplit[i] == delimeter){
            if(word.length() == 0) continue;
            arr[j] = word;
            j++;
            word = "";
        }
        else{
            word += toSplit[i];
        }
    }
}

/**
 * Function Name: insertListNode
 * Purpose: insert a node in a linked list of movies that branches from a BST node
 * @ param toInsert - the node that is to be inserted into the linked list
 * @ param currentNode - the BST node that points to the head of the linked list
 * @ return none
 */
void MovieTree :: insertListNode(ListNode* toInsert, TreeNode* currentNode){

    // Set the current pointer equal to the head, and declare a pointer to store the previous node
    ListNode* temp = currentNode->listHead;
    ListNode* prev = NULL;

    // Iterate over the linked list that the currentNode points to
    while(temp != NULL){
        
        // Check if the toInsert node's movie title alphabetically comes before the current node's movie title in the linked list 
        bool before = true;
        for(int i=1; i<(toInsert->title).length(); i++){
            if((toInsert->title)[i-1] == (temp->title)[i-1]){
                if((toInsert->title)[i] > (temp->title)[i]){
                    before = false;
                    break;
                }
                else if((toInsert->title)[i] < (temp->title)[i]){
                    break;
                }
            }
        }

        // If the toInsert node's title alphabetically comes before the current node's title
        if(before){
            // Set the next of the toInsert node equal to the current node in the list
            toInsert->next = temp;

            // Set the previous node's next equal to the node to be inserted, as long as the previous node isn't NULL
            if(prev != NULL){
                prev->next = toInsert;
            }

            // If the current node is equal to the head of the list that the BST Node points to, then set the new head equal to the toInsert node
            if(temp == currentNode->listHead){
                currentNode->listHead = toInsert;
            }

            break;
        }
        else{ // if the toInsert ndoe does not coem before the current node alphabetically
            // If there are no more movies to compare to in the linked list, then the node being inserted goes at the end of the list
            if(temp->next == NULL){
                temp->next = toInsert;
                break;
            } 

            // Set the previous node equal to the current node, so that on the next iteration it will point to the node that is before the next temp
            prev = temp;
            temp = temp->next;
        }
    }
}

/**
 * Function Name: insertMovie
 * Purpose: insert a given movie into a Binary Search Tree
 * @ param movieNode - a linked list node corresponding to a movie read from a text file
 * @ return none
 */
void MovieTree :: insertMovie(ListNode* movieNode){

    // Create new BST node and set the data for it
    TreeNode* toAdd = new TreeNode;
    toAdd->parent = NULL;
    toAdd->left = NULL;
    toAdd->right = NULL;
    toAdd->letter = (movieNode->title)[0];
    toAdd->listHead = movieNode;

    // Insert the BST node into the tree
    if(root == NULL){ // if BST is emtpy
        root = toAdd;
    }
    else{ // BST is already created
        TreeNode * temp = root;
        TreeNode * parent;
        while (temp != NULL) {
            parent = temp;

            // If the letter of the node being inserted is the same as the letter of the current node in comparison, do not add the TreeNode to the BST
            if(toAdd->letter == temp->letter){
                break;
            }
            if (toAdd->letter < temp->letter)
                temp = temp->left;
            else 
                temp = temp->right;
        }

        // If temp does not equal NULL, i.e. if the letter of the TreeNode being inserted already existed in the BST
        // Add the movieNode to the linked list of movies that temp points to
        if(temp != NULL){
            insertListNode(movieNode, temp); 
        }
        else{ // otherwise, set the pointers of the node being added to the BST
            toAdd->parent = parent;
            if (toAdd->letter < parent->letter)
                parent->left = toAdd;
            else
                parent->right = toAdd;
        }
    }
}

/**
 * Function Name: readFile
 * Purpose: read a text file of movies and create a binary search tree based on alphabetical order
 * @ param fileName - the name of the file entered by the user in the command line
 * @ return a boolean value to indicate whether or not the file was opened
 */
bool MovieTree :: readFile(char* filename){
    ifstream myfile;
    myfile.open(filename);
    if(myfile.is_open()){
        string line;
        string lineArr[4];
        while(getline(myfile,line)){
            split(line,';',lineArr);
            if(stoi(lineArr[3]) != 0){
                // Create a new linked list node and set the data members
                ListNode* newMovie = new ListNode;
                newMovie->rank = stoi(lineArr[0]);
                newMovie->title = lineArr[1];
                newMovie->year = stoi(lineArr[2]);
                newMovie->quantity = stoi(lineArr[3]);
                newMovie->next = NULL;
                
                // Insert the node/movie into the BST
                insertMovie(newMovie);
            }
        }
        return true;
    }
    else{
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// FINDING ////////////////////////////////////////

/**
 * Function Name: searchList
 * Purpose: search a linked list for a given node and return the node
 * @ param 
 * @ param
 * @ return either a pointer to the movie that was being searched for, or NULL if the movie was not found in the linked list
 */
ListNode* MovieTree :: searchList(ListNode* startNode, string movieName){
    ListNode* curr = startNode;
    while(curr != NULL){
        if(curr->title == movieName){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

/**
 * Function Name: findMovie
 * Purpose: search a BST of movies to find a given movie. Print out information about the movie if it is found, or print "Movie not found." otherwise
 * @ param movieTitle - the title of the movie tthat is being searched for, entered by the user
 * @ return none
 */
void MovieTree :: findMovie(string movieTitle){
    TreeNode* temp = root;
    ListNode* foundMovie;
    while(temp != NULL){
        if(movieTitle[0] == temp->letter){
            // Search the linked list that is pointed to by the current BST node and return the appropriate value
            foundMovie = searchList(temp->listHead, movieTitle);

            // If the movie is found in the list
            if(foundMovie != NULL){
                cout << "\nMovie Info:" << endl;  
                cout << "===========" << endl;
                cout << "Ranking:" << foundMovie->rank << endl;
                cout << "Title:" << foundMovie->title << endl;
                cout << "Year:" << foundMovie->year << endl;
                cout << "Quantity:" << foundMovie->quantity << endl; 
                break;
            }
            else{ // otherwise
                temp = NULL;
            }
        }
        else if(movieTitle[0] < temp->letter){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }

    // if the movie was not found
    if(temp == NULL){
        cout << "\nMovie not found." << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// RENTING ////////////////////////////////////////

/**
 * Function Name: rentMovie
 * Purpose: search a BST of movies for a given movie and rent it out to the user if it is found, i.e. subtract 1 from the quantity of the given movie in stock
 * @ param movieTitle - the title of the movie the user wishes to rent
 * @ return none
 */
void MovieTree :: rentMovie(string movieTitle){
    TreeNode* temp = root;
    ListNode* foundMovie;
    while(temp != NULL){
        if(movieTitle[0] == temp->letter){
            // Search the linked list that is pointed to by the current BST node and return the appropriate value
            foundMovie = searchList(temp->listHead, movieTitle);

            // If the movie is found in the list
            if(foundMovie != NULL){
                foundMovie->quantity = (foundMovie->quantity) - 1;
                cout << "\nMovie has been rented." << endl;
                cout << "\nMovie Info:" << endl;
                cout << "===========" << endl; 
                cout << "Ranking:" << foundMovie->rank << endl;
                cout << "Title:" << foundMovie->title << endl;
                cout << "Year:" << foundMovie->year << endl;
                cout << "Quantity:" << foundMovie->quantity << endl;

                // Delete the movie if the quantity reaches 0
                if(foundMovie->quantity == 0){
                    deleteMovie(movieTitle);
                }

                break;
            }
            else{ // otherwise
                temp = NULL;
            }
        }
        else if(movieTitle[0] < temp->letter){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }

    // if the movie is not found in the list
    if(temp == NULL){
        cout << "\nMovie not found." << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// PRINTING ////////////////////////////////////////

/**
 * Function Name: displayMenu
 * Purpose: display a menu to the user that allows them to choose how to run the program
 * @ param none
 * @ return userChoice - the number corresponding to the user's choice
 */
int MovieTree :: displayMenu(){
    cout << "\n======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl; 

    string userChoice;
    cin >> userChoice;
    
    // if the length of the user's input is greater than 1, or if the user's input is not between 0 and 7
    if(userChoice.length() > 1 || !(userChoice[0]>'0' && userChoice[0]<'7')){
        return 0;
    }
    else{
        return stoi(userChoice);
    }
}

/**
 * Function Name: printList
 * Purpose: for all nodes in a linked list of movies: print the movie name and quantity in stock
 * @ param headOfList - a pointer to the head of the linked list that is being traversed
 * @ return none
 */
void MovieTree :: printList(ListNode* headOfList){
    ListNode* temp = headOfList;
    while(temp != NULL){
        cout << "Movie: " << temp->title << " " << temp->quantity << endl;
        temp = temp->next;
    }
}

/**
 * Function Name: printNode
 * Purpose: print all of the contents of a BST of linked lists, which in this case is every movie title and its quantity in the BST
 * @ param node - a given BST node where the printing will start from (usually the root)
 * @ return none
 */
void MovieTree :: printNode(TreeNode* node){
    // Check valid input
    if(node == NULL) return;

    // print left sub tree
    if(node->left != NULL){
        printNode(node->left);
    }

    // print linked list of movies for current tree node
    printList(node->listHead);

    // print right sub tree
    if(node->right != NULL){
        printNode(node->right);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// DELETING ////////////////////////////////////////

/**
 * Function Name: findMinimum
 * Prupose: finds the node with the minimum value of a sub tree
 * @ param temp - the ndoe where the searching process for the minimum starts
 * @ return temp - the node that is the minimum
 */
TreeNode* MovieTree :: findMinimum(TreeNode* temp){
    if(temp == NULL) return NULL;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

/**
 * Function Name: findMaximum
 * Prupose: finds the largest node in the left subtree of the given node
 * @ param temp - the node where the sub tree starts
 * @ return the node that holds the maximum value in the sub tree
 */
TreeNode* MovieTree :: findMaximum(TreeNode* temp){
    if(temp == NULL) return NULL;
    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

/** 
 * Function Name: deleteTreeNode
 * Purpose: delete a node from a Binary Search Tree
 * @ param node - the node that is being deleted
 * @ return none
 */
void MovieTree :: deleteTreeNode(TreeNode* node){
    // if the tree is empty
    if(node == NULL){
        return;
    }
    
    TreeNode *child, *parent, *leftChild, *rightChild, *min, *max;

    if(node->left == NULL && node->right == NULL){ // no children
        if(node == root){
            root = NULL;
        }
        else{
            // check if the letter of the node to be deleted is greater or less than the value of the parent
            if(node->letter < node->parent->letter){
                node->parent->left = NULL;
            }
            else{
                node->parent->right = NULL;
            }
        }
    }
    else if(node->left == NULL || node->right == NULL){ // one child - left OR right
        parent = node->parent;

        if(node->left != NULL){
            child = node->left;
        }
        else{
            child = node->right;
        }

        if(node == root){
            root = child;
            //root->parent = NULL;
        }
        else{
            if(node->letter < parent->letter){
                parent->left = child;
            }
            else{
                parent->right = child;
            }
            child->parent = parent;
        }
    }
    else{ // Two Children

        // root
        if(node == root){
            max = findMaximum(node->left);
            max->left->parent = max->parent;
            max->parent->right = max->left;
            max->left = root->left;
            max->right = root->right;
            max->parent = NULL;
            root = max;

        }
        else{
            parent = node->parent;
            leftChild = node->left;
            rightChild = node->right;
            min = findMinimum(rightChild);
            if(min == rightChild){
                if(node->letter < parent->letter){ // left
                    parent->left = min;
                    min->parent = parent;
                    min->left = leftChild;
                    min->left->parent = min;
                }
                else{ // right
                    parent->right = min;
                    min->parent = parent;
                    min->left = leftChild;
                    min->left->parent = min;
                }
            }
            else{
                min->parent->left = min->right;
                if(min->right){
                    min->right->parent = min->parent;
                }
                min->left = leftChild;
                min->right = rightChild;
                min->parent = parent;
                leftChild->parent = min;
                rightChild->parent = min;

                if(node->letter < parent->letter){ // left
                    parent->left = min;
                }
                else{ // right
                    parent->right = min;
                }
            }
        }
    }

    delete node;
}

/**
 * Function Name: deleteList
 * Purpose: delete all nodes of a linked list starting at the head
 * @ param nodeBST - the BST node that points to the linked list that will be deleted
 * @ return none
 */
void MovieTree :: deleteList(TreeNode* nodeBST){
    ListNode* temp = nodeBST->listHead;
    ListNode* toDelete;
    while(temp != NULL){
        toDelete = temp;
        cout << "Deleting: " << toDelete->title << endl;
        temp = temp->next;
        delete toDelete;
    }
    nodeBST->listHead = temp;
    delete temp;
}

/** 
 * Function Name: postOrderDelete
 * Purpose: delete all of the linked lists and nodes in a BST of linked lists
 * @ param node - the node where the traversing and deleting will start
 * @ return none
 */
void MovieTree :: postOrderDelete(TreeNode* node){
    if(node == NULL) return;
    
    if(node->left != NULL){
        postOrderDelete(node->left);
    }

    deleteList(node);
    deleteTreeNode(node);

    if(node->right != NULL){
        postOrderDelete(node->right);
    }
}

/**
 * Function Name: deleteMovie
 * Purpose: delete a given movie from a BST of movies
 * @ param movieName - the title of the movie the user enters
 * @ return none
 */
void MovieTree :: deleteMovie(string movieName){
    TreeNode* temp = root;
    ListNode* foundMovie;
    while(temp != NULL){
        if(movieName[0] == temp->letter){
            // Search the linked list that is pointed to by the current BST node and return the appropriate value
            foundMovie = searchList(temp->listHead, movieName);

            // If the movie is found in the linked list
            if(foundMovie != NULL){

                // Delete the movie
                if(foundMovie == temp->listHead){
                    temp->listHead = foundMovie->next;
                }
                else{
                    ListNode* curr = temp->listHead;
                    ListNode* prev = NULL;
                    while(curr != NULL){
                        if(curr == foundMovie){
                            prev->next = curr->next;
                        }
                        prev = curr;
                        curr = curr->next;
                    }
                }

                delete foundMovie;

                // If the deleted movie was the last movie in the TreeNode, delete the node
                if(temp->listHead == NULL){
                    deleteTreeNode(temp);
                }

                break;
            }
            else{
                temp = NULL;
            }
        }
        else if(movieName[0] < temp->letter){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }

    // if the movie was not found in the linked list
    if(temp == NULL){
        cout << "\nMovie not found." << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// COUNTING ////////////////////////////////////////

/**
 * Function Name: countList
 * Purpose: count the number of nodes (movies) in a linked list
 * @ param head - a pointer to the head of the linked list that is being counted
 * @ return count - the number of nodes in the linked list
 */
int MovieTree :: countList(ListNode* head){
    int count = 0;
    ListNode* temp = head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

/**
 * Function Name: countNode
 * Purpose: count the number of nodes in all of the linked lists that branch from every Tree node in the BST (count all of the movies)
 * @ param node - the BST node from which teh counting will start (the root most likely)
 * @ return count - the total number of unique movies in the entire BST of linked lists
 */
int MovieTree :: countNode(TreeNode* node){
    // If the BST is empty
    if(node == NULL) return -1;

    // Count the number of movies branching from the current node
    int count = countList(node->listHead);

    // Count the number of movies in the left sub tree
    if(node->left != NULL){
        count += countNode(node->left);
    }

    // Count the number of movies in the right sub tree
    if(node->right != NULL){
        count += countNode(node->right);
    }

    return count;
}

//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// EXTRA ////////////////////////////////////////

/**
 * Function Name: printNodeLetter
 * Purpose: print the letters corresponding to each node in a BST
 * @ param node - the starting node for traversal
 * @ return none
 */
void MovieTree :: printNodeLetter(TreeNode* node){
    if(node == NULL) return;

    if(node->left){
        printNodeLetter(node->left);
    }

    cout << node->letter << " ";

    if(node->right){
        printNodeLetter(node->right);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////// RUNNING THE PROGRAM ////////////////////////////////////////

/**
 * Function Name: runProgram
 * Purpose: runs the entire program that the MovieTree class is built to carry out
 * @ param none
 * @ return none
 */
void MovieTree :: runProgram(char* fileName){
    // Read the file given by the user and fill the binary search tree
    bool success = readFile(fileName);

    // Check if the file was opened successfully
    if(!success){
        cout << "The file was not opened." << endl;
    }
    else{
        // Local variables to store user input fo finding, renting, or deleting a movie
        string findMovieName, rentMovieName, deleteMovieName;

        // Display the initial menu to the user
        int userChoice = displayMenu();

        // Ensure that the user's input is a valid number between 1 and 6
        while(!userChoice){
            cout << "Please enter a number between 1 and 6 corresponding to your choice." << endl;
            userChoice = displayMenu();
        }

        // continue displaying the menu and running the program until the user decides to quit
        while(userChoice != 6){

            // test the user's input number against the different menu options, and call different functions accordingly
            switch(userChoice){
                case 1: // Find a movie
                    cout << "Enter title: " << endl;
                    cin.ignore();
                    getline(cin,findMovieName);
                    findMovie(findMovieName);

                break;

                case 2: // Rent a movie
                    cout << "Enter title: " << endl;
                    cin.ignore();
                    getline(cin,rentMovieName);
                    rentMovie(rentMovieName);

                break;

                case 3: // Print the inventory
                    if(!root){
                        cout << "\nNo movies in stock." << endl;
                    }
                    else{
                        cout << "\n";
                        printNode(root);
                    }
                    

                break;

                case 4: // Delete a movie
                    cout << "Enter title: " << endl;
                    cin.ignore();
                    getline(cin,deleteMovieName);
                    deleteMovie(deleteMovieName);

                break;

                case 5: // Count the movies
                    int movieCount = countNode(root);
                    cout << "Tree contains: " << movieCount << " movies." << endl;

                break;

            }

            // display the menu and ask the user for input, and continue to do so if their input is invalid
            
            userChoice = displayMenu();
            while(!userChoice){
                cout << "Please enter a number between 1 and 6 corresponding to your choice." << endl;
                userChoice = displayMenu();
            }
        }

        cout << "Goodbye!\n" << endl;
        // Destructor will delete the entire tree and all linked lists
    }
}
//////////////////////////////////////////////////////////////////////////////////////////