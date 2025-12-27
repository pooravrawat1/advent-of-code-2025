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
    long long x, y;
};

int main()
{
    ifstream infile("input.txt");
    string line;
    vector<Point> points;
    long long x, y;
    while (getline(infile, line))
    {
        stringstream ss(line);
        char comma;
        ss >> x >> comma >> y;
        points.push_back({x, y});
    }

    long long maxArea = 0;

    for (size_t i = 0; i < points.size(); i++)
    {
        for (size_t j = i + 1; j < points.size(); j++)
        {
            long long height = abs(points[i].y - points[j].y) + 1;
            long long width = abs(points[i].x - points[j].x) + 1;
            long long area = height * width;
            if (area > maxArea)
            {
                maxArea = area;
            }
        }
    }

    cout << maxArea << endl;
    return 0;
}
