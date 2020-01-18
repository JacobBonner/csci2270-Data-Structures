Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Recitation 3 Assignment - Stack Implementation with Doubly Linked List

What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.
        recitation3.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It reads a given text file line by line, follows different
            commands to perform from each line, and executes each command on a stack.
    The Program:
        The program that can be executed using these files creates a stack, takes commands from lines on a file, and either pushes given values onto the stack, pops the 
        top value off of the stack, or prints out what the top value of the stack is. After the whole file is read and all commands have been carried out on the stack,
        the values of teh stack are printed out from bottom to top, and then from top to bottom.
        
How:
    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the file to compile. For example: g++ -std=c++11 recitation3.cpp -o Recitation3
        
    Running the program:
        Then to run the program, the user would write the name of the executable as well as the name of the the text file they wish to use in the program.
        For example: ./Recitation3 stacktest1.txt