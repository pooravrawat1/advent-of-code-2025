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

long long countPaths(string current, string target, unordered_map<string, long long>& localMemo) {
    if (current == target) return 1;
    if (localMemo.count(current)) return localMemo[current];

    long long total = 0;
    for (const string& neighbor : adj[current]) {
        total += countPaths(neighbor, target, localMemo);
    }
    return localMemo[current] = total;
}

long long getPaths(string start, string end) {
    memo.clear(); 
    return countPaths(start, end, memo);
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

    long long s_to_dac = getPaths("svr", "dac");
    long long dac_to_fft = getPaths("dac", "fft");
    long long fft_to_out = getPaths("fft", "out");
    long long totalSeq1 = s_to_dac * dac_to_fft * fft_to_out;

    long long s_to_fft = getPaths("svr", "fft");
    long long fft_to_dac = getPaths("fft", "dac");
    long long dac_to_out = getPaths("dac", "out");
    long long totalSeq2 = s_to_fft * fft_to_dac * dac_to_out;

    long long finalAnswer = totalSeq1 + totalSeq2;

    cout << finalAnswer << endl;

    return 0;
}