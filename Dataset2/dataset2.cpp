#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <cmath> 
using namespace std;

struct Star {
    string name;
    int x, y, z;
    int weight;
    int profit;
};

void starInfoGenerator(vector<Star>& stars, unordered_map<int, string> naming, unsigned long long int memberID, int starsNum) {
    
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
        vector<int> details = {x, y, z, weight, profit};
        stars.push_back({starName, x, y, z, weight, profit});
        writeFile << starName << " " << x << " " << y << " " << z << " " << weight << " " << profit << endl;
    }
    
    writeFile.close();
}

double calculateDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

void edgesRecorder(unordered_map<int, string> naming, vector<Star> stars) {
    string fileName = "edges_details.txt";
    unordered_multimap<string, string> edgesPair = {
        {"A", "B"}, {"A", "C"}, {"A", "D"}, {"A", "E"}, {"A", "O"}, {"A", "R"}, {"B", "O"}, {"B", "D"}, {"B", "C"}, {"C", "E"},
        {"C", "R"}, {"D", "O"}, {"D", "E"}, {"D", "F"}, {"D", "G"}, {"D", "P"}, {"E", "R"}, {"E", "S"}, {"E", "H"}, {"E", "F"},
        {"F", "S"}, {"F", "H"}, {"F", "G"}, {"F", "P"}, {"G", "H"}, {"G", "I"}, {"G", "J"}, {"G", "Q"}, {"G", "P"}, {"H", "S"},
        {"H", "T"}, {"H", "K"}, {"H", "I"}, {"I", "T"}, {"I", "K"}, {"I", "J"}, {"I", "Q"}, {"J", "K"}, {"J", "L"}, {"J", "M"}, 
        {"J", "Q"}, {"K", "T"}, {"K", "N"}, {"K", "L"}, {"L", "M"}, {"L", "N"}, {"M", "N"}, {"M", "Q"}, {"N", "T"}, {"O", "R"},
        {"O", "P"}, {"P", "Q"}, {"R", "S"}, {"S", "T"}
    };

    ofstream writeFile(fileName);
    if(!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(const auto& pair: edgesPair) {
        string name1 = "star_" + pair.first;
        string name2 = "star_" + pair.second;

        const Star* star1 = nullptr;
        const Star* star2 = nullptr;

        for(const auto& star: stars) {
            if (star.name == name1) {
                star1 = &star;
            } else if (star.name == name2) {
                star2 = &star;
            }
            if (star1 && star2) {
                break;
            }
        }

        if (star1 && star2) {
            double distance = calculateDistance(star1->x, star1->y, star1->z, star2->x, star2->y, star2->z);
            writeFile << pair.first << " " << pair.second << " " << fixed << setprecision(2) << distance << endl;
        }
    }

}

int main() {
    unsigned long long int memberID = 1211103094ULL + 1211103424ULL + 1211104288ULL;
    const int starsNum = 20;
    // vector<vector<int>> stars;
    vector<Star> stars;
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
    srand(memberID);
    starInfoGenerator(stars, naming, memberID, starsNum);
    edgesRecorder(naming, stars);
    return 0;
}