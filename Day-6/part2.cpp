#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ifstream infile("input.txt");
    vector<string> rows;
    string line;

    while (getline(infile, line))
    {
        rows.push_back(line);
    }

    infile.close();

    int R = rows.size();
    int C = 0;

    for (int i = 0; i < R; i++)
    {
        int rowLength = rows[i].size();
        if (rowLength > C)
        {
            C = rowLength;
        }
    }

    for (int i = 0; i < R; i++)
    {
        while (rows[i].size() < C)
        {
            rows[i] += ' ';
        }
    }

    long long grandTotal = 0;
    int col = C - 1;

    while (col >= 0)
    {
        bool isSeparator = true;
        for (int r = 0; r < R; r++)
        {
            if (rows[r][col] != ' ')
            {
                isSeparator = false;
                break;
            }
        }

        if (isSeparator)
        {
            col--;
            continue;
        }

        vector<long long> numbers;
        char op = ' ';

        while (col >= 0)
        {
            bool gap = true;
            for (int r = 0; r < R; r++)
            {
                if (rows[r][col] != ' ')
                {
                    gap = false;
                    break;
                }
            }

            if (gap)
            {
                break;
            }

            string digitStr = "";
            for (int r = 0; r < R - 1; r++)
            {
                if (rows[r][col] != ' ')
                {
                    digitStr += rows[r][col];
                }
            }

            if (digitStr != "")
            {
                long long num = stoll(digitStr);
                numbers.push_back(num);
            }

            if (rows[R - 1][col] != ' ')
            {
                op = rows[R - 1][col];
            }

            col--;
        }

        long long result;

        if (op == '+')
        {
            result = 0;
            for (int i = 0; i < numbers.size(); i++)
            {
                result += numbers[i];
            }
        }
        else
        {
            result = 1;
            for (int i = 0; i < numbers.size(); i++)
            {
                result *= numbers[i];
            }
        }
        grandTotal += result;
    }
    cout << grandTotal << endl;

    return 0;
}