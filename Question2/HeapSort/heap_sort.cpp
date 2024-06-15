#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <vector>

using namespace std;

// Priority Queue class using max heap
template <typename T>
class PriorityQueue {
    vector<T> A;
    void heapify_enqueue(int index) {
        if (index == 0)
            return;

        int parent_index = (index - 1) / 2;
        if (A[index] > A[parent_index]) {
            swap(A[index], A[parent_index]);
            heapify_enqueue(parent_index);
        }
    }

    void heapify_dequeue(int index) {
        int max;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < A.size() && A[left] > A[index])
            max = left;
        else
            max = index;

        if (right < A.size() && A[right] > A[max])
            max = right;

        if (max != index) {
            swap(A[index], A[max]);
            heapify_dequeue(max);
        }
    }

public:
    void enqueue(T element) {
        A.push_back(element);
        heapify_enqueue(A.size() - 1);
    }

    T dequeue() {
        T removed_element = A[0];
        A[0] = A[A.size() - 1];
        A.pop_back();
        heapify_dequeue(0);
        return removed_element;
    }

    int size() {
        return A.size();
    }
};

// Function to read data from file
void readFile(int arr[], int n, int fileNum) {
    string fileName = "../../Question1/Dataset1/set_" + to_string(fileNum) + ".txt";
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

// Function to write data to file
void writeFiles(int arr[], int n, int fileNum) {
    string fileName = "set_" + to_string(fileNum) + "_sorted" + ".txt";
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

        PriorityQueue<int> pq;

        // Measure enqueue time
        auto start_enqueue = chrono::system_clock::now();
        for (int j = 0; j < sizes[i]; j++) {
            pq.enqueue(arr[j]);
        }
        auto end_enqueue = chrono::system_clock::now();
        chrono::duration<double> duration_enqueue = end_enqueue - start_enqueue;
        cout << "Time taken to enqueue array with size of " << sizes[i] << ": " << duration_enqueue.count() << "s" << endl;

        // Measure dequeue time
        auto start_dequeue = chrono::system_clock::now();
        for (int j = 0; j < sizes[i]; j++) {
            arr[j] = pq.dequeue();
        }
        auto end_dequeue = chrono::system_clock::now();
        chrono::duration<double> duration_dequeue = end_dequeue - start_dequeue;
        cout << "Time taken to dequeue array with size of " << sizes[i] << ": " << duration_dequeue.count() << "s" << endl;

        // Store the sorted data after dequeueing
        writeFiles(arr, sizes[i], i + 1);
        delete[] arr;
    }

    return 0;
}
