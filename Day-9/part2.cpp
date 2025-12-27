#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Point
{
    long long x, y;
};

bool isInside(const vector<Point> &poly, long long x, long long y)
{
    bool res = false;
    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];

        if (x >= min(p1.x, p2.x) && x <= max(p1.x, p2.x) &&
            y >= min(p1.y, p2.y) && y <= max(p1.y, p2.y))
        {
            return true;
        }

        if (((p1.y > y) != (p2.y > y)) &&
            (x < (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y) + p1.x))
        {
            res = !res;
        }
    }
    return res;
}

int main()
{
    vector<Point> redTiles;
    long long x, y;
    char comma;

    while (cin >> x >> comma >> y)
    {
        redTiles.push_back({x, y});
    }

    long long maxArea = 0;
    int n = redTiles.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            long long xMin = min(redTiles[i].x, redTiles[j].x);
            long long xMax = max(redTiles[i].x, redTiles[j].x);
            long long yMin = min(redTiles[i].y, redTiles[j].y);
            long long yMax = max(redTiles[i].y, redTiles[j].y);

            long long width = xMax - xMin + 1;
            long long height = yMax - yMin + 1;
            long long currentArea = width * height;

            if (currentArea <= maxArea)
                continue;

            double midX = (xMin + xMax) / 2.0;
            double midY = (yMin + yMax) / 2.0;

            if (isInside(redTiles, xMin, yMin) &&
                isInside(redTiles, xMax, yMax) &&
                isInside(redTiles, xMin, yMax) &&
                isInside(redTiles, xMax, yMin))
            {

                bool holeFound = false;
                for (int k = 0; k < n; k++)
                {
                    if (redTiles[k].x > xMin && redTiles[k].x < xMax &&
                        redTiles[k].y > yMin && redTiles[k].y < yMax)
                    {
                        holeFound = true;
                        break;
                    }
                }

                if (!holeFound)
                {
                    maxArea = currentArea;
                }
            }
        }
    }

    cout << maxArea << endl;
    return 0;
}