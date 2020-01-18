Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Homework 3 - Communication Between Towers

What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.
        assignment3.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It creates an interface that allows a user to build a 
            network of cities through a linked list, and gives them the option to print the newtwork path, transmit a message across the network, add a new city, 
            delete a city, or clear the network.
        CommunicationNetwork.hpp:
            This file contains the class definition of the Communication Network class that is used in assignment3.cpp. The data memmbers and functions are utilized
            to create and edit the linked list network of cities.
        CommunicationNetwork.cpp:
            This file is the implementation and definition of the functions in the Communication Network class. 
        messageIn.txt:
            The purpose of this file is to give the user a text file for them to write a message in that they can then tranmit across the linked list city network.

    The Program:
        The program that can be executed using these files simulates a communications network using a linked list. Each node in the linked list represents a city, 
        which are all implemented as a struct with a name, a pointer connecting each city to the next city in the network and the previous city in the network, and 
        a place to store the message being sent. The program provides the user the capability to update the newtork in various ways and transmit messages across the
        list. The following interface is continually shown to the user until they decide to quit, and exit the program:

            ======Main Menu======
            1. Build Network
            2. Print Network Path
            3. Transmit Message Coast-To-Coast-To-Coast
            4. Add City
            5. Delete City
            6. Clear Network
            7. Quit

        Below is a description of each option:

        1. Build Network 
            Creates the initial network of cities and displays the city names to the user.

        2. Print Network Path  
            Prints out the name of each city in the linked list in order from head to tail.

        3. Transmit Message Coast-To-Coast-To-Coast
            Reads word by word from a text file and transmits the message starting at the beginning of the network to the end of the network, and then back to the 
            beginning.

        4. Add City
            Allows the user to add a city to the network. It prompts the user for a new city name, and also the name of a previous city to add after.
            Entering "First" for the prevous city name will add the city to the head, and entering "" will add the city to the tail.

        5. Delete City
            Allows the user to remove a city from the network. It prompts the user for the name of the city they wish to delete from the linked list.

        6. Clear Network
            Allows the user to delete all cities in the network starting at the head city.

        7. Quit 
            Allows the user to exit the program. 

How:
    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the file in which the program runs, as well as the file where the functions of the class 
        are implemented. 
        For example: g++ -std=c++11 CommunicationNetwork.cpp assignment3.cpp -o Assignment3
        
    Running the program:
        Then to run the program, the user would write the name of the executable as well as the name of the the text file they wish to use to transmit messages.
        For example: ./Assignment3 messageIn.txt