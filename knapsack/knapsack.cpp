#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to hold the star details
struct Star {
    string name;
    int x, y, z;
    double weight, profit;
};

// Function to print the item weight table
void printItemWeightTable(const vector<Star>& stars) {
    cout << left << setw(15) << "Star"
         << setw(15) << "Weight(kg)"
         << setw(15) << "Benefit" << endl;

    cout << string(45, '-') << endl;
    for (const Star& star : stars) {
        cout << left << setw(15) << star.name
             << setw(15) << star.weight
             << setw(15) << star.profit << endl;
    }
}

// Function to perform the 0/1 Knapsack Algorithm
double knapsack(const vector<Star>& stars, int max_capacity) {
    int n = stars.size(); //Get number of stars
    vector<vector<double>> dp(n + 1, vector<double>(max_capacity + 1, 0)); // 2D vector to store the DP table

    // Build the DP table
    for (int i = 1; i <= n; ++i) { 
        for (int w = 0; w <= max_capacity; ++w) { // Loop through each possible weight
            if (stars[i - 1].weight <= w) { 
                // Take the maximum profit between including and excluding the current star
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - stars[i - 1].weight] + stars[i - 1].profit); 
            } else {
                dp[i][w] = dp[i - 1][w]; // If the current star's weight is greater than the current weight limit, exclude it
            }
        }
    }

    // Store the results in a text file
    ofstream file("knapsack_result.txt");

    file << "Resulting DP Matrix:\n";     
    for (const auto& row : dp) {
        for (double value : row) {
            file << setw(3) << value << ' ';
        }
        file << '\n';
    }

    // To find the items included in the knapsack
    int w = max_capacity;
    int max_profit = dp[n][max_capacity];
    vector<Star> items_included;

    for (int i = n; i > 0 && max_profit > 0; --i) {
        if (max_profit == dp[i-1][w]) {
            continue;
        } else {
            items_included.push_back(stars[i-1]);
            max_profit -= stars[i-1].profit;
            w -= stars[i-1].weight;
        }
    }

    // Reverse the order of items_included to get the correct order
    reverse(items_included.begin(), items_included.end());

    file << "\nList of stars to visit (indices):\n";
    for (const Star& star : items_included) {
        file << star.name << ' ';
    }
    file << '\n';

    file << "\nWeights and profits of selected stars:\n";
    double total_weight = 0;
    double total_profit = 0;
    for (const Star& star : items_included) {
        file << "Star " << star.name << ": Weight = " << star.weight << ", Profit = " << star.profit << '\n';
        total_weight += star.weight;
        total_profit += star.profit;
    }
    file << "\nTotal weight: " << total_weight << '\n';
    file << "Total profit: " << total_profit << '\n';

    file.close();
    return dp[n][max_capacity]; // Return the maximum profit for the given weight limit
}

int main() {

    ifstream infile("../Dataset2/star_details.txt");
    string line;

    cout << "\n-----------------------------------------------"
         << "\n|                 Question 4                  |"
         << "\n|              0/1 Knapsack                   |"
         << "\n-----------------------------------------------\n" << endl;

    if (!infile) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    vector<Star> stars;
    while (getline(infile, line)) {
        istringstream iss(line);
        Star star;
        if (!(iss >> star.name >> star.x >> star.y >> star.z >> star.weight >> star.profit)) {
            break;  // error in reading line
        }
        stars.push_back(star);
    }

    printItemWeightTable(stars);

    int max_capacity = 800;

    // Perform the 0/1 Knapsack Algorithm
    double maxProfit = knapsack(stars, max_capacity);

   
    cout << "Maximum profit for the given weight limit (" << max_capacity << ") is: " << maxProfit << endl;

    return 0;
}
