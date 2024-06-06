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
    
    void addEdge(const string& u, const string& v, double distance) {
        adjList[u].emplace_back(v, distance);
        adjList[v].emplace_back(u, distance); // Since the graph is undirected
    }
};

class Compare {
public:
    bool operator() (const pair<string, double>& p1, const pair<string, double>& p2) {
        return p1.second > p2.second;
    }
};

void DijkstraDistances(Graph& graph, const string& start) {
    map<string, double> distances;
    map<string, string> previous;
    priority_queue<pair<string, double>, vector<pair<string, double>>, Compare> pq;
    
    // Initialize distances
    cout << "Initializing distances..." << endl;
    for (const auto& vertex : graph.adjList) {
        distances[vertex.first] = INT_MAX;
        cout << "Distance from " << start << " to " << vertex.first << " set to infinity." << endl;
    }
    distances[start] = 0;
    cout << "Distance from " << start << " to itself set to 0." << endl;
    
    pq.emplace(start, 0);
    
    while (!pq.empty()) {
        string u = pq.top().first;
        pq.pop();
        cout << "\nProcessing vertex: " << u << endl;
        
        for (const auto& neighbor : graph.adjList[u]) {
            string v = neighbor.first;
            double distance = neighbor.second;
            cout << "Considering edge from " << u << " to " << v << " with distance " << distance << endl;
            
            double alt = distances[u] + distance;
            cout << "Alternative path distance: The total distance from " << start << " to " << v << " is " << alt << endl;
            if (alt < distances[v]) {
                cout << "Updating distance of " << v << " to " << alt << " (previously " << distances[v] << ")" << endl;
                distances[v] = alt;
                pq.emplace(v, alt);
                previous[v] = u;
            }
        }
    }
    
    // Open the output file once, before the loop
    ofstream outfile("shortest_distance.txt");

    // Output the distances from the start node to each other node
    cout << "\nFinal shortest distances:" << endl;
    for (const auto& distance : distances) {
        cout << "Distance from " << start << " to " << distance.first << " is " << distance.second << endl;
        outfile << "Distance from " << start << " to " << distance.first << " is " << distance.second << endl;
    }

    // Close the output file
    outfile.close();
}

int main() {
    Graph graph;
    ifstream infile("../Dataset2/edges_details.txt");
    string line;
    
    if (!infile) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    while (getline(infile, line)) {
        istringstream iss(line);
        string u, v;
        double distance;
        if (!(iss >> u >> v >> distance)) {
            break;  // error in reading line
        }
        graph.addEdge(u, v, distance);
    }

    infile.close();

    // Run Dijkstra's algorithm from a starting node, "A"
    DijkstraDistances(graph, "A");
    
    return 0;
}
