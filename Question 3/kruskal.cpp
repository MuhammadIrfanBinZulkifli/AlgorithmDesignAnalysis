#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Edge {
    string src, dest;
    double weight;
};

class Graph {
public:
    vector<Edge> edges;
    
    void addEdge(const string& u, const string& v, double weight) {
        edges.push_back({u, v, weight});
    }
};

class DisjointSets {
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;
    
public:
    void makeSet(const string& s) {
        parent[s] = s;
        rank[s] = 0;
    }
    
    string find(const string& s) {
        if (parent[s] != s) {
            parent[s] = find(parent[s]);
        }
        return parent[s];
    }
    
    void unionSets(const string& u, const string& v) {
        string rootU = find(u);
        string rootV = find(v);
        
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void KruskalMST(Graph& graph) {
    vector<Edge> result;
    DisjointSets ds;

    // #1 : We  define a 'cloud' of sets, one for each vertex
    cout << "Creating sets for each vertex..." << endl;
    for (const auto& edge : graph.edges) {
        ds.makeSet(edge.src);
        ds.makeSet(edge.dest);
    }

    // #2 : We make a priority queue by sorting the edges by weight
    cout << "Sorting edges by weight..." << endl;
    sort(graph.edges.begin(), graph.edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // #3 : We process the edges in sorted order
    cout << "Processing edges in sorted order...\n\n" << endl;
    for (const auto& edge : graph.edges) {
        string rootSrc = ds.find(edge.src);
        string rootDest = ds.find(edge.dest);

        cout << "Considering edge " << edge.src << " - " << edge.dest << " with weight " << edge.weight << endl;
        
        // #4 : We merge the 'clouds' by adding the edge to the MST if the vertices are in different sets
        if (rootSrc != rootDest) {
            cout << "Adding edge " << edge.src << " - " << edge.dest << " to the MST\n" << endl;
            result.push_back(edge);
            ds.unionSets(rootSrc, rootDest);
        } else {
            cout << "Edge " << edge.src << " - " << edge.dest << " forms a cycle and is discarded\n" << endl;
        }
    }

    ofstream outfile("mst_edges.txt");

    cout << "\n-------------------" << endl;
    cout << "Edges in the MST:" << endl;
    cout << "-------------------" << endl;
    double totalWeight = 0;
    for (const auto& edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        outfile << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }

    cout << "\nTotal weight of MST: " << totalWeight << endl;
    outfile << "Total weight of MST: " << totalWeight << endl;
    outfile.close();
}

int main() {
    Graph graph;
    ifstream infile("../Dataset2/edges_details.txt");
    string line;
    
    cout << "\n-----------------------------------------------"
         << "\n|                 Question 3                  |"
         << "\n|     Minimum Spanning Tree (Kruskal's)       |"
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

    cout << "----------------------------------------------" << endl;
    cout << "Running Kruskal's algorithm to find the MST..." << endl;
    cout << "---------------------------------------------- \n" << endl;
    KruskalMST(graph);
    
    return 0;
}
