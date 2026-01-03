#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    ifstream infile("input.txt");
    string line;
    vector<string> manifold;

    while (getline(infile, line))
    {
        if (line.empty())
            break;
        manifold.push_back(line);
    }

    int height = manifold.size();
    int width = manifold[0].length();

    vector<vector<long long>> path(height, vector<long long>(width, 0));

    for (int i = 0; i < width; i++)
    {
        if (manifold[0][i] == 'S')
        {
            path[0][i] = 1;
            break;
        }
    }

    long long totalTimelinesAtBottom = 0;

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (path[y][x] > 0)
            {
                bool hitSplitter = false;
                for (int nextY = y + 1; nextY < height; nextY++)
                {
                    if (manifold[nextY][x] == '^')
                    {
                        if (x - 1 >= 0)
                        {
                            path[nextY][x - 1] += path[y][x];
                        }
                        if (x + 1 < width)
                        {
                            path[nextY][x + 1] += path[y][x];
                        }
                        hitSplitter = true;
                        break;
                    }
                }
                if (!hitSplitter)
                {
                    totalTimelinesAtBottom += path[y][x];
                }
            }
        }
    }

    for (int x = 0; x < width; x++)
    {
        totalTimelinesAtBottom += path[height - 1][x];
    }

    cout << totalTimelinesAtBottom << endl;
    return 0;
}