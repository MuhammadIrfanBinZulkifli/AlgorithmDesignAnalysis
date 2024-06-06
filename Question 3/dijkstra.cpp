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
    for (const auto& vertex : graph.adjList) {
        distances[vertex.first] = INT_MAX;
    }
    distances[start] = 0;
    
    pq.emplace(start, 0);
    
    while (!pq.empty()) {
        string u = pq.top().first;
        pq.pop();
        
        for (const auto& neighbor : graph.adjList[u]) {
            string v = neighbor.first;
            double weight = neighbor.second;
            
            double alt = distances[u] + weight;
            if (alt < distances[v]) {
                distances[v] = alt;
                pq.emplace(v, alt);
                previous[v] = u;
            }
        }
    }
    
    // Open the output file once, before the loop
    ofstream outfile("shortest_distance.txt");

    // Output the distances from the start node to each other node
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
