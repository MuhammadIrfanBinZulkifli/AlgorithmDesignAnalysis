#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
using namespace std;

void generateNum(mt19937 &gen, int size, string fileName) {
    
    ofstream writeFile(fileName);
    if(!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(int i = 0; i < size; i++) {
        uniform_int_distribution<> distr(1, size); // Define the range from 1 to range of number
        int randomNum = distr(gen); // Generate the random number
        writeFile << randomNum << " ";
    }

    writeFile.close();
    cout << fileName << " succesfully inserted with random number." << endl;
}

int main() {
    int sizes[6] = {100, 1000, 10000, 100000, 500000, 1000000}; // array containing size of the datasets to be generated
    int getArrayLength = sizeof(sizes) / sizeof(int);
    int groupLeaderID = 1211103115; // Azri Syahmi ID
    mt19937 gen(groupLeaderID); // mt19937 instatiated with the gen as instance with the seed value of groupLeaderID
    
    for(int i = 0; i < getArrayLength; i++) { // loop for generating random numbers for each dataset
        string fileName = "set_" + to_string(i + 1) + ".txt";
        generateNum(gen, sizes[i], fileName);
    }

    return 0;
}