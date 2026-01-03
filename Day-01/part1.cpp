#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    int zeroes = 0;
    int start = 50;
    vector<string> dir;
    ifstream infile("input.txt");
    string line;
    while (getline(infile, line))
    {
        if (!line.empty())
        {
            dir.push_back(line);
        }
    }
    infile.close();

    for (size_t i = 0; i < dir.size(); i++)
    {
        if (dir[i].length() < 2)
        {
            continue;
        }

        int number = stoi(dir[i].substr(1));

        if (dir[i][0] == 'L')
        {
            start = (start - number % 100 + 100) % 100;
        }
        else if (dir[i][0] == 'R')
        {
            start = (start + number) % 100;
        }

        if (start == 0)
        {
            zeroes++;
        }
    }
    cout << zeroes << endl;
    return 0;
}