Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Homework 1 - Community Garage Sale

What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.
        assignment1.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It reads a given text file, evaluates
            and stores certain information from the file in an array, deletes elements from the array, and displays certain contents of the array.
    The Program:
        The program that can be executed using these files simulates a community message board that monitors items wanted and items for sale and looks for matches. 
        When a match is found, for example if a bike is for sale and someone else wants it for more or the same price, then the item is removed from the meassage board. 
        First, the program reads a text file given by the user, evaluates the information on each line one by one, and stores the information from each line in an array 
        if the item has no match. If the item has a match, it will not be added to the array, and the item that it matched with will be deleted from the array. As 
        matches are found, the program will display the type of item that was sold, as well as the price. Once the whole file has been read end evaluated, the type, 
        status, and price of remaining items in the array will be displayed, i.e. the items that are still for sale that no one wanted, or the items that were wanted 
        but were not for sale. FInally, the number of items that were sold and the number of items that remain in the message board are displayed.
How:
    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the file to compile. For example: g++ -std=c++11 assignment1.cpp -o Assignment1
        
    Running the program:
        Then to run the program, the user would write the name of the executable as well as the name of the the text file they wish to use in the program.
        For example: ./Assignment garageSale.txt

    Compiling and running the program in the afformentioned manner will successfully run the given program, and it will execute and display as described above.