/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream>
#include <string>
#include "Queue.hpp"
using namespace std;


Queue :: Queue(){
    head = NULL;
    tail = NULL;
}


Queue :: ~Queue(){
    
}


/**
 * Function Name: isEmpty
 * Purpose: determines whether the queue is empty or not
 * @ param none
 * @ return true if the queue is empty, or false otherwise
 */
bool Queue :: isEmpty(){
    if (head == NULL) return true;
    return false;
}


/**
 * Function Name: enqueue
 * Purpose: adds a vertex to the queue
 * @ param vert - a pointer to a vertex whose information is being stored in a node in the queue
 * @ return none
 */
void Queue :: enqueue(Vertex* vert){
    QueueNode* newNode = new QueueNode;
    newNode->city = vert;
    newNode->next = NULL;

    if(tail) tail->next = newNode;
    tail = newNode;
    if(!head) head = newNode;
}


/**
 * Function Name: dequeue
 * Purpose: removes the first element in the queue (FIFO)
 * @ param none
 * @ return a pointer to the vertex that is removed
 */
Vertex* Queue :: dequeue(){
    QueueNode* temp = head;
    head = head->next;
    if(!head) tail = head;
    return temp->city;
}


/**
 * Function Name: runIsEmpty
 * Purpose: run the private isEmpty function
 * @ param none
 * @ return true if the queue is empty, or false otherwise
 */
bool Queue :: runIsEmpty(){
    return isEmpty();
}