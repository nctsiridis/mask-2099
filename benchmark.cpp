#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include "bit_filter_solution.cpp"
#include "standard_solution.cpp"

using namespace std;
using namespace chrono;

vector<int> generate_random_vector(int size, int min_val = -1000000, int max_val = 1000000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);
    vector<int> result(size);
    for (int& x : result) x = dis(gen);
    return result;
}

int main() {
    ofstream csv("data/benchmark_results.csv");
    csv << "InputSize,BitFilterTime_ms,StandardTime_ms\n";

    vector<int> sizes = {1000, 5000, 10000, 50000, 100000, 200000, 5000000, 10000000, 500000000};

    for (int size : sizes) {
        vector<int> input = generate_random_vector(size);
        int k = size / 10;

        // Bit filter
        BitFilterSolution bfs;
        vector<int> nums1 = input;
        auto t1 = high_resolution_clock::now();
        bfs.maxSubsequence(nums1, k);
        auto t2 = high_resolution_clock::now();
        auto bit_time = duration_cast<milliseconds>(t2 - t1).count();

        // Standard
        StandardSolution stds;
        vector<int> nums2 = input;
        auto t3 = high_resolution_clock::now();
        stds.maxSubsequence(nums2, k);
        auto t4 = high_resolution_clock::now();
        auto std_time = duration_cast<milliseconds>(t4 - t3).count();

        csv << size << "," << bit_time << "," << std_time << "\n";
        cout << "Size: " << size << " | BitFilter: " << bit_time << "ms | Standard: " << std_time << "ms\n";
    }

    csv.close();
    return 0;
}
