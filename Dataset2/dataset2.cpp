#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath> 
using namespace std;

struct Star { // stars structure containing members of name, x, y, z, weight, and profit of the stars.
    string name;
    int x, y, z;
    int weight;
    int profit;
};

// function used to generate the star details and write in the text file
void starInfoGenerator(vector<Star>& stars, string naming[], unsigned long long int memberID, int starsNum) {
    
    string fileName = "star_details.txt"; // filename to be used to store the stars details
    ofstream writeFile(fileName); // create ofstream object to write the file of fileName

    if(!writeFile.is_open()) { // check if the file is open
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(int i = 0; i < starsNum; i++) {

        string starName = "star_" + naming[i]; // get the stars name
        int x = rand() % 500 + 1; // generate the x-coordinate
        int y = rand() % 500 + 1; // generate the y-coordinate
        int z = rand() % 500 + 1; // generate the z-coordinate
        int weight = rand() % 100 + 1; // generate the weight
        int profit = rand() % 100 + 1; // generate the profit
        stars.push_back({starName, x, y, z, weight, profit}); // create the structures of stars and push to the stars vector
        writeFile << starName << " " << x << " " << y << " " << z << " " << weight << " " << profit << endl; // write the details into the "stars_details.txt"
    }
    
    writeFile.close();
}

// function used to calculate distance between two stars
double calculateDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2)); // return the distance calculated between two stars based on the coordinates of x, y, z
}

// function used to record the edges based on the pre-designed graph
void edgesRecorder(vector<Star> stars) {
    string fileName = "edges_details.txt"; // file naming
    multimap<string, string> edgesPair = { // map that containing pair of vertices that form edges according to the pre-designed graph
        {"A", "B"}, {"A", "C"}, {"A", "D"}, {"A", "E"}, {"A", "O"}, {"A", "R"}, {"B", "O"}, {"B", "D"}, {"B", "C"}, {"C", "E"},
        {"C", "R"}, {"D", "O"}, {"D", "E"}, {"D", "F"}, {"D", "G"}, {"D", "P"}, {"E", "R"}, {"E", "S"}, {"E", "H"}, {"E", "F"},
        {"F", "S"}, {"F", "H"}, {"F", "G"}, {"F", "P"}, {"G", "H"}, {"G", "I"}, {"G", "J"}, {"G", "Q"}, {"G", "P"}, {"H", "S"},
        {"H", "T"}, {"H", "K"}, {"H", "I"}, {"I", "T"}, {"I", "K"}, {"I", "J"}, {"I", "Q"}, {"J", "K"}, {"J", "L"}, {"J", "M"}, 
        {"J", "Q"}, {"K", "T"}, {"K", "N"}, {"K", "L"}, {"L", "M"}, {"L", "N"}, {"M", "N"}, {"M", "Q"}, {"N", "T"}, {"O", "R"},
        {"O", "P"}, {"P", "Q"}, {"R", "S"}, {"S", "T"}
    };

    ofstream writeFile(fileName); // create ofstream object to write the file
    if(!writeFile.is_open()) { // check if the file is open
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for(const auto& pair: edgesPair) { // iterate through the edgesPair multimap
        string name1 = "star_" + pair.first; // name for the first stars
        string name2 = "star_" + pair.second; // name for the second stars

        const Star* star1 = nullptr; // declare a pointer of const Star structure and appoint it with nullptr
        const Star* star2 = nullptr;

        for(const auto& star: stars) { // iterate through the stars vector to find the match stars and assign it to the star1 and star2
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
            double distance = calculateDistance(star1->x, star1->y, star1->z, star2->x, star2->y, star2->z); // calculate distance
            writeFile << pair.first << " " << pair.second << " " << fixed << setprecision(2) << distance << endl; // write into edges_details.txt
        }
    }

}

int main() {

    // add all of the members studentID for the random seed reference
    unsigned long long int memberID = 1211103094ULL + 1211103424ULL + 1211104288ULL; 
    const int starsNum = 20; // total stars numbers to be generated
    vector<Star> stars; // vector that containing structures of all stars generated
    string naming[20]; // array for the stars naming purposes

    // for loop to add the naming into the naming array
    for (int i = 0; i < 20; i++) { 
        naming[i] = char('A' + i);
    } 

    srand(memberID); // use the srand function to seed the random number generator with the memberID
    starInfoGenerator(stars, naming, memberID, starsNum); // call starInfoGenerator to generate the stars
    edgesRecorder(stars); // call edgesRecorder method to record the edges with the distance for each edge
    return 0;
}