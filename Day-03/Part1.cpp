#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

int joltage(string line)
{
    char first_digit = '0';
    int first_pos = 0;
    char second_digit = '0';
    for (int i = 0; i < line.size() - 1; i++)
    {
        if (line[i] > first_digit)
        {
            first_digit = line[i];
            first_pos = i;
        }
    }

    for (int j = first_pos + 1; j < line.size(); j++)
    {
        if (line[j] > second_digit)
        {
            second_digit = line[j];
        }
    }

    return (first_digit - '0') * 10 + (second_digit - '0');
}

long long solve(string input)
{
    long long totalSum = 0;
    stringstream ss(input);
    string line;
    while (getline(ss, line))
    {
        totalSum += joltage(line);
    }
    return totalSum;
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
            totalSum += joltage(line);
        }
    }
    cout << totalSum << endl;
    return 0;
}