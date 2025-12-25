#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Point
{
    long long x, y, z;
};

struct Edge
{
    int u, v;
    long long distSq;
};

bool compareEdges(const Edge &a, const Edge &b)
{
    if (a.distSq != b.distSq)
        return a.distSq < b.distSq;
    if (a.u != b.u)
        return a.u < b.u;
    return a.v < b.v;
}

struct DSU
{
    vector<int> parent;
    int numComponents;

    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
        numComponents = n;
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
        {
            parent[root_i] = root_j;
            numComponents--;
            return true;
        }
        return false;
    }
};

int main()
{
    ifstream infile("input.txt");
    vector<Point> points;
    string line;

    while (getline(infile, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string val;
        vector<long long> coords;
        while (getline(ss, val, ','))
            coords.push_back(stoll(val));
        if (coords.size() == 3)
            points.push_back({coords[0], coords[1], coords[2]});
    }

    int n = points.size();
    if (n < 2)
        return 0;

    vector<Edge> edges;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            long long dx = points[i].x - points[j].x;
            long long dy = points[i].y - points[j].y;
            long long dz = points[i].z - points[j].z;
            edges.push_back({i, j, dx * dx + dy * dy + dz * dz});
        }
    }

    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);
    long long finalResult = 0;

    for (const auto &edge : edges)
    {
        if (dsu.unite(edge.u, edge.v))
        {
            if (dsu.numComponents == 1)
            {
                finalResult = points[edge.u].x * points[edge.v].x;
                break;
            }
        }
    }

    cout << finalResult << endl;

    return 0;
}
