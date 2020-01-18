/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 


#include <iostream> 
#include <fstream>
#include <string>
#include "Queue.hpp"
using namespace  std;


class Graph
{
    private:
        int zombieSpeed; // for extra credit
        int numCities; // number if cities in graph
        Vertex* vertices; // contains a vertex for each city
        void split(string toSplit, char delimeter, string arr[], bool isFirstLine, int type);


    public:

        // Constructors/Destructors
        Graph();
        Graph(int cityCount);
        ~Graph();

        // General Functions
        void readFile(char* fileName);
        Vertex* searchForCity(string cityName);


        //// PART 1 - no infection status or zombie speed ////

        // Helper/Driver Functions
        int displayMenu1();

        // Print Vertices
        void printVertices1();

        // Check Adjacent
        bool checkAdjacent(string city1, string city2);


        //// PART 2 - infection status and zombie speed ////

        // Helper/Driver Functions 
        int displayMenu2();
        void setAdjCitiesVisited();
        void setVertexVisited(AdjacentCity* cityAdj);
        void setParent(Vertex* parentVertex, string cityName);
        int countCitiesInDistrict(int districtValue);
        void setZombieDistance();

        // Print Vertices
        void printVertices2();

        // Find Districts
        void findDistricts();
        void DFS(Vertex* curr, int districtNumber);

        // Find Shortest Path (weighted and unweighted)
        Vertex* findShortestUnweightedPath(Vertex* start, Vertex* finish);
        void shortestPathRunner(string cityOne, string cityTwo, int userChoice);
        Vertex* findShortestWeightedPath(Vertex* start, Vertex* finish);
        void printPath(Vertex* finalCity);

        // Zombie Infection
        void runInfection();
        void zombieSpeedInfection();
};