#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <climits>

using namespace std;

class Graph {
public:
    map<string, vector<pair<string, double>>> adjList;
    
    void addEdge(const string& u, const string& v, double weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // Since the graph is undirected
    }
};

// Custom comparator for the priority queue to generate a min-heap - as pq is a max-heap by default
// We use Min-Heap here because we want to extract the minimum distance node -  the shortest path
class Compare {
public:
    bool operator() (const pair<string, double>& p1, const pair<string, double>& p2) {
        return p1.second > p2.second;
    }
};

void DijkstraDistances(Graph& graph, const string& start) {
    map<string, double> distances;
    map<string, string> previous;
    // #1 : We make a priority queue to store the vertices and their distances
    priority_queue<pair<string, double>, vector<pair<string, double>>, Compare> pq;
    
    // #2 : We initialize the distances of all vertices - aka the one we haven't found yet to infinity
    // except the starting vertex (A) which is set to 0
    cout << "-------------------------" << endl;
    cout << "Initializing distances..." << endl;
    cout << "-------------------------" << endl;
    for (const auto& vertex : graph.adjList) {
        distances[vertex.first] = INT_MAX;
        cout << "Distance from " << start << " to " << vertex.first << " set to infinity." << endl;
    }
    distances[start] = 0;
    cout << "Distance from " << start << " to itself set to 0." << endl;
    
    cout << "\n" << endl;

    // #3 : We add the starting vertex to the priority queue
    pq.emplace(start, 0);
    
    while (!pq.empty()) {
        // #4 : We extract the vertex with the minimum distance from the priority queue
        string u = pq.top().first;
        // #5 : We remove the vertex from the priority queue
        pq.pop();
        cout << "----------------------" << endl;
        cout << "Processing vertex: " << u << endl;
        cout << "----------------------" << endl;
        
        for (const auto& neighbor : graph.adjList[u]) {
            string v = neighbor.first;
            double distance = neighbor.second;
            // #6 : We try to relax the edges
            cout << "Considering edge from " << u << " to " << v << " with distance " << distance << endl;
            
            // #7 : We calculate the alternative path distance
            double alt = distances[u] + distance;
            cout << "Alternative path distance: The total distance from " << start << " to " << v << " is " << alt << endl;
            // #8 : We update the distance if the alternative path is shorter
            if (alt < distances[v]) {
                cout << "Updating distance of " << v << " to " << alt << " (previously " << distances[v] << ")" << endl;
                distances[v] = alt;
                pq.emplace(v, alt);
                previous[v] = u;
                cout << "Edge from " << u << " to " << v << " is relaxed." << endl;
            } else {
                cout << "The alternative path is longer than the current distance of " << distances[v] << " from " << start << " to " << v << endl;
            }
           cout << "\n" << endl;
        }
    }
    
    ofstream outfile("shortest_distance.txt");

    // #9 : We output the final shortest distances
    cout << "-------------------------" << endl;
    cout << "Final shortest distances:" << endl;
    cout << "-------------------------" << endl;
    for (const auto& distance : distances) {
        cout << "Distance from " << start << " to " << distance.first << " is " << distance.second << endl;
        outfile << "Distance from " << start << " to " << distance.first << " is " << distance.second << endl;
    }

    outfile.close();
}


int main() {
    Graph graph;
    ifstream infile("../Dataset2/edges_details.txt");
    string line;

    cout << "\n-----------------------------------------------"
         << "\n|                 Question 3                  |"
         << "\n|   Shortest Path Algorithm (Dijkstra's)      |"
         << "\n-----------------------------------------------\n" << endl;
    
    if (!infile) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    while (getline(infile, line)) {
        istringstream iss(line);
        string u, v;
        double weight;
        if (!(iss >> u >> v >> weight)) {
            break;  // error in reading line
        }
        graph.addEdge(u, v, weight);
    }

    infile.close();

    // Run Dijkstra's algorithm from a starting node, "A"
    DijkstraDistances(graph, "A");
    
    return 0;
}
