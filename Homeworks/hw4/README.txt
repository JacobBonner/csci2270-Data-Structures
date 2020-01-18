Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Homework 4 - Binary Search Trees and Linked Lists

What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.
        Assignment4.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It utilizes the MovieTree class to read a text file of
            movies and create a binary search tree of linked lists. It then allows the user to pick from an interface of options to edit the movies that exist in the 
            tree, such as renting the movies, finding a movie, and deleting movies.
        MovieTree.hpp:
            The purpose of this file is to define the class and declare its data members and functions that will be used to implement the BST of Linked Lists.
        MovieTree.cpp:
            The purpose of this file is to define and implement the functions of the MovieTree class.
        Movie.txt:
            The file for the user to read that contains the list of movies used to create the BST.
        
    The Program:
        The program that can be executed using these files simulates an online movie service by storing movies in a Binary Search Tree (BST) ordered by the first letter 
        in the movie title, and then a singly linked list for each node in the BST that includes the information for each movie. For each of the movies in the store’s 
        inventory, the following information is kept: 
            - IMDB ranking  
            - Title  
            - Year released 
            - Quantity in stock 

        The user will enter a file name where each line is a different movie, and the program will read the file and create a binary search tree of linked lists
        organized alphabetically. Then the program will continue to display a menu to the user until they select the option to quit. Until they quit, the user is able to
        search for a movie, rent a movie, print the inventory, delete a movie, or count the movies.

How:
    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the file in which the program runs, as well as the file where the functions of the class 
        are implemented. 
        For example: g++ -std=c++11 MovieTree.cpp Assignment4.cpp -o Assignment4
        
    Running the program:
        Then to run the program, the user would write the name of the executable as well as the name of a text file to use to build the BST.
        For example: ./Assignment4 Movies.txt