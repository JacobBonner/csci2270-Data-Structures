/** CSCI 2270 - Homework 2
 * Author: Jake Bonner
 * Instructor: Christopher Godley
 * Section: 310
 */ 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


// Struct to store information for each word
struct wordItem
{
    string word;
    int count;
};


/**
 * Function name: getStopWords
 * Purpose: read stop word list from file and store the words in an array
 * Parameters: ignoreWordFile (filename to read ignore words from), ignoreWords (array to populate with ignore words)
 * Return: none
 */ 
void getStopWords(char* ignoreWordFileName, string ignoreWords[50]){
    ifstream ignoreFile;
    ignoreFile.open(ignoreWordFileName);
    if(ignoreFile.is_open()){
        string line;
        int count = 0;
        while(getline(ignoreFile,line)){
            ignoreWords[count] = line; // fills array with the word from the current line
            count++;
        }
    }
    else{
        cout << "The file " << ignoreWordFileName << " was unsuccesfully opened." << endl;
    }
}


/**
 * Function name: isStopWord
 * Purpose: to check if a word is a stop word
 * Parameters: word (a word, to see if it is a stop word), ignoreWords (the array of strings storing the stop words)
 * Return: true if a word is a stop word, or false if it is not (otherwise)
 */ 
bool isStopWord(string word, string ignoreWords[50]){
    for(int i=0; i<50; i++){
        if(word == ignoreWords[i]){
            return true;
        }
    }
    return false;
}


/**
 * Function name: arrayDouble
 * Purpose: to double the length of an array
 * Parameters: itemArray (array of wordItems to double), length (the length of the array)
 * Return: an array that is twice the length of the one passed into the function
 */ 
void arrayDouble(wordItem *&itemArray, int length){
    //cout << "Adress of Array being passed into function: " << itemArray << endl;
    wordItem* newArray = new wordItem[length*2];
    for(int i=0; i<length; i++){
        newArray[i] = itemArray[i];
    }
    wordItem* temp = itemArray;
    itemArray = newArray;
    // cout << "Address of temp Array: " << temp << endl;
    // cout << "Address of New Array: " << itemArray << endl;
    // cout << "\n";
    delete [] temp;
}


/**
 * Function name: checkForWord
 * Purpose: check if the given word already exists in the array of wordItems
 * Parameters: wordArray (an array of wordItems to compare to), word (the word to check for existence in the array), length (the length of the array)
 * Return: the index where the word was found, or -1 if the word does not exist in the array
 */ 
int checkForWord(wordItem* wordArray, string word, int length){
    for(int i=0; i<length; i++){
        if(wordArray[i].word == word){
            return i;
        }
    }
    return -1;
}


/**
 * Function name: readFile
 * Purpose: read a text file and store each unique word and its count in a wordItem array
 * Parameters: file name (file to read and store information about the words), worditem array pointer by reference (array to put items into),
 *             stopWords (array of words to ignore from the file), double count (pointer to variable that tracks how many times the array is doubled),
 *             stop count (pointer to variable that tracks how many stop words there are in the file)
 * Return: the number of unqie words in the file, i.e the length of the array
 */
int readFile(char* fileName, wordItem *&wordArray, string stopWords[50], int* doubleCount, int* stopCount){
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){
        string word;
        int wordCount = 0;
        int size = 10;
        while((myfile >> word)){
            
            // Check if the current word read from the file is an "ignore word"
            bool stopWord = isStopWord(word, stopWords);
            
            if(!stopWord){

                // Check if the current word read from the file already exists in the wordItem array
                int wordCheck = checkForWord(wordArray, word, wordCount);
                
                if(wordCheck == -1){ // the word is not already in the array
                    
                    // Check if the array is not large enough, and if so, double it
                    if(wordCount >= size){
                        arrayDouble(wordArray,size);
                        size = size*2;
                        (*doubleCount)++;
                    }

                    // Set the word and count of the new wordItem
                    wordArray[wordCount].word = word;
                    wordArray[wordCount].count = 1;
                    
                    // Increase the word count by 1
                    wordCount++;
                }
                else{

                    // Increase the count of a word if it already exists in the array
                    wordArray[wordCheck].count = (wordArray[wordCheck].count+1);
                }
            }
            else{
                (*stopCount)++;
            }
        }
        return wordCount;
    }
    else{
        cout << "The file " << fileName << " was unsuccesfully opened." << endl;
    }
}


/**
 * Function name: arraySort
 * Purpose: sort an array of wordItems in ascending order by their count values
 * Parameters: list (an array of wordItems to be sorted), length (the length of the array)
 * Return: none
 */ 
void arraySort(wordItem list[], int length){
    for(int i=0; i<length-1; i++){
        for(int j=0; j<length-i-1; j++){
            if(list[j].count > list[j+1].count){
                wordItem temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}


/**
 * Function name: getTotalNumberNonStopWords
 * Purpose: compute the total number of words saved in the words array
 * Parameters: list (an array of wordItems), length (the length of the array)
 * Return: the total number of words in the words array
 */ 
int getTotalNumberNonStopWords(wordItem list[], int length){
    int total = 0;
    for(int i=0; i<length; i++){
        total += list[i].count;
    }
    return total;
}


/**
 * Function name: printTopN
 * Purpose: print the top N words with the highest frequency
 * Parameters: wordItemList (a pointer to a sorted array of wordItems), topN (the number of top frequency words to print), wordCount (total number of words), length( length of array)
 * Return: none
 */ 
void printTopN(wordItem wordItemList[], int topN, int wordCount, int length){
    for(int i=length-1; i>=length-topN; i--){
        int numCount = wordItemList[i].count;
        double percent = ((double)numCount/wordCount)*100;
        string word = wordItemList[i].word;
        cout << numCount << " - " << fixed << setprecision(2) << percent << "% - " << word << endl;
    }
}


int main(int argc, char* argv[]){

    // Initialize and populate array with stop/ignore words
    string stopWords[50];
    getStopWords(argv[3],stopWords);

    // Initialize variables to keep track of how many times the array is doubled, and how many stop/common words there are
    int doubleCount = 0;
    int stopWordCount = 0;

    // Initialize wordItem array and fill it with words and counts
    wordItem* wordItemArray = new wordItem[10];

    int wordCount = readFile(argv[2], wordItemArray, stopWords, &doubleCount, &stopWordCount);

    // Sort the wordItem array from high to low, according to the count of each word
    arraySort(wordItemArray,wordCount);

    // Get the total number of non-stop words
    int wordTotal = getTotalNumberNonStopWords(wordItemArray,wordCount);

    cout << "\n";

    // Print out the top N most frequent words
    printTopN(wordItemArray,stoi(argv[1]),wordTotal+stopWordCount,wordCount);

    // Print out the number of times the array was doubled, and the number of unique common words
    cout << "#" << endl;
    cout << "Array doubled: " << doubleCount << endl;
    cout << "#" << endl;
    cout << "Unique non-common words: " << wordCount << endl;
    cout << "#" << endl;
    cout << "Total non-common words: " << wordTotal << endl;

    return 0;
}