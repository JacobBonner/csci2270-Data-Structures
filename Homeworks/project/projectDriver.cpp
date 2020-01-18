/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream>
#include <fstream>
#include <string>
#include "Graph.hpp"
using namespace std;
        

/**
 * Function Name: getNumCities
 * Purpose: read a given file and count the number of cities that will be represented by the adjaceny matrix
 * @ param fileName - the name of the file that will be read
 * @ param infectionFile - a pointer to a boolean that indicates whether or not the file has information about infection
 * @ return the number of cities in the file
 */
int getNumCities(char* fileName, bool* infectionFile){
    ifstream myfile;
    myfile.open(fileName);
    
    if(myfile.is_open()){
        string firstLine;
        getline(myfile,firstLine);

        int count = 0;
        for(int i=0; i<firstLine.length(); i++){
            if(firstLine[i] == ','){
                count++;
            }
        }

        if(firstLine[firstLine.length()-1] >= '0' && firstLine[firstLine.length()-1] <= '9'){
            count--;
            *infectionFile = true;
        }

        return count;
    }
    else{
        return -1;
    }   
}


int main(int argc, char* argv[]){

    bool isInfectionFile = false;

    // Get the number of cities
    int numOfCities = getNumCities(argv[1],&isInfectionFile);

    // If the number of cities is equal to -1, then the file was not opened
    if(numOfCities == -1){
        cout << "The file was not opened." << endl;
    }
    else{ // otherwise create the graph and run the program

        // Create Graph
        Graph myGraph(numOfCities);

        // Read file and create graph
        myGraph.readFile(argv[1]);

        // Local variables
        string cityOne, cityTwo;

        // Check if the file has infection information
        if(isInfectionFile){

            // Display menu to the user
            int userChoice = myGraph.displayMenu2();

            // Ensure that the user's input is a valid number between 1 and 7
            while(!userChoice){
                cout << "\nPlease enter a number between 1 and 7 corresponding to your choice." << endl;
                userChoice = myGraph.displayMenu2();
            }

            while(userChoice != 7){
                switch(userChoice){
                    case 1: // Print Vertices
                        myGraph.printVertices2();

                    break;

                    case 2: // Find Districts
                        myGraph.findDistricts();

                    break;

                    case 3: // Find Shortest Path
                        cout << "\nEnter a starting city: " << endl;
                        cin.ignore();
                        getline(cin,cityOne);
                        cout << "Enter an ending city: " << endl;
                        getline(cin,cityTwo);

                        myGraph.shortestPathRunner(cityOne, cityTwo, 3);

                    break;

                    case 4: // Find Shortest Weighted Path
                        cout << "\nEnter a starting city: " << endl;
                        cin.ignore();
                        getline(cin,cityOne);
                        cout << "Enter an ending city: " << endl;
                        getline(cin,cityTwo);

                        myGraph.shortestPathRunner(cityOne, cityTwo, 4);

                    break;

                    case 5: // Zombie Infection
                        myGraph.runInfection();

                    break;

                    case 6: // Infection w/ Zombie Speed (EXTRA CREDIT)
                        myGraph.zombieSpeedInfection();

                    break;
                }

                // Display menu to the user
                userChoice = myGraph.displayMenu2();

                // Ensure that the user's input is a valid number between 1 and 7
                while(!userChoice){
                    cout << "\nPlease enter a number between 1 and 7 corresponding to your choice." << endl;
                    userChoice = myGraph.displayMenu2();
                }
            }
        }
        else{
            // Display menu to the user
            int userChoice = myGraph.displayMenu1();

            // Declaration of local variables that will be used for user input
            string vertexOne, vertexTwo;

            // Ensure that the user's input is a valid number between 1 and 3
            while(!userChoice){
                cout << "\nPlease enter a number between 1 and 3 corresponding to your choice." << endl;
                userChoice = myGraph.displayMenu1();
            }

            while(userChoice != 3){
                switch(userChoice){
                    case 1: // Print Vertices
                        myGraph.printVertices1();
                    break;

                    case 2: // Vertex Adjacent
                        cout << "Enter first city:" << endl;
                        cin.ignore();
                        getline(cin, vertexOne);
                        cout << "Enter second city:" << endl;
                        getline(cin, vertexTwo);

                        bool adj = myGraph.checkAdjacent(vertexOne, vertexTwo);
                        if(adj){
                            cout << "\nTrue" << endl;
                        }
                        else{
                            cout << "\nFalse" << endl;
                        }
                    break;
                }

                // Display menu to the user
                userChoice = myGraph.displayMenu1();

                // Ensure that the user's input is a valid number between 1 and 3
                while(!userChoice){
                    cout << "\nPlease enter a number between 1 and 3 corresponding to your choice." << endl;
                    userChoice = myGraph.displayMenu1();
                }
            }
        }

        // When user selects 'Quit'
        cout << "\nGoodbye!" << endl;
    }

    return 0;
}