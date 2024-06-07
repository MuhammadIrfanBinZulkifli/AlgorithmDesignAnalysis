#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest!= i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void readFile(int arr[], int n, int fileNum) {
    string fileName = "../Dataset1/set_" + to_string(fileNum) + ".txt";
    ifstream inputFile(fileName);
    int count = 0;
    if (inputFile.is_open()) {
        string line;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;
            while (ss >> token && count < n) {
                int number = stoi(token); // Convert string to int
                arr[count++] = number; // Store the number in the array
            }
        }
        inputFile.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

void writeFiles(int arr[], int n, int fileNum) {
    string fileName = "set_" + to_string(fileNum) + "_sorted.txt";
    ofstream writeFile(fileName);
    if (!writeFile.is_open()) {
        cerr << "Error: file can't be opened" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        writeFile << arr[i] << " ";
    }

    writeFile.close();
}

int main() {

    const int sizesArray = 6;
    int sizes[sizesArray] = {100, 1000, 10000, 100000, 500000, 1000000};

    for (int i = 0; i < sizesArray; i++) {

        int* arr = new int[sizes[i]];
        readFile(arr, sizes[i], i + 1);
        auto start = chrono::system_clock::now();
        heapSort(arr, sizes[i]);
        auto endss = chrono::system_clock::now();
        chrono::duration<double> duration = endss - start;
        cout << "Time taken to heap sort array with size of " << sizes[i] << ": " << duration.count() << "s" << endl;
        writeFiles(arr, sizes[i], i + 1);

    }
}