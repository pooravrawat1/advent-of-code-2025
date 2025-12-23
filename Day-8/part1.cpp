#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

struct Point
{
    int id;
    long long x, y, z;
};

struct Edge
{
    long long dist;
    int u, v;
};

int main()
{
    ifstream infile("input.txt");
}

bool compareEdges(const Edge &)