#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <unordered_map>
using namespace std;

void starInfoGenerator(unsigned long long int memberID, int starsNum) {

    unordered_map<int, string> naming = {
        {0, "A"},
        {1, "B"},
        {2, "C"},
        {3, "D"},
        {4, "E"},
        {5, "F"},
        {6, "G"},
        {7, "H"},
        {8, "I"},
        {9, "J"},
        {10, "K"},
        {11, "L"},
        {12, "M"},
        {13, "N"},
        {14, "O"},
        {15, "P"},
        {16, "Q"},
        {17, "R"},
        {18, "S"},
        {19, "T"},
    };  
    
    string fileName = "star_details.txt";
    ofstream writeFile(fileName);

    if(!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(int i = 0; i < starsNum; i++) {

        string starName = "star_" + naming[i];
        int x = rand() % 500 + 1;
        int y = rand() % 500 + 1;
        int z = rand() % 500 + 1;
        int weight = rand() % 100 + 1;
        int profit = rand() % 100 + 1;

        writeFile << starName << " " << x << " " << y << " " << z << " " << weight << " " << profit << endl;
    }
    
    writeFile.close();
}

int main() {
    unsigned long long int memberID = 1211103094ULL + 1211103424ULL + 1211104288ULL;
    const int starsNum = 20;
    srand(memberID);
    starInfoGenerator(memberID, starsNum);
    return 0;
}