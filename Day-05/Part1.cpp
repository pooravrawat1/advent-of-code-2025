#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream infile("input.txt");
    vector<long long> start;
    vector<long long> end;
    vector<long long> ingredient;

    string line;
    bool readingRanges = true;

    while (getline(infile, line))
    {
        if (line.empty())
        {
            readingRanges = false;
            continue;
        }

        if (readingRanges)
        {
            size_t dashPos = line.find('-');
            long long a = stoll(line.substr(0, dashPos));
            long long b = stoll(line.substr(dashPos + 1));
            start.push_back(a);
            end.push_back(b);
        }
        else
        {
            ingredient.push_back(stoll(line));
        }
    }

    infile.close();

    vector<pair<long long, long long>> ranges;
    for (int i = 0; i < start.size(); i++)
    {
        ranges.push_back({start[i], end[i]});
    }

    sort(ranges.begin(), ranges.end());

    vector<pair<long long, long long>> merged;

    for (int i = 0; i < ranges.size(); i++)
    {
        if (merged.empty())
        {
            merged.push_back(ranges[i]);
        }
        else if (ranges[i].first <= merged.back().second + 1)
        {
            if (ranges[i].second > merged.back().second)
            {
                merged.back().second = ranges[i].second;
            }
        }
        else
        {
            merged.push_back(ranges[i]);
        }
    }

    int count = 0;

    for (int i = 0; i < ingredient.size(); i++)
    {
        long long id = ingredient[i];
        bool fresh = false;

        for (int j = 0; j < merged.size(); j++)
        {
            if (merged[j].first <= id && id <= merged[j].second)
            {
                fresh = true;
                break;
            }
        }

        if (fresh)
            count++;
    }

    cout << count << endl;
    return 0;
}
