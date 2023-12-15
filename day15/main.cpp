#include "../common.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int HASH(const string &s)
{
    int current = 0;
    for (const char &c : s)
    {
        current += (int)c;
        current *= 17;
        current %= 256;
    }
    return current;
}

int main()
{
    ifstream input("input.txt");
    string line;

    getline(input, line);

    vector<string> parts = split(line, ",");

    vector<pair<string, int>> boxes[256];

    int p1total = 0;

    for (const string &s : parts)
    {
        bool remove;
        int value = -1;
        vector<string> subparts;

        if (s.find("=") != string::npos)
        {
            subparts = split(s, "=");
            remove = false;
            value = stoi(subparts[1]);
        }
        else
        {
            subparts = split(s, "-");
            remove = true;
        }

        string id = subparts[0];

        p1total += HASH(s);
        int current = HASH(id);

        if (remove)
        {
            for (auto it = boxes[current].begin(); it != boxes[current].end(); ++it)
            {
                if (it->first == id)
                {
                    boxes[current].erase(it);
                    break;
                }
            }
        }
        else
        {
            bool replaced = false;
            for (auto &p : boxes[current])
            {
                if (p.first == id)
                {
                    p.second = value;
                    replaced = true;
                    break;
                }
            }
            if (!replaced)
            {
                boxes[current].push_back(make_pair(id, value));
            }
        }
    }

    cout << p1total << endl;

    int p2total = 0;

    for (int i = 0; i < 256; i++)
    {
        if (boxes[i].size() > 0)
        {
            for (int j = 0; j < boxes[i].size(); j++)
            {
                p2total += (i + 1) * (j + 1) * boxes[i][j].second;
            }
        }
    }

    cout << p2total << endl;

    return 0;
}