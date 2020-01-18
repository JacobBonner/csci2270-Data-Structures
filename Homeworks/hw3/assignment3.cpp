/** CSCI 2270 - Homework 3
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 

#include <iostream>
#include <fstream>
#include <string>
#include "CommunicationNetwork.hpp"
using namespace std;

/**
 * Function Name: displayMenu
 * Purpose: display the menu to the user, and recieve input from the user
 * @ param none
 * @ return userChoice - the integer corresponding to the user's choice
 */
int displayMenu(){
    cout << "\n======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;

    string userChoice;
    cin >> userChoice;
    
    // if the length of the user's input is greater than 1, or if the user's input is not between 0 and 7
    if(userChoice.length() > 1 || !(userChoice[0]>'0' && userChoice[0]<'8')){
        return 0;
    }
    else{
        return stoi(userChoice);
    }
}


int main(int argc, char* argv[]){

    // CommuncationNetwork object, i.e. the network that will be used
    CommunicationNetwork Network;

    // local varables to store user input
    string cityToDelete, cityToAdd, previousCity;

    // Display the menu for the first time and obtain the user's input
    int userChoice = displayMenu();

    // continue to display the menu and ask for input while the user's choice is not valid
    while(!userChoice){
        cout << "Please enter a number between 1 and 7 corresponding to your choice." << endl;
        userChoice = displayMenu();
    }

    // continue to display the menu and ask the user for input until they quit
    while(userChoice != 7){
        
        // test the user's input against the different menu options, and run the corresponding functions for each case
        switch(userChoice)
        {
            case 1: // Build Network
                Network.buildNetwork();
            break;

            case 2: // Print Network Path
                Network.printNetwork();
            break;

            case 3: // Transmit Message
                Network.transmitMsg(argv[1]);
            break;

            case 4: // Add city
                cout << "Enter a city name: " << endl;
                cin.ignore();
                getline(cin,cityToAdd);
                cout << "Enter a previous city name: " << endl;
                getline(cin,previousCity);
                Network.addCity(cityToAdd, previousCity);
            break;

            case 5: // Delete City
                cout << "Enter a city name: " << endl;
                cin.ignore();
                getline(cin,cityToDelete);
                Network.deleteCity(cityToDelete);
            break;

            case 6: // Clear Network
                Network.deleteNetwork();
            break;
        }
        
        // display the menu and ask the user for input, and continue to do so if their input is invalid
        userChoice = displayMenu();
        while(!userChoice){
            cout << "Please enter a number between 1 and 7 corresponding to your choice." << endl;
            userChoice = displayMenu();
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}