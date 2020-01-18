/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream>
#include <string>
#include "List.hpp"
using namespace std;


struct Vertex
{
    string cityName; // name of city
    List adjacentCities; // adjacent cities
    char stateOfInfection; // 'I' if city is infected, or 'S' if it is safe
    int district; // district number
    bool visited; // indicates whether the vertex has been visited/solved in the search algorithms
    Vertex* parent; // points to the parent of the vertex
    int distance; // the distance to the vertex from a given starting vertex (used in search algos)
    bool infectedThisStep; // indicates whether or not the given vertex was infected during a given time step
};


struct QueueNode
{
    QueueNode* next;
    Vertex* city;
};


class Queue
{
    private:
        QueueNode* head;
        QueueNode* tail;
        bool isEmpty();

    public:
        Queue();
        ~Queue();
        void enqueue(Vertex* vert);
        Vertex* dequeue();
        bool runIsEmpty();
};