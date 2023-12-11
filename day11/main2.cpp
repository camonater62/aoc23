#include <iostream>
#include <fstream>
#include "../common.hpp"
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

// My computer has 32 bit longs
#define long long long

int main()
{
    ifstream input("input.txt");
    string line;

    vector<vector<char>> map;

    while (getline(input, line))
    {
        vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        map.push_back(row);
    }

    // // print map
    // for (const vector<char> &row : map)
    // {
    //     for (char c : row)
    //     {
    //         cout << c;
    //     }
    //     cout << endl;
    // }

    vector<int> columns;

    // add new columns to the map
    for (int x = 0; x < map[0].size(); x++)
    {
        bool empty = true;
        for (int y = 0; y < map.size(); y++)
        {
            if (map[y][x] != '.')
            {
                empty = false;
                break;
            }
        }
        if (empty)
        {
            columns.push_back(x);
        }
    }

    vector<int> rows;

    // add new rows to the map
    for (int y = 0; y < map.size(); y++)
    {
        const vector<char> &row = map[y];
        bool empty = true;
        for (int x = 0; x < row.size(); x++)
        {
            if (row[x] != '.')
            {
                empty = false;
                break;
            }
        }
        if (empty)
        {
            rows.push_back(y);
        }
    }

    long total = 0;

    vector<pair<long, long>> galaxies;

    int yoffset = 0;

    for (int y = 0; y < map.size(); y++)
    {
        int xoffset = 0;
        if (find(rows.begin(), rows.end(), y) != rows.end())
        {
            yoffset++;
            continue;
        }
        for (int x = 0; x < map[y].size(); x++)
        {
            if (find(columns.begin(), columns.end(), x) != columns.end())
            {
                xoffset++;
                continue;
            }
            if (map[y][x] == '#')
            {
                galaxies.push_back({x + 999999L * xoffset, y + 999999L * yoffset});
            }
        }
    }

    for (int i = 0; i < galaxies.size(); i++)
    {
        for (int j = i + 1; j < galaxies.size(); j++)
        {
            long diffx = galaxies[i].first - galaxies[j].first;
            long diffy = galaxies[i].second - galaxies[j].second;
            total += abs(diffx) + abs(diffy);
        }
    }

    cout << total << endl;

    return 0;
}