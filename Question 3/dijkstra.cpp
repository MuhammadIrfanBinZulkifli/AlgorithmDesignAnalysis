#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Star {
    string name;
    int x, y, z, weight, profit;

    Star(string name, int x, int y, int z, int weight, int profit) 
        : name(name), x(x), y(y), z(z), weight(weight), profit(profit) {}

    // Overload the less than operator to compare stars based on their weight
    bool operator<(const Star& other) const {
        return weight > other.weight;  // Min-heap based on weight
    }
};

// Retrieve star details from the star_details.txt file (GeeksforGeeks, 2024)
vector<Star> readStarDetails() {
    vector<Star> stars;
    ifstream inputFile("Dataset2/star_details.txt");

    if (!inputFile) {
        cerr << "Error: Could not open the file " << endl;
        return stars;  // Return an empty vector
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string name;
        int x, y, z, weight, profit;
        if (iss >> name >> x >> y >> z >> weight >> profit) {
            stars.emplace_back(name, x, y, z, weight, profit);
        } else {
            cerr << "Error: Could not parse the line: " << line << endl;
        }
    }
    return stars;
}

// Creating a priority queue of stars based on their weights
priority_queue<Star> createPriorityQueue(const vector<Star>& stars) {
    priority_queue<Star> pq;
    for (const auto& star : stars) {
        pq.push(star);
    }
    return pq;
}

int main() {
    // Reading star details from the file with a hardcoded path
    vector<Star> stars = readStarDetails();

    if (stars.empty()) {
        cerr << "Error: No stars were read from the file." << endl;
        return 1;  // Exit the program with an error code
    }

    // Creating a priority queue with the stars
    priority_queue<Star> pq = createPriorityQueue(stars);

    if (pq.empty()) {
        cerr << "Error: Priority queue is empty." << endl;
        return 1;  // Exit the program with an error code
    }

    // Printing stars in the order of their weights
    while (!pq.empty()) {
        Star star = pq.top();
        pq.pop();
        cout << star.name << ": Weight = " << star.weight << ", Profit = " << star.profit << endl;
    }

    return 0;
}


// References:
// Newman, D. (2014). dtnewman/djikstra_shortest_path. GitHub. https://github.com/dtnewman/djikstra_shortest_path
// GeeksforGeeks. (2024, February 22). How to read from a file in C? GeeksforGeeks. https://www.geeksforgeeks.org/how-to-read-from-a-file-in-cpp/