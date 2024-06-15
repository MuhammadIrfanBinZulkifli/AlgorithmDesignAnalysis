#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
using namespace std;

void selectionSort(int arr[], int n) {
    for(int i = n - 1; i > 0; i--) {
        int maxIndex = i; // set maxIndex to i
        for(int j = 0; j < i; j++) {
            if(arr[j] > arr[maxIndex]) { // check if the element is bigger than the element at maxIndex
                maxIndex = j;
            }
        }
        if(maxIndex != i) {
            swap(arr[i], arr[maxIndex]); // swap the element at arr[i] with arr[maxIndex]
        }
    }
}

void readFile(int arr[], int n, int fileNum) { // method to read the file from generated in dataset1
    string fileName = "../../Question1/Dataset1/set_" + to_string(fileNum) + ".txt";
    ifstream inputFile(fileName);
    int count = 0;
    if (inputFile.is_open()) {
        string line;
        
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;
            while (ss >> token && count < n) {
                int number = stoi(token); // Convert string to int
                arr[count++] = number; // Store the number in the array
            }
        }
        inputFile.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

void writeFiles(int arr[], int n, int fileNum) { // method to write the sorted dataset into a text file
    string fileName = "set_" + to_string(fileNum) + "_sorted.txt";
    ofstream writeFile(fileName);
    if(!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(int i = 0; i < n; i++) {
        writeFile << arr[i] << " ";
    }

    writeFile.close();
}

int main() {

    const int sizesArray = 6;
    int sizes[sizesArray] = {100, 1000, 10000, 100000, 500000, 1000000};
    
    for(int i = 0; i < sizesArray; i++) { // loop through from 0 to 5 to read each dataset

        int* arr = new int[sizes[i]]; // dynamically declare an array of integers with the size of sizes[i]
        readFile(arr, sizes[i], i + 1);
        auto start = chrono::system_clock::now(); // get the current time upon the starting time of selection sort method
        selectionSort(arr, sizes[i]); // call selection sort method
        auto endss = chrono::system_clock::now(); // get the current time upon the end time of selection sort method
        chrono::duration<double> duration = endss - start; // get the duration of the selection sort to complete the sorting
        cout << "Time taken to selection sort array with size of " << sizes[i] << ": " << duration.count() << "s" << endl;
        writeFiles(arr, sizes[i], i+1);

    }
}