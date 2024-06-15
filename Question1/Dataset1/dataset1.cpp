#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
using namespace std;

void generateNum(int counter_uniqueNum, string unique_num[], int size, int lengthNum, string fileName) {
    
    ofstream writeFile(fileName);
    if(!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(int i = 0; i < size; i++) {
        string randomStrNum;
        for(int j = 0; j < lengthNum; j++) {
            int randomIndex = rand() % counter_uniqueNum;
            string strDigit = unique_num[randomIndex];
            randomStrNum = randomStrNum + strDigit;
        }
        
        writeFile << stoi(randomStrNum) << " ";
    }

    writeFile.close();
    cout << fileName << " succesfully inserted with random number." << endl;
}

int main() {
    int sizes[6] = {100, 1000, 10000, 100000, 500000, 1000000}; // array containing size of the datasets to be generated
    int getArrayLength = sizeof(sizes) / sizeof(int);
    int groupLeaderID = 1211103115; // Azri Syahmi ID
    srand(groupLeaderID);

    string unique_num[] = {"0", "1", "2", "3", "5"}; // unique number in leader id
    int counter_uniqueNum = 5; // length of unique number

    multimap<int, int> sizeLengthPair = {
        {100, 3}, {1000, 4}, {10000, 5}, {100000, 6}, {500000, 6}, {1000000, 7}
    };

    for(int i = 0; i < getArrayLength; i++) { // loop for generating random numbers for each dataset
        string fileName = "set_" + to_string(i + 1) + ".txt";
        int lengthNum;
        auto range = sizeLengthPair.equal_range(sizes[i]);
        for (auto it = range.first; it != range.second; ++it) {
            lengthNum = it->second;
        }
        
        generateNum(counter_uniqueNum, unique_num, sizes[i], lengthNum, fileName);
    }

    return 0;
}