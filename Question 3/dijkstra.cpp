#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <cmath> 
#include <iomanip>

using namespace std;

// Structure to represent a star
struct Star {
    string name;
    int x, y, z, weight;

    Star(string name, int x, int y, int z, int weight) 
        : name(name), x(x), y(y), z(z), weight(weight) {}
};

// Function to calculate the Euclidean distance between two stars
double calculateDistance(const Star& s1, const Star& s2) {
    return sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2) + pow(s2.z - s1.z, 2));
}

// Function to retrieve star details from the file (GeeksforGeeks, 2024)
vector<Star> readStarDetails(const string& filePath) {
    vector<Star> stars;
    ifstream file(filePath);

    if (!file) {
        cerr << "Error: Could not open the file " << filePath << endl;
        return stars;  // Return an empty vector
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        int x, y, z, weight;
        if (iss >> name >> x >> y >> z >> weight) {
            stars.emplace_back(name, x, y, z, weight);
        } else {
            cerr << "Error: Could not parse the line: " << line << endl;
        }
    }
    return stars;
}

// Function to create a graph of stars and their distances
vector<vector<double>> createGraph(const vector<Star>& stars) {
    vector<vector<double>> graph(stars.size(), vector<double>(stars.size(), 0.0));
    for (size_t i = 0; i < stars.size(); ++i) {
        for (size_t j = 0; j < stars.size(); ++j) {
            if (i != j) {
                graph[i][j] = calculateDistance(stars[i], stars[j]);
            }
        }
    }


    // Print the adjacency matrix

    cout << "Adjacency matrix of the graph:" << endl;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph[i].size(); ++j) {
            cout << fixed << setprecision(2) << graph[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n" << endl;
    
    return graph;    
}

// Dijkstra's algorithm to find the shortest distances from source star (Nerdylicious, 2015).
vector<double> DijkstraDistances(const vector<vector<double>>& graph, int source) {
    int n = graph.size();
    
    // Initializing distances to infinity
    vector<double> distances(n, INFINITY); 
    distances[source] = 0.0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0.0, source});

    vector<bool> visited(n, false);

    cout << "Dijkstra's Algorithm Steps:" << endl;
    while (!pq.empty()) {
        double dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        cout << "Step " << u + 1 << ": Selected star " << u << ", Distance from source: " << distances[u] << endl;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                // Update shortest distance if new distance is smaller (Nerdylicious, 2015).
                double new_dist = dist + graph[u][v];
                if (new_dist < distances[v]) {
                    distances[v] = new_dist;
                    pq.push({new_dist, v});
                }
            }
        }
    }

    cout << "\nDijkstra's algorithm completed.\n" << endl;

    return distances;
}

int main() {

    // Printing the program details 
    cout << "\n--------------------------------------------" << endl;
    cout << "Question 3a)" << endl;
    cout << "Program to identify the shortest paths from Star" << endl;
    cout << "A to the other stars using Dijkstra’s Algorithm" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "\n" << endl;

    string filePath = "../Dataset2/star_details.txt";
    vector<Star> stars = readStarDetails(filePath);

    if (stars.empty()) {
        cerr << "Error: No stars were read from the file." << endl;
        return 1;  // Exit the program with an error code
    }

    // Printing the star details
    cout << "Star details: " << endl;
    for (const Star& star : stars) {
        cout << star.name << " " << star.x << " " << star.y << " " << star.z << " " << star.weight << endl;
    }

    cout << "\n" << endl;

    vector<vector<double>> graph = createGraph(stars);

    int source = 0; // Assuming source star index
    vector<double> distances = DijkstraDistances(graph, source);

    // Output shortest distances from source star
    for (size_t i = 0; i < distances.size(); ++i) {
        cout << "Shortest distance from " << stars[source].name << " to " << stars[i].name << ": " << distances[i] << endl;
    }

    // Output shortest distances from source star
    ofstream file("shortest_distances.txt");
    for (size_t i = 0; i < distances.size(); ++i) {
        file << "Shortest distance from " << stars[source].name << " to " << stars[i].name << ": " << distances[i] << std::endl;
    }
    file.close();
}

// References:
// Nerdylicious. (2015) DijkstraShortestPath: Implementation of Dijkstra’s algorithm in C++ which finds the shortest path from a start node to every other node in a weighted graph. GitHub. https://github.com/Nerdylicious/DijkstraShortestPath
// GeeksforGeeks. (2024, February 22). How to read from a file in C? GeeksforGeeks. https://www.geeksforgeeks.org/how-to-read-from-a-file-in-cpp/