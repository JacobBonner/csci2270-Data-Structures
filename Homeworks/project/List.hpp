/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream> 
#include <fstream>
#include <string>
using namespace  std;


struct AdjacentCity
{
    string name;
    int distance;
    AdjacentCity* next;
    bool visited;
    int zombieDistance;
};


class List
{
    private:
        AdjacentCity* head;

    public:
        List();
        ~List();
        void addCity(string cityName, int weight);
        void traverse();
        bool searchList(string cityName);
        AdjacentCity* getHead();
};