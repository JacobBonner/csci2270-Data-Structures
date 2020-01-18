/** CSCI 2270 - Homework 4
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */


#include <iostream>
using namespace std;


// Represents nodes of a linked list, which in this case are movies with an IMBD ranking, title, year, and quantity in stock
struct ListNode
{
    int rank;
    string title;
    int year;
    int quantity;
    ListNode* next;
};


// Represents nodes of a binary search tree, which include a letter to sort the nodes alphabetically, and a pointer to the head of the linked list of movies 
// starting with the node's letter
struct TreeNode
{
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    char letter;
    ListNode* listHead;
};


class MovieTree
{
    private:
        // Data members
        TreeNode* root;

        // INSERTING
        void split(string toSplit, char delimeter, string strArr[4]);
        void insertListNode(ListNode* toInsert, TreeNode* currentNode);
        void insertMovie(ListNode* newNode);
        bool readFile(char* fileName);

        // FINDING
        ListNode* searchList(ListNode* node, string movieName);
        void findMovie(string movie);

        // RENTING
        void rentMovie(string movieTitle);

        // PRINTING
        int displayMenu();
        void printList(ListNode* head);
        void printNode(TreeNode* node);
          
        // DELETING
        TreeNode* findMinimum(TreeNode* temp);
        TreeNode* findMaximum(TreeNode* temp);
        void deleteTreeNode(TreeNode* node);
        void deleteList(TreeNode* nodeBST);
        void postOrderDelete(TreeNode* node);
        void deleteMovie(string movieName);

        // COUNTING
        int countList(ListNode* head);
        int countNode(TreeNode* node);


        // EXTRA
        void printNodeLetter(TreeNode* node);


    public:
        MovieTree();
        ~MovieTree();
        void runProgram(char* filename);
};