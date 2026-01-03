#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

bool compareDigitsDescThenPosAsc(const pair<char,int>& a, const pair<char,int>& b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

long long joltage12(string line)
{
    int n = line.size();
    int k = 12;
    
    string result = "";
    int startPos = 0;
    
    for (int i = 0; i < k; i++) {
        int remaining = k - i - 1;
        int endPos = n - remaining;
        
        char maxDigit = '0';
        int maxPos = startPos;
        
        for (int j = startPos; j < endPos; j++) {
            if (line[j] > maxDigit) {
                maxDigit = line[j];
                maxPos = j;
            }
        }
        
        result += maxDigit;
        startPos = maxPos + 1;
    }
    
    long long num = 0;
    for (char c : result) {
        num = num * 10 + (c - '0');
    }
    
    return num;
}

int main()
{
    ifstream inputFile("input.txt");
    string line;
    
    long long totalSum = 0;
    while (getline(inputFile, line))
    {
        if (!line.empty())
        {
            totalSum += joltage12(line);
        }
    }
    cout << totalSum << endl;
    return 0;
}
