#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<string> grid;
    string row;

    ifstream infile("input.txt");

    while (infile >> row)
    {
        grid.push_back(row);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int accessible = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == '@')
            {
                int neighbors = 0;
                for (int k = 0; k < 8; k++)
                {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols)
                    {
                        if (grid[ni][nj] == '@')
                        {
                            neighbors++;
                        }
                    }
                }
                if (neighbors < 4)
                {
                    accessible++;
                }
            }
        }
    }

    cout << accessible << endl;
    return 0;
}