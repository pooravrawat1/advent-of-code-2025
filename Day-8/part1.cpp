#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
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
    return a.distSq < b.distSq;
}
struct DSU
{
    vector<int> parent;
    vector<int> sz;

    DSU(int n)
    {
        parent.resize(n);
        sz.assign(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int i)
    {
        if (parent[i] != i)
        {
            return parent[i] = find(parent[i]);
        }
        return i;
    }

    void unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
        {
            if (sz[root_i] < sz[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
};

int main()
{
    ifstream infile("input.txt");
    string line;
    vector<Point> points;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string val;
        vector<long long> coords;
        while (getline(ss, val, ','))
        {
            coords.push_back(stoll(val));
        }
        if (coords.size() == 3)
        {
            points.push_back({coords[0], coords[1], coords[2]});
        }
    }

    int n = points.size();
    if (n < 3)
        return 0;
    vector<Edge> edges;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            long long dx = points[i].x - points[j].x;
            long long dy = points[i].y - points[j].y;
            long long dz = points[i].z - points[j].z;
            long long distsq = dx * dx + dy * dy + dz * dz;
            edges.push_back({i, j, distsq});
        }
    }
    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);
    int limit = min(1000, (int)edges.size());
    for (int i = 0; i < limit; i++)
    {
        dsu.unite(edges[i].u, edges[i].v);
    }

    vector<long long> sizes;
    for (int i = 0; i < n; i++)
    {
        // If 'i' is the Boss of a circuit
        if (dsu.parent[i] == i)
        {
            sizes.push_back(dsu.sz[i]);
        }
    }
    sort(sizes.rbegin(), sizes.rend());
    if (sizes.size() >= 3)
    {
        long long result = sizes[0] * sizes[1] * sizes[2];
        cout << result << endl;
    }
    return 0;
}