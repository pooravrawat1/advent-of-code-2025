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

    int totalRemoved = 0;

    while (true)
    {
        vector<vector<bool>> remove(rows, vector<bool>(cols, false));
        int removeThisRound = 0;

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
                        remove[i][j] = true;
                    }
                }
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (remove[i][j])
                {
                    grid[i][j] = '.';
                    removeThisRound++;
                }
            }
        }
        if (removeThisRound == 0)
        {
            break;
        }
        totalRemoved += removeThisRound;
    }

    cout << totalRemoved << endl;
    return 0;
}