/** CSCI 2270 - Homework 1
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Struct to store information for each garage sale item
struct GarageSaleItem
{
    string type; // chicken, microwave, truck, bike, dresser
    bool status; // 1 = true = "for sale" and 0 = false = "wanted"
    int price; // convert to int from the file using stoi
};


/** 
 * Parameters: a string to split (string), a delimeter to split the string on (char), an array to add the split elements to (string).
 * Return: None
 * Ouput: None
 * Algorithm:
 * 1. Adds the delimeter onto the end of the given string.
 * 2. Loops through each character of the string, and each time there is an occurrence of the delimeter, it adds the characters
 *    up until that point into the array.
 * 3. Continue this process from the next character following an occurrence of the delimeter, until the given string has been iterated
 *    all the way through.
 */ 
void split(string toSplit, char delimeter, string arr[]){
    string word;
    toSplit += delimeter;
    int j=0;
    for(int i=0; i<toSplit.length(); i++){
        if(toSplit[i] == delimeter){
            if(word.length() == 0) continue;
            arr[j] = word;
            j++;
            word = "";
        }
        else if(toSplit[i-1] != ','){
            word += toSplit[i];
        }
    }
}


/** 
 * Parameters: pointer to array (GarageSaleItem*), the length of the array (int), a struct item to compare to the elements in the array (GarageSaleItem)
 * Return: index of the item in the array that matches the given struct item, or -1 if there is no match found (int)
 * Output: None
 * Algorithm:
 * 1. Iterate through the given array for the given length.
 *      Check if the current item in the array has the same type as the GarageSaleItem object passed in to the function.
 *          If yes, check if the status of the array item is the opposite of the GarageSaleItem object.
 *              If yes, check if the price of the Struct that has "wanted" is greater than or equal to the price of the "for sale" item.
 *                  If a match is found, immediately return the index at which the match was found.
 *      If the current item does not match with the object passed in to the function, go to the next item in the array, and continue the process until the array length has been reached.
 * 2. If no match is found in the array, return -1.
 */ 
int searchArray(GarageSaleItem *array, int length, GarageSaleItem currentItem){
    for(int i=0; i<length; i++){
        if(currentItem.type == array[i].type){ // Checks to see if the types match
            if(currentItem.status != array[i].status){ // Checks to see if one is "for sale" and the other is "wanted"
                if((currentItem.status && array[i].price >= currentItem.price) || (array[i].status && currentItem.price >= array[i].price)){ // Checks if wanted price >= sale price
                    return i;
                }
            }
        }
    }

    return -1; // indicates that no match was found
}


/** 
 * Parameters: pointer to array (GaraeSaleItem*), index of the item to be deleted from the array (int), the number of current elements in the array (int)
 * Return: the number of elements minus one (int)
 * Output: None
 * Algorithm:
 * 1. Start at the given index and shift each element in the array to the left.
 * 2. Return the number of elements passed in to the function minus 1.
 */ 
int DeleteElement(GarageSaleItem* arr, int index, int numElements){
    for(int i=index; i<numElements-1; i++){
            arr[i] = arr[i+1];
        }
    return (numElements-1);
}


/**
 * Parameters: pointer to a struct array (GarageSaleItem*), the number of elements in the array (int)
 * Return: none
 * Output: the type, status, and price of each item in the given array
 * Algorithm:
 * 1. Iterate through the given array for the given number of elements, and print out the type, status, and price of each GarageSaleItem.
 */ 
void DisplayMessageBoard(GarageSaleItem* itemArray, int numberElements){
    for(int i=0; i<numberElements; i++){
        if(itemArray[i].status){ // If the item is "for sale"
            cout << itemArray[i].type << ", " << "for sale" << ", " << itemArray[i].price << endl;
        }
        else{ // if the item is "wanted"
            cout << itemArray[i].type << ", " << "wanted" << ", " << itemArray[i].price << endl;
        }
        
    }
}


/** 
 * Parameters: name of file (string), array of GarageSaleItem structs (struct array)
 * Return: the number of elements in the array (int)
 * Output: None
 * Algorithm:
 * 1. Read in a given file one line at a time, split each line on the commas, and create and array of strings.
 * 2. Add the information on each line to a new GarageSaleItem struct.
 * 3. Check if the current GarageSaleItem from the current line matches any elements already in the array.
 *      If yes, do not add the GarageSaleItem to the array, and delete the match found in the array.
 *      If no, add the GarageSaleItem to the array, and add one to the number of elements in the array.
 * 4. Read the next line in the file and go back to step 2 until the file is finished being read.
 * 5. Print out the elements remaining in the array, as well as the number of items sold, and the number of items remaining.
 * 6. Return the number of elements in the array.
 */ 
int readFile(string fileName, GarageSaleItem itemArr[100]){
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){
        string line;
        string lineArr[3];
        int numElements = 0;
        int numSold = 0;
        int matchIdx;
        cout << "\nItems Sold:" << endl;
        while(getline(myfile,line)){
            // Fill an array with the 3 parts of a line (type,status,price)
            split(line,',',lineArr);
            
            // Create a new struct to hold the information from the current line, and set the variables in the struct
            GarageSaleItem lineItem;
            lineItem.type = lineArr[0];
            if(lineArr[1] == "for sale"){
                lineItem.status = true;
            }
            else if(lineArr[1] == "wanted"){
                lineItem.status = false;
            }
            lineItem.price = stoi(lineArr[2]);
            
            // Check to see if the current item has a match in the array
            matchIdx = searchArray(itemArr,numElements,lineItem);
            if(matchIdx == -1){ // Add the item to the array and increase the number of elements
                itemArr[numElements] = lineItem;
                numElements++;
            }
            else{ // Remove the match found from the array
                if(itemArr[matchIdx].status){ // Displays the price of the "for sale" item
                    cout << itemArr[matchIdx].type << " " << itemArr[matchIdx].price << endl;
                }
                else{
                    cout << lineItem.type << " " << lineItem.price << endl;
                }

                // Delete the struct from the array that was a match
                numElements = DeleteElement(itemArr,matchIdx,numElements);

                // Increase the number of items sold
                numSold++;
            }            
        }
        myfile.close();

        // Display the remaining items in the message board, i.e the contents remaining in the array
        cout << "\n";
        cout << "Items remaining:" << endl;
        DisplayMessageBoard(itemArr,numElements);
        cout << "\n";

        // Display: the number of items sold and the number of items remaining in the array
        cout << "Items Sold:\n" << numSold << endl;
        cout << "\nItems remaining in the message board after reading all lines in the file:\n" << numElements << endl;

        return numElements;
    }
    else{
        myfile.close();
        return -1;
    }
}


int main(int argc, char* argv[]){

    // Initialize array of GarageSaleItem Struct
    GarageSaleItem itemArray[100];

    // Read file and fill struct array
    int numberOfElements = readFile(argv[1],itemArray);

    // Check if file was successfully opened
    if(numberOfElements == -1){
        cout << "The file you entered was not found." << endl;
    }

    return 0;
}