Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Final Project - Part II


What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.

        projectDriver.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It reads a given text file, creates a graph from the 
            given information in the file (adjacency matrix), and creates an interface for the user to interact with the graph.

        Queue.hpp:
            Contains the definition of the Queue class, which includes the declaration of the data members and functions that are used to run the program.

        Queue.cpp:
            This file has the implementation and definition of each function from the Queue class.
            
        Graph.hpp:
            Contains the definition of the Graph class, which includes the declaration of the data members and functions that are used to run the program.

        Graph.cpp:
            This file has the implementation and definition of each function from the Graph class.

        List.hpp:
            Contains the definition of the List class, which includes the declaration of the data members and functions that are used to run the program.

        List.cpp:
            This file has the implementation and definition of each function from the List class.

        zombieCitiesInfection.txt:
            This text file contains the adjacency matrix used to create the graph, as well as information regarding the speed of the zombies, and the infection status
            of every city in the graph. 

    The Program:
        The program that can be executed using these files simulates a zombie apocalypse in which certain cities have been infected while others remain strong. The 
        program starts by reading in a file that contains an adjacency matrix, and it creates a graph where each city is a different vertex. Once the graph is built,
        a menu is displayed to the user, which allows them to run search algorithms on the graph and learn information about the cities. Depending on the type of file,
        one of two menus will be displayed, and each one has different running capabilities. The menus are as follows:

        PART I
            Menu:
                1. Print Vertices
                2. Vertex adjacent
                3. Quit

            Description:
                1. The 'Print Vertices' option will print out every vertex in the graph as well as the cities that are adjacent to each one.
                2. The 'Vertex adjacent' option asks the user to input two cities, and will check to see if the two cities are adjacent.
                3. This option allows the user to quit and exit the program.


        PART II 
            Menu:
                1. Print Vertices
                2. Find Districts
                3. Find Shortest Path
                4. Find Shortest Weighted Path
                5. Zombie Infection!
                6. Infection with Zombie Speed!
                7. Quit
            
            Description:
                1. The 'Print Vertices' option prints out the city name and district number of every vertex in the graph, as well as the cities that are adjacent 
                    to each one.
                2. 'Find Districts' does a depth-first search (DFS) of the graph to determine the connected cities in the graph, and it assigns those cities the
                    same district ID. 
                3. The 'Find Shortest Path' option prompts the user for the names of two cities, and first determines if they are in the same district. If the 
                    cities are in different districts, it prints “No safe path between cities”. If the cities are in the same district, the program executes a 
                    breadth-first search (BFS) that returns the number of edges to traverse along the shortest path, and the names of the vertices along the path. 
                4. 'Find Shortest Weighted Path' prompts the user for the names of two cities, and first determines if they are in the same district. If the 
                    cities are in different districts, it prints “No safe path between cities”. If the cities are in the same district, the program runs Dijkstra's 
                    Algorithm to find the shortest possible path between the two cities. It then prints the total shortest distance between the cities, as well as
                    the names of the vertices along the path.
                5. The 'Zombie Infection!' option begins an infection process of the graph at t=0. For the first time step, any existing cities that are infected will 
                    begin infecting their adjacent neighbors. In a single time step, a city may only be infected if one of its neighbors was already infected at the
                    start of that time step. After the simulation is done, the total number of time steps it took for the infection to spread to every city is printed.
                6. 'Infection with Zombie Speed!' is the same as the 'Zombie Infection!' option, with an included Zombie Speed that represents the radial distance a 
                    zombie horde may move in a single time step. If the zombies cannot make the entire distance in one time step, the progress carries over to the 
                    next time step.
                7. This option allows the user to quit and exit the program.


How:
    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the files to compile, which include the driver and the class implementation files.
        For example: g++ -std=c++11 projectDriver.cpp Graph.cpp List.cpp Queue.cpp -o Project
        
    Running the program:
        Then to run the program, the user would write the name of the executable as well as the name of the the text file they wish to use in the program.
        For example: ./Project.exe zombieCitiesInfection.txt 