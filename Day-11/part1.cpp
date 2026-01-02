#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<string>> adj;
unordered_map<string, long long> memo;

long long countPaths(string current) {
    if (current == "out") return 1;
    if (memo.count(current)) return memo[current];

    long long total = 0;
    for (const string& neighbor : adj[current]) {
        total += countPaths(neighbor);
    }
    memo[current] = total;
    return total;
}

int main() {
    ifstream infile("input.txt");
    string line;

    while (getline(infile, line)) {
        stringstream ss(line);
        string device, neighbor;
        ss >> device;
        if (device.back() == ':') device.pop_back();
        while (ss >> neighbor) {
            adj[device].push_back(neighbor);
        }
    }
    cout << countPaths("you") << endl;
    return 0;
}   