#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

    int id = 1;
    int p1total = 0;
    int p2total = 0;

    while (getline(input, line))
    {
        line = split(line, ": ")[1];
        bool valid = true;

        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        for (string round : split(line, "; "))
        {
            for (string cube : split(round, ", "))
            {
                int count = stoi(split(cube, " ")[0]);
                string color = split(cube, " ")[1];

                switch (color[0])
                {
                case 'r':
                    valid = valid && count <= 12;
                    maxRed = max(maxRed, count);
                    break;
                case 'g':
                    valid = valid && count <= 13;
                    maxGreen = max(maxGreen, count);
                    break;
                case 'b':
                    valid = valid && count <= 14;
                    maxBlue = max(maxBlue, count);
                    break;
                }
            }
        }

        if (valid)
        {
            p1total += id;
        }

        p2total += maxRed * maxGreen * maxBlue;

        id++;
    }

    cout << "Total (P1): " << p1total << endl;
    cout << "Total (P2): " << p2total << endl;

    return 0;
}