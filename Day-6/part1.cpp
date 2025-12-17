#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream infile("input.txt");
    long long answer = 0;
    string row1, row2, row3, row4, ops;

    getline(infile, row1);
    getline(infile, row2);
    getline(infile, row3);
    getline(infile, row4);
    getline(infile, ops);

    infile.close();

    int maxLen = max({row1.length(), row2.length(), row3.length(), row4.length(), ops.length()});

    row1 += string(maxLen - row1.length(), ' ');
    row2 += string(maxLen - row2.length(), ' ');
    row3 += string(maxLen - row3.length(), ' ');
    row4 += string(maxLen - row4.length(), ' ');
    ops += string(maxLen - ops.length(), ' ');

    int i = 0;
    while (i < maxLen)
    {
        if (row1[i] == ' ' && row2[i] == ' ' && row3[i] == ' ' && row4[i] == ' ')
        {
            i++;
            continue;
        }
        string n1 = "", n2 = "", n3 = "", n4 = "";
        char op = ' ';

        while (i < maxLen && !(row1[i] == ' ' && row2[i] == ' ' && row3[i] == ' ' && row4[i] == ' '))
        {
            if (row1[i] != ' ')
                n1 += row1[i];
            if (row2[i] != ' ')
                n2 += row2[i];
            if (row3[i] != ' ')
                n3 += row3[i];
            if (row4[i] != ' ')
                n4 += row4[i];
            if (ops[i] != ' ')
                op = ops[i];
            i++;
        }

        vector<long long> nums;
        if (!n1.empty())
            nums.push_back(stoll(n1));
        if (!n2.empty())
            nums.push_back(stoll(n2));
        if (!n3.empty())
            nums.push_back(stoll(n3));
        if (!n4.empty())
            nums.push_back(stoll(n4));

        long long result;
        if (op == '+')
        {
            result = 0;
            for (long long x : nums)
                result += x;
        }

        else if (op == '*')
        {
            result = 1;
            for (long long x : nums)
                result *= x;
        }
        else
        {
            continue;
        }

        answer += result;
    }
    cout << answer << endl;
    return 0;
}
