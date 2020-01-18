Who:
    Author: Jake Bonner
    Course: CSCI 2270 - Data Structures
    Project/Assignment: Homework 2 - Word Analysis

What:
    Files:
        README.txt:
            The purpose of this file is to inform others of this folder so they can understand what it is for, and how to use the programs contained in the files.
            It Contains information about the author, the files in the folder, and how to run the programs.
        assignment2.cpp:
            The purpose of this file is to create and execute the programs which accomplish the task at hand. It reads a given text file, stores unique words from the
            file and their number of occurrences in an array of structs, dynamically allocates memory and doubles the array to include more words, and displays the top n
            number of most frequent words, as well as the total number of uncommon words.
            
    The program:
            The program that can be executed by compiling the files in this folder reads a text file and stores the unique words found in the file in
            a dynamically allocated array, and calculates and outputs the following information:
                ● The top n words, and the number and percentage of times each word was found
                ● The number of different uncommon words in the file
                ● The total number of uncommon words in the file
                ● The number of array doublings needed to store all unique words in the file
            First, the program reads in a file that contains the 50 most common words in the English language, and stores these words in an array. Then, it reads a text
            file entered by the user, and, ignoring the 50 common words from the other file, fills an array with each unique word in the file, and counts how many times
            each word appears. Once the whole text file has been read, the program calculates and displays the top n (entered by the user) most frequent words and the
            percentage they appear out of all words in the file. Also, it prints out the number of times the array was doubled, how many unique non-common 
            words there are in the text, and the total number of non-common words.

            How the array is stored and how the size is doubled:
                The array of structs is initialized dyanamically in the main function of assignment2.cpp with an initial size of 10. Then, as the file is read
                the array is passed by reference and a new array is created dyanamically to allocate more memory for additional words. Then, the old array is deleted,
                and this process continues until the whole text file has been read and all words are stored.

How:

    Compiling the code:
        The user must do so with a c++ compiler, followed by the name of the file to compile. For example: g++ -std=c++11 assignment2.cpp -o Assignment2
        
    Running the program:
        Then to run the program, the user would write the name of the executable, the number of most frequent words they wish to see from the file, the name of the 
        the text file to read in the program and count the words from, and the name of the file with the stop words included in it.
        For example: ./Assignment2 10 Tom_Sawyer.txt ignoreWords.txt