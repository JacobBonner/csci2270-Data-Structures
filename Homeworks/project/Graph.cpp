/** CSCI 2270 - Final Project
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 

#include <iostream> 
#include <fstream>
#include <string>
#include "Graph.hpp"
using namespace  std;

//////////////////// CONSTRUCTORS/DESTRUCTOR ////////////////////

Graph :: Graph(){
    numCities = 0;
    zombieSpeed = 0;
}


Graph :: Graph(int numberOfCities){
    numCities = numberOfCities;
    vertices = new Vertex[numCities];
    zombieSpeed = 0;
}


Graph :: ~Graph(){
    
}

//////////////////////////////////////////////////////////////////



//////////////////// GENERAL FUNCTIONS (part I and II) ////////////////////

/**
 * Function Name: split
 * Purpose: split a string on a given delimeter, and insert substrings in between the delimeters into an array
 * @ param toSplit - a string to split on a delimeter
 * @ param delimeter - the character to split the string on
 * @ param arr - an array of strings to hold each substring
 * @ param isFirstLine - indicates whether the given string is the first line in the file
 * @ param type - indicates whether or not the file being read has a zombie speed in the first line
 * @ return none
 */
void Graph :: split(string toSplit, char delimeter, string arr[], bool isFirstLine, int type){
    string word;
    string newSplit;

    if(isFirstLine){ // if it's the first line of the file
        if(type == 1){ // first line doesn't have zombie speed
            newSplit = toSplit + delimeter;
        }
        else{ // first line has zombie speed
            int k=0;
            while(!(toSplit[k] >= '0' && toSplit[k] <= '9')){ 
                newSplit += toSplit[k];
                k++;
            }
            zombieSpeed = stoi(toSplit.substr(k));
        }

        int j=-1;
        for(int i=0; i<newSplit.length(); i++){
            if(newSplit[i] == delimeter){
                if(word.length() == 0) continue;
                if(j != -1) arr[j] = word;
                j++;
                word = "";
            }
            else{
                word += newSplit[i];
            }
        }
    }
    else{ // every line other than the first line
        newSplit = toSplit + delimeter;
        int j;
        if(type == 1){
            j = -1;
            for(int i=0; i<newSplit.length(); i++){
                if(newSplit[i] == delimeter){
                    if(word.length() == 0) continue;
                    if(j != -1) arr[j] = word;
                    j++;
                    word = "";
                }
                else{
                    word += newSplit[i];
                }
            }
        }
        else{
            j = -2;
            for(int i=0; i<newSplit.length(); i++){
                if(newSplit[i] == delimeter){
                    if(word.length() == 0) continue;
                    if(j > -1) arr[j] = word;
                    j++;
                    word = "";
                }
                else{
                    word += newSplit[i];
                }
            }
        }
    }
}


/**
 * Function Name: readFile
 * Purpose: read a given text file with an adjacent matrix, and create a graph
 * @ param fileName - the name of the file that will be read
 * @ return none
 */
void Graph :: readFile(char* fileName){
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){

        string line;
        int lineNum = -1;
        bool isInfectionText = false;

        // An array to hold the city names
        string cityNames[numCities];

        // An array to hold the information from each line
        string lineArr[numCities];

        // Array to hold the distance values for each line
        int distances[numCities];

        while(getline(myfile,line)){
            if(lineNum == -1){
                if(line[line.length()-1] >= '0' && line[line.length()-1] <= '9'){
                    split(line, ',', cityNames,true,2);
                    isInfectionText = true;
                }
                else{
                    split(line, ',', cityNames,true,1);
                }
            }
            else{

                // Create new Vertex (city) and set its name
                Vertex newVertex;
                newVertex.cityName = cityNames[lineNum];
                newVertex.district = -1;
                newVertex.visited = false;
                newVertex.parent = NULL;
                newVertex.distance = 0;
                newVertex.infectedThisStep = false;

                // Check if the file is a type with infection information or not
                if(isInfectionText){ // file contains infection information

                    // Set the state of infection for the current vertex
                    for(int i=0;i<line.length(); i++){
                        if(line[i] == ','){
                            newVertex.stateOfInfection = line[i+1];
                            break;
                        }
                    }

                    // Split the current line into an array
                    split(line, ',', lineArr,false,2);
                }
                else{ // otherwise

                    // Split the current line into an array
                    split(line, ',', lineArr,false,1);
                }

                // Copy the values from the line array as integers into an integer array
                for(int i=0; i<numCities; i++){
                    distances[i] = stoi(lineArr[i]);
                }

                // Set the adjacent cities for the current Vertex
                for(int i=0; i<numCities; i++){
                    if(distances[i] != 0 && distances[i] != -1){
                        // Insert city into the adjacent list for the current Vertex
                        newVertex.adjacentCities.addCity(cityNames[i], distances[i]);
                    }
                }

                // Add the vertex to the vertices array
                vertices[lineNum] = newVertex;
            }
            lineNum++;
        }
    }
}


/**
 * Function Name: searchForCity
 * Purpose: searches the array of vertices to see if a city exists in the graph
 * @ param name - the name of the city that is being searched for in the vertices array
 * @ return a pointer to the vertex that corresponds to the given city, or a NULL pointer if the city does not exist in the graph
 */
Vertex* Graph :: searchForCity(string name){
    for(int i=0; i<numCities; i++){
        if(vertices[i].cityName == name){
            return &vertices[i];
        }
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////



//////////////////// PART I ////////////////////

///// HELPER/DRIVER FUNCTIONS /////

/**
 * Function Name: displayMenu1
 * Purpose: display a menu that presents the user with the capabilities of this program
 * @ param none
 * @ return userChoice - the number corresponding to the user's choice
 */
int Graph :: displayMenu1(){
    cout << "\n======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Vertex adjacent" << endl;
    cout << "3. Quit" << endl;

    string userChoice;
    cin >> userChoice;
    
    // if the length of the user's input is greater than 1, or if the user's input is not between 1-3
    if(userChoice.length() > 1 || !(userChoice[0]>'0' && userChoice[0]<'4')){
        return 0;
    }
    else{
        return stoi(userChoice);
    }
}

///// PRINT VERTICES /////

/**
 * Function Name: printVertices1
 * Purpose: print the vertices in the array and the adjacent cities for each one
 * @ param none
 * @ return none
 */
void Graph :: printVertices1(){
    cout << "\n";
    for(int i=0; i<numCities; i++){
        cout << vertices[i].cityName << ": ";
        vertices[i].adjacentCities.traverse();
        cout << "\n";
    }
}

///// CHECK ADJACENT /////

/**
 * Function Name: checkAdjacent
 * Purpose: check whether or not two given cities are adjacent in the graph
 * @ param city1 - the name of a city
 * @ param city2 - the name of a second city
 * @ return true if the cities are adjacent, or false if they are not
 */
bool Graph :: checkAdjacent(string city1, string city2){
    for(int i=0; i<numCities; i++){
        if(vertices[i].cityName == city1){
            return vertices[i].adjacentCities.searchList(city2);
        }
        else if(vertices[i].cityName == city2){
            return vertices[i].adjacentCities.searchList(city1);
        }
    }
    return false;
}

////////////////////////////////////////////////



//////////////////// PART II ////////////////////

///// HELPER/DRIVER FUNCTIONS /////

/**
 * Function Name: displayMenu2
 * Purpose: display a menu that presents the user with the capabilities of this program
 * @ param none
 * @ return userChoice - the number corresponding to the user's choice
 */
int Graph :: displayMenu2(){
    cout << "\n======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Find districts" << endl;
    cout << "3. Find shortest path" << endl;
    cout << "4. Find shortest weighted path" << endl;
    cout << "5. Zombie Infection!" << endl;
    cout << "6. Infection with Zombie Speed!" << endl;
    cout << "7. Quit" << endl;

    string userChoice;
    cin >> userChoice;
    
    // if the length of the user's input is greater than 1, or if the user's input is not between 1-7
    if(userChoice.length() > 1 || !(userChoice[0]>'0' && userChoice[0]<'8')){
        return 0;
    }
    else{
        return stoi(userChoice);
    }
}


/**
 * Function Name: setAdjCitiesVisited
 * Purpose: Sets the visited status of every adjacent city of each vertex in the graph
 * @ param none
 * @ return none
 */
void Graph :: setAdjCitiesVisited(){
    for(int i=0; i<numCities; i++){
        AdjacentCity* temp = vertices[i].adjacentCities.getHead();
        while(temp != NULL){
            for(int j=0; j<numCities; j++){
                if(temp->name == vertices[j].cityName){
                    temp->visited = vertices[j].visited;
                }
            }
            temp = temp->next;
        }
    }
}


/**
 * Function Name: setVertexVisited
 * Purpose: set the visited status of the vertex corresponding to a given adjacent city
 * @ param adjCity - a pointer to the adjacent city whose visited status is being used to set the status of the correpsonding Vertex
 * @ return none
 */
void Graph :: setVertexVisited(AdjacentCity* adjCity){
    for(int i=0; i<numCities; i++){
        if(vertices[i].cityName == adjCity->name){
            vertices[i].visited = adjCity->visited;
        }
    }
}


/**
 * Function Name: setParent
 * Purpose: Set the parent pointer of the vertex with the given name
 * @ param parentVertex - the parent vertex that is being set as a given city's parent
 * @ param cityName - the name of the city/vertex whose parent is being set
 * @ return none
 */
void Graph :: setParent(Vertex* parentVertex, string cityName){
    for(int i=0; i<numCities; i++){
        if(vertices[i].cityName == cityName){
            vertices[i].parent = parentVertex;
        }
    }
}


/**
 * Function Name: countCitiesInDistrict
 * Purpose: count the number of cities in a given district
 * @ param districtValue - the district whose number of vertices is being calculated
 * @ return the number of cities/vertices in the given district
 */
int Graph :: countCitiesInDistrict(int districtValue){
    int counter = 0;
    for(int i=0; i<numCities; i++){
        if(vertices[i].district == districtValue) counter++;
    }
    return counter;
}


///// PRINT VERTICES /////

/**
 * Function Name: printVertices2
 * Purpose: print the vertices in the array, and the district and adjacent cities for each vertex
 * @ param none
 * @ return none
 */
void Graph :: printVertices2(){
    cout << "\n";
    for(int i=0; i<numCities; i++){
        cout << vertices[i].district << ":" << vertices[i].cityName << ": ";
        vertices[i].adjacentCities.traverse();
        cout << "\n";
    }
}


///// FIND DISTRICTS /////

/**
 * Function Name: findDistricts
 * Purpose: Sets the district of every vertex in the graph by calling depth first search
 * @ param none
 * @ return none
 */
void Graph :: findDistricts(){
    int districtVal = 1;
    for(int i=0; i<numCities; i++){
        if(vertices[i].district == -1){
            DFS(&vertices[i], districtVal);
            districtVal++;
        }
    }
    // Reset visited to false
    for(int i=0; i<numCities; i++){
        vertices[i].visited = false;
    }
    setAdjCitiesVisited();
}


///// FIND SHORTEST PATH (weighted/unweighted) /////

/**
 * Function Name: DFS
 * Purpose: search through the graph Depth First and give each set of connected cities a district number
 * @ param current - the Vertex/city whose adjacent cities are being searched through
 * @ param districtVal - the number representing the district number of the current group of vertices being searched through
 * @ return none
 */
void Graph :: DFS(Vertex* current, int districtVal){
    current->visited = true;
    setAdjCitiesVisited();
    current->district = districtVal;
    AdjacentCity* temp = current->adjacentCities.getHead();
    while(temp != NULL){
        if(!(temp->visited)){
            Vertex* nextVert = searchForCity(temp->name);
            DFS(nextVert, districtVal);
        }
        temp = temp->next;
    }
}


/**
 * Function Name: findShortestUnweightedPath
 * Purpose: finds the shortest unweighted path between two given vertices by using breadth first search
 * @ param start - the starting vertex that will be searched from
 * @ param finish - the final vertex that is being searched for
 * @ return a pointer to the final vertex that is being searched for
 */
Vertex* Graph :: findShortestUnweightedPath(Vertex* start, Vertex* finish){

    // if the starting and ending node are the same
    if(start == finish){
        return finish;
    }

    // Set the starting city's visited to true
    start->visited = true;
    setAdjCitiesVisited();

    // Create a queue and add the starting city to it
    Queue Q;
    Q.enqueue(start);

    // Local variables for traversal
    AdjacentCity* temp;
    Vertex *curr, *toEnqueue;

    while(!Q.runIsEmpty()){

        // Dequeue from the Que and check the adjacent cities of that city
        curr = Q.dequeue();
        temp = curr->adjacentCities.getHead();

        while(temp != NULL){

            // Check if the current city has been visited
            if(!temp->visited){
                
                // Set the parent of the current city
                setParent(curr,temp->name);
                
                // Set the distance of the current city to be the distance of the previous city + 1
                toEnqueue = searchForCity(temp->name);
                toEnqueue->distance = curr->distance + 1;

                // Check if the current city is the city we are searhing for
                if(temp->name == finish->cityName){
                    return searchForCity(temp->name);
                }
                else{
                    
                    // Set visited to true for every occurrence of the current city
                    temp->visited = true;
                    setVertexVisited(temp);
                    setAdjCitiesVisited();

                    // Add the next city to the queue
                    Q.enqueue(toEnqueue);
                }
            }
        temp = temp->next;
        }
    }
}


/**
 * Function Name: printPath
 * Purpose: print the shortest unweighted or weighted path between two vertices in the graph
 * @ param finalCity - the final city/vertex that was being searhed for using breadth first search, or Dijkstras Algorithm
 * @ return none
 */
void Graph :: printPath(Vertex* finalCity){
    // Create an array to hold the names of the cities that were traveled through
    int totalDistance = finalCity->distance;
    int districtSize = countCitiesInDistrict(finalCity->district);
    int idx = districtSize-1;
    string cityPathNames[districtSize];
    cout << "\n";
    
    // Fill the array with the names of the cities using the parent pointers established in the search algorithms
    Vertex* temp = finalCity;
    while(temp != NULL){
        cityPathNames[idx] = temp->cityName;
        temp = temp->parent;
        idx--;
    }
    
    // Print out the total distance, as well as the name of each city in the shortest path found
    cout << totalDistance << ": ";
    for(int i=0; i<districtSize; i++){
        if(cityPathNames[i] != ""){
            cout << cityPathNames[i];
            if(i != districtSize-1) cout << " -> ";
        }
    }
    cout << endl;
}


/**
 * Function Name: findShortestWeightedPath
 * Purpose: calculate the shortest weighted path between two given nodes using Dijkstras Algorithm
 * @ param start - the starting vertex 
 * @ paran finish - the vertex to which the shortest path is being found from the starting vertex
 * @ return the vertex to which the shortest path is being found
 */
Vertex* Graph :: findShortestWeightedPath(Vertex* start, Vertex* finish){
    // Set all instances of the starting vertex to true, and set the distance equal to zero
    start->visited = true;
    start->distance = 0;
    setAdjCitiesVisited();

    // Count the number of cities in the current district, and create an array of that size to hold the vertices that have been solved
    int citiesInDistrict = countCitiesInDistrict(start->district);
    Vertex* solved[citiesInDistrict];
    for(int i=0; i<citiesInDistrict; i++){
        if(i == 0){
            solved[i] = start;
        }
        else{
            solved[i] = NULL;
        } 
    }

    // Local variables for traversal and such
    AdjacentCity* temp;
    Vertex *solvedVertex, *curr, *parentVertex;
    int minDistance, dist;
    int index = 1;

    // while the destination city has not been solved
    while(!finish->visited){
        minDistance = 1000000;
        solvedVertex = NULL;
        for(int i=0; i<citiesInDistrict; i++){
            if(solved[i] != NULL){
                curr = solved[i];
                temp = curr->adjacentCities.getHead();
                while(temp != NULL){
                    if(!temp->visited){
                        dist = curr->distance + temp->distance;
                        if(dist < minDistance){
                            solvedVertex = searchForCity(temp->name);
                            minDistance = dist;
                            parentVertex = curr;
                        }
                    }
                    temp = temp->next;
                }
            }
        }

        // Set new data for the solved vertex
        solvedVertex->distance = minDistance;
        solvedVertex->parent = parentVertex;
        solvedVertex->visited = true;
        solved[index] = solvedVertex;
        index++;

        // Set visited to true for all instances of the city
        setAdjCitiesVisited();
    }

    return finish;
}


/**
 * Function Name: shortestPathRunner
 * Purpose: runs either a breadth first search to find the shortest unweighted path between two vertices, or calls Dijkstras Algorithm to find the shortest weighted path
 * @ param cityOne - the name of the starting city used in the distance calculations
 * @ parma cityTwo - the name of the city that is having the shortest distance to calculated
 * @ param userChoice - distinguishes between running breadth first for unewighted path, or Dijkstras for weighted path
 * @ return none
 */
void Graph :: shortestPathRunner(string cityOne, string cityTwo, int userChoice){
    if(vertices[0].district != -1){

            Vertex* startCity = searchForCity(cityOne);
            Vertex* endCity = searchForCity(cityTwo);
            Vertex* finalVertex;

            if(startCity != NULL && endCity != NULL){ // both cities exist
                if(startCity->district == endCity->district){ // same district
                    if(userChoice == 3){ // CALCULATE THE SHORTEST PATH UNWEIGHTED (BFS)
                        finalVertex = findShortestUnweightedPath(startCity, endCity);
                    }
                    else{ // CALCULATE THE SHORTEST PATH WEIGHTED (Dijkstras)
                        finalVertex = findShortestWeightedPath(startCity, endCity);
                    }
                    printPath(finalVertex);
                }
                else{ // different districts
                    cout << "\nNo safe path between cities" << endl;
                }
            }
            else{ // one or both cities don't exist
                cout << "\nOne or more cities doesn't exist" << endl;
            }
        }
    else{ // districts have not been set
        cout << "\nPlease identify the districts before checking distances" << endl;
    }

    // Reset visited to false, parent to NULL, and distance to 0
    for(int i=0; i<numCities; i++){
        vertices[i].visited = false;
        vertices[i].parent = NULL;
        vertices[i].distance = 0;
    }
    setAdjCitiesVisited();
}

///// ZOMBIE INFECTION /////

/**
 * Function Name: runInfection
 * Purpose: runs the spreading of the infection in the graph
 * @ param none
 * @ return none
 */
void Graph :: runInfection(){
    AdjacentCity* temp;
    Vertex* toInfect;
    bool infectionSpread = true;
    int timeStep = 0;

    for(int i=0; i<numCities; i++){
        if(vertices[i].stateOfInfection == 'S'){
            infectionSpread = false;
        }
    }

    // if either this function or the zombie speed infection have already been run, i.e the infection has already spread
    if(infectionSpread){
        cout << "\nInfection has already spread! (restart program to run infection again)" << endl;
    }
    else{
        cout << "\nStarting infection!" << endl;
        while(!infectionSpread){
            infectionSpread = true;
            timeStep++;
            for(int i=0; i<numCities; i++){
                if(vertices[i].stateOfInfection == 'I' && !vertices[i].infectedThisStep){ // if the current vertex is infected, AND has not been infected this time step
                    temp = vertices[i].adjacentCities.getHead();
                    while(temp != NULL){
                        toInfect = searchForCity(temp->name);
                        if(toInfect->stateOfInfection == 'S'){ // if an adjacent vertex is Safe, change it to be infected
                            toInfect->stateOfInfection = 'I';
                            toInfect->infectedThisStep = true;
                        }
                        temp = temp->next;
                    }
                }
            }

            // Check to see if all cities have been infected
            for(int i=0; i<numCities; i++){
                if(vertices[i].stateOfInfection == 'S'){
                    infectionSpread = false;
                }
                vertices[i].infectedThisStep = false;
            }
        }

        cout << "\nFinal time step: " << timeStep << endl;
    }
}


/**
 * Function Name: zombieSpeedInfection
 * Purpose: runs the spreading of the infection in the graph based on the speed of the zombies
 * @ param none
 * @ return none
 */
void Graph :: zombieSpeedInfection(){

    AdjacentCity* temp;
    Vertex* toInfect;
    bool infectionSpread = true;
    int timeStep = 0;

    for(int i=0; i<numCities; i++){
        if(vertices[i].stateOfInfection == 'S'){
            infectionSpread = false;
        }
    }

    // if either this function or the zombie speed infection have already been run, i.e the infection has already spread
    if(infectionSpread){
        cout << "\nInfection has already spread! (restart program to run infection again)" << endl;
    }
    else{
        cout << "\nStarting infection with zombie speed!" << endl;
        while(!infectionSpread){
            infectionSpread = true;
            timeStep++;
            //cout << "\nTIME STEP: " << timeStep << endl;
            for(int i=0; i<numCities; i++){
                if(vertices[i].stateOfInfection == 'I' && !vertices[i].infectedThisStep){ // if the current vertex is infected, AND has not been infected this time step
                    temp = vertices[i].adjacentCities.getHead();
                    while(temp != NULL){
                        toInfect = searchForCity(temp->name);
                        if(toInfect->stateOfInfection == 'S'){ // if an adjacent vertex is Safe, change it to be infected
                            //cout << "\n" << temp->name << " has a distance of " << temp->zombieDistance << endl;
                            if(zombieSpeed >= temp->zombieDistance){
                                toInfect->stateOfInfection = 'I';
                                //cout << toInfect->cityName << " is being infected." << endl;
                                toInfect->infectedThisStep = true;
                            }
                            // else{
                            //     cout << temp->name << " cannot be reached by zombies this time step." << endl;
                            // }
                        }

                        if(temp->zombieDistance - zombieSpeed >= 0){
                            temp->zombieDistance = temp->zombieDistance - zombieSpeed;
                        }

                        temp = temp->next;
                    }
                }
            }

            // Check to see if all cities have been infected
            for(int i=0; i<numCities; i++){
                if(vertices[i].stateOfInfection == 'S'){
                    infectionSpread = false;
                }
                vertices[i].infectedThisStep = false;
            }
        }

        cout << "\nFinal time step: " << timeStep << endl;
    }
}

/////////////////////////////////////////////////