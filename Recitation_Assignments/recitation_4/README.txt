Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Recitation 4 Assignment -  Non-recursive in-order tree traversal

What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.
        recitation4.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It creates a Binary Search Tree by reading a text file of
            numbers, and then calls a function to print out the numbers in the BST in order from smallest ot largest (non-recursively).
        TreeTraversal.hpp:
            Contains the class definition of the TreeTraversal class, which is used to build and print out the values in a Binary Search Tree.
        TreeTraversal.cpp:
            Contains the implementation and definition of the member functions of the TreeTraversal class.
        Stack.hpp:
            Contains the class definition of the Stack class, which is used to push and pop nodes of a BST such as to print out the valus in order from smallest to 
            largest.
        Stack.cpp:
            Contains the implementation and definition of the member functions of the Stack class.

    The Program:
        The program that can be executed using these files creates a binary search tree (BST) based on numbers in a text file, and then uses a stack to print out the 
        values stored in the nodes of the BST in order from smallest to largest.

How:
    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the file in which the program runs, as well as the files where the functions of the classes 
        are implemented. 
        For example: g++ -std=c++11 TreeTraversal.cpp Stack.cpp recitation4.cpp -o Recitation4
        
    Running the program:
        Then to run the program, the user would write the name of the executable as well as the name of the the text file they wish to use to create the Binary Search
        Tree.
        For example: ./Assignment3 input1.txt