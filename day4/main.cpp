#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

vector<string> split(string str, string delimiter)
{
    vector<string> result;
    int pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

int main()
{
    ifstream input("input.txt");
    string line;
    int p1total = 0;
    int p2total = 0;
    int index = 1;

    unordered_map<int, int> copies;

    while (getline(input, line))
    {
        line = split(line, ": ")[1];
        vector<string> parts = split(line, " | ");
        set<int> winning;
        int points = 0;
        int toAdd = 0;

        p2total += copies[index] + 1;

        for (string num : split(parts[0], " "))
        {
            if (num.size() == 0)
            {
                continue;
            }
            winning.insert(stoi(num));
        }
        for (string num : split(parts[1], " "))
        {
            if (num.size() == 0)
            {
                continue;
            }
            if (winning.find(stoi(num)) != winning.end())
            {
                if (points == 0)
                {
                    points = 1;
                }
                else
                {
                    points *= 2;
                }
                toAdd++;
            }
        }

        p1total += points;

        for (int i = 1; i <= toAdd; i++)
        {
            copies[index + i] += copies[index] + 1;
        }

        index++;
    }

    cout << p1total << endl;
    cout << p2total << endl;

    return 0;
}