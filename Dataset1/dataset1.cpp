#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

void generateNum(int groupLeaderID, int size, string fileName) {
    
    ofstream writeFile(fileName);
    if(!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(int i = 0; i < size; i++) {
        int randomNum = rand() % 1000 + 1;
        writeFile << randomNum << " ";
    }

    writeFile.close();
    cout << fileName << " succesfully inserted with random number." << endl;
}

int main() {
    int sizes[6] = {100, 1000, 10000, 100000, 500000, 1000000};
    int getArrayLength = sizeof(sizes) / sizeof(int);
    int groupLeaderID = 1211103115; // Azri Syahmi ID
    srand(groupLeaderID);
    
    for(int i = 0; i < getArrayLength; i++) {
        string fileName = "set_" + to_string(i + 1) + ".txt";
        generateNum(groupLeaderID, sizes[i], fileName);
    }

    return 0;
}