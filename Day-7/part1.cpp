#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

struct beam
{
    int x, y;
};

int main()
{
    ifstream infile("input.txt");
    string line;
    vector<string> manifold;
    int startX = 0;

    while (getline(infile, line))
    {
        if (line.empty())
            break;
        manifold.push_back(line);
    }

    if (!manifold.empty())
    {
        for (int i = 0; i < manifold[0].length(); i++)
        {
            if (manifold[0][i] == 'S')
            {
                startX = i;
            }
        }
    }

    int height = manifold.size();
    int width = manifold[0].length();

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    queue<beam> q;
    q.push({startX, 0});

    int count = 0;

    while (!q.empty())
    {
        beam current = q.front();
        q.pop();

        for (int y = current.y; y < height; y++)
        {
            if (manifold[y][current.x] == '^')
            {
                if (!visited[y][current.x])
                {
                    visited[y][current.x] = true;
                    count++;
                    if (current.x - 1 >= 0)
                    {
                        q.push({current.x - 1, y + 1});
                    }
                    if (current.x + 1 < width)
                    {
                        q.push({current.x + 1, y + 1});
                    }
                }
                break;
            }
        }
    }

    cout << count << endl;
    return 0;
}
