/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream> 
#include <fstream>
#include <string>
#include "List.hpp"
using namespace  std;


List :: List(){
    head = NULL;
}


List :: ~List(){
    
}


/**
 * Function Name: addCity
 * Purpose: add a city (node) to the tail of a linked list
 * @ param cityName - the name of the city that is being added
 * @ param weight - a number that represents the distance to this city from a given vertex
 * @ return none
 */
void List :: addCity(string cityName, int weight){
    AdjacentCity* newCity = new AdjacentCity;
    newCity->name = cityName;
    newCity->distance = weight;
    newCity->next = NULL;
    newCity->visited = false;
    newCity->zombieDistance = weight;

    if(head == NULL){
        head = newCity;
    }
    else{
        AdjacentCity* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newCity;
    }
}


/**
 * Function Name: traverse
 * Purpose: print the city name of each node in the linked list
 * @ param none
 * @ return none
 */
void List :: traverse(){
    AdjacentCity* tmp = head;
    while(tmp != NULL){
        cout << tmp->name;
        if(tmp->next != NULL) cout << ", ";
        tmp = tmp->next;
    }
}


/**
 * Function Name: searchList
 * Purpose: search the linked list to check if a city exists in the list
 * @ param cityName - the name of the city that is being searched for
 * @ return true if the city is found in the list, or false if it is not found
 */
bool List :: searchList(string cityName){
    AdjacentCity* tmp = head;
    while(tmp != NULL){
        if(tmp->name == cityName) return true;
        tmp = tmp->next;
    }
    return false;
}


/**
 * Function Name: getHead
 * Purpose: returns the pointer to the head of the linked list
 * @ param none
 * @ return the head of the linked list
 */
AdjacentCity* List :: getHead(){
    return head;
}