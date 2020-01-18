// Recitation 1 Assignment
// Author: Jake Bonner
// CSCI 2270 Summer 2019
// Recitation: 311

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sieveMethod(bool nums[], int size){
    for(int i=0; i<size; i++){
        nums[i] = true;
    }
    for(int i=2; i<size; i++){ 
        for(int j=2; j<32; j++){
            if(i%j == 0 && i!=j){
                nums[i] = false;
            }
        }
    }
}

int getNumCount(string fileName){
    int numberCount = -1;
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){
        string line;
        getline(myfile,line);
        numberCount = stoi(line);
    }
    return numberCount;
}

void readFile(string fileName,int fileNums[],int arrSize){
    ifstream myfile;
    myfile.open(fileName);
    if(myfile.is_open()){
        string line;
        int lineCount = 0;
        while(getline(myfile,line)){
            if(lineCount <= arrSize){
                if(lineCount != 0){
                    fileNums[lineCount-1] = stoi(line);
                }
                lineCount++;
            }
        }
    }
}

void stdOut(bool primeOrComp[1000],int fileNumbers[],int size){
    for(int i=0; i<size; i++){
        cout << fileNumbers[i];
        if(primeOrComp[fileNumbers[i]]){
            cout << " prime" << endl;
        }
        else{
            cout << " composite" << endl;
        }
    }
}

int main(){
    const static int size = 1000;

    bool primeCheck[size];
    sieveMethod(primeCheck,size);

    int numberCount = getNumCount("input.txt");
    if(numberCount != -1){
        int numsInFile[numberCount];
        readFile("input.txt",numsInFile,numberCount);
        stdOut(primeCheck,numsInFile,numberCount);
    }
    else{
        cout << "File not found" << endl;
    }

    return 0;
}