#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool isInvalidID(long long num)
{
    string str = to_string(num);
    int len = str.length();
    if (len % 2 != 0)
    {
        return false;
    }
    else
    {
        string sub1 = str.substr(0, len / 2);
        string sub2 = str.substr(len / 2);
        return sub1 == sub2;
    }
}

long long solve(string input)
{
    long long totalSum = 0;
    stringstream ss(input);
    string range;
    while (getline(ss, range, ','))
    {
        stringstream rangeStream(range);
        string startStr, endStr;

        getline(rangeStream, startStr, '-');
        getline(rangeStream, endStr, '-');

        long long start = stoll(startStr);
        long long end = stoll(endStr);

        for (long long i = start; i <= end; ++i)
        {
            if (isInvalidID(i))
            {
                totalSum += i;
            }
        }
    }
    return totalSum;
}

int main()
{
    string input = "749639-858415,65630137-65704528,10662-29791,1-17,9897536-10087630,1239-2285,1380136-1595466,8238934-8372812,211440-256482,623-1205,102561-122442,91871983-91968838,62364163-62554867,3737324037-3737408513,9494926669-9494965937,9939271919-9939349036,83764103-83929201,24784655-24849904,166-605,991665-1015125,262373-399735,557161-618450,937905586-937994967,71647091-71771804,8882706-9059390,2546-10476,4955694516-4955781763,47437-99032,645402-707561,27-86,97-157,894084-989884,421072-462151";
    cout << solve(input) << endl;
    return 0;
}
