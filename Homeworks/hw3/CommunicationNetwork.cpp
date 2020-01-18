#include <iostream>
#include <fstream>
#include "CommunicationNetwork.hpp"
using namespace std;


// Constructor
CommunicationNetwork :: CommunicationNetwork(){
    head = NULL;
}


// Destructor
CommunicationNetwork :: ~CommunicationNetwork(){
    deleteNetwork();
}


/**
 * Function Name: addCity
 * Purpose: add a city with a given name to the network, at the position after a given previous city name
 * @ param newCityName - the name of the city to be added
 * @ param previousCityName - the name of the previous city to be added after
 * @ return none
 */
void CommunicationNetwork :: addCity(string newCityName, string previousCityName){
    // variable to indicate whether the previous city is found
    bool found = false;

    // create new city and set the name, and the next and prev to NULL
    City* newCity = new City;
    newCity->name = newCityName;
    newCity->next = NULL;
    newCity->prev = NULL;

    if(head == NULL){
        cout << "Network is empty." << endl;
        if(previousCityName != "First" && previousCityName != ""){
            cout << previousCityName << " not found." << endl;
        }
        cout << newCityName << " is now the first and only city in the network." << endl;
        head = newCity;
    }
    else{
        // temporary pointer to hold the current city while traversing
        City* tmp = head;

        if(previousCityName == "First"){ // inserting the new City at the head
            newCity->next = head;
            head->prev = newCity;
            head = newCity;
            found = true;
        }
        else if(previousCityName == ""){ // inserting the new city at the tail
            while(tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = newCity;
            newCity->prev = tmp;
            found = true;
        }
        else{ // inserting the new city in the middle somewhere
            while(tmp != NULL){
                if(tmp->name == previousCityName){
                    newCity->next = tmp->next;
                    tmp->next = newCity;
                    newCity->prev = tmp;
                    found = true;
                    break;
                }
                tmp = tmp->next;
            }
        }

        // if the previous city name does not exist in the network
        if(!found){
            cout << previousCityName << " not found in network." << endl;
        }
    }
}


/**
 * Function Name: transmitMsg
 * Purpose: to transmit a message word by word from head to tail to head
 * @ param filename - the name of the file to be read and transmitted
 * @ return none
 */
void CommunicationNetwork :: transmitMsg(char * filename){
    // if the network is empty
    if(head == NULL){
        cout << "Empty list" << endl;
    }
    else{
        ifstream myfile;
        myfile.open(filename);
        if(myfile.is_open()){
            string word;
            while(myfile >> word){
                City* temp = head;
                while(temp->next != NULL){ // send the word from head to tail
                    temp->message = word;
                    cout << temp->name << " received " << temp->message << endl;
                    temp->message = "";
                    temp = temp->next;
                }
                
                while(temp != NULL){ // send the work from tail to head
                    temp->message = word;
                    cout << temp->name << " received " << temp->message << endl;
                    temp->message = "";
                    temp = temp->prev;
                }
            }
        }
        else{
            cout << "The file you entered was not opened successfully." << endl;
        }
    }
}


/**
 * Function Name: printNetwork
 * Purpose: print out the name of every city in the network
 * @ param none
 * @ return none
 */
void CommunicationNetwork :: printNetwork(){
    // if the network is empty
    if(head == NULL){
        cout << "Network is Empty." << endl;
    }
    else{
        City* tmp = head;
        cout << "===CURRENT PATH===" << endl;
        if(tmp->prev == NULL){ // verifies that the previous of the head is indeed NULL
            cout << "NULL <- ";
        }
        while(tmp != NULL){
            cout << tmp->name;
            if(tmp->next != NULL) cout << " <-> ";
            tmp = tmp->next;
        }
        if(tmp == NULL){ // verifies that the next of the last City is indeed NULL
            cout << " -> NULL" << endl;
        }
        cout << "==================" << endl;
    }
}


/**
 * Function Name: buildNetwork
 * Purpose: initialize the network with 10 cities 
 * @ param none
 * @ return none
 */
void CommunicationNetwork :: buildNetwork(){
    // create array to hold the city names
    string cities[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};
    
    // pointers to cities
    City *newCity, *prevCity;

    // start with the last city in the list
    prevCity = new City;
    prevCity->name = cities[9];
    prevCity->next = NULL;

    // iterate backward through the array and set pointers to the next and previous cities
    for(int i=8; i>=0; i--){
        newCity = new City;
        newCity->name = cities[i];
        prevCity->prev = newCity;
        newCity->next = prevCity;
        prevCity = newCity;
    }

    // set the first city in the array equal to the head
    prevCity->prev = NULL;
    head = prevCity;

    // print the current network
    printNetwork();
}


/**
 * Function Name: deleteCity
 * Purpose: delete the city with the given name from the network
 * @ param removeCity - the name of the city to be removed from the network
 * @ return none
 */
void CommunicationNetwork :: deleteCity(string removeCity){
    if(head == NULL){
        cout << "Error. Network is empty." << endl;
    }
    else{
        bool cityFound = false;
        City* toDelete;

        // deleting head
        if(removeCity == head->name){
            toDelete = head;
            head = head->next;
            if(head != NULL){
                head->prev = NULL;
            }
        }
        else{
            // start at the head and search through the entire network until the tail is reached
            City* temp = head;
            while(temp != NULL){
                if(temp->name == removeCity){ // if the current city has the name that was passed in to the function
                    if(head->next == NULL){
                        head = NULL;
                    }
                    if(temp->next == NULL){
                        temp->prev->next = NULL;
                    }
                    else{
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                    }
                    cityFound = true;
                    toDelete = temp;
                    break;
                }
                temp = temp->next;
            }
            delete toDelete;
            if(!cityFound){
                cout << removeCity << " not found" << endl;
            }
        }
    }
}


/**
 * Function Name: deleteNetwork
 * Purpose: delete the network that has been created
 * @ param none
 * @ return none
 */
void CommunicationNetwork :: deleteNetwork(){
    City* currentCity = head;
    City* temp;

    // start at the head and delete every city until the end of the network
    while(currentCity != NULL){
        temp = currentCity;
        cout << "deleting " << temp->name << endl;
        currentCity = currentCity->next;
        delete temp;
    }
    delete currentCity;
    head = NULL;
}