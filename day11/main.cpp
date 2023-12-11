#include <iostream>
#include <fstream>
#include "../common.hpp"
#include <string>

using namespace std;

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
            for (int y = 0; y < map.size(); y++)
            {
                map[y].insert(map[y].begin() + x, '.');
            }
            x++;
        }
    }

    // add new rows to the map
    for (int i = 0; i < map.size(); i++)
    {
        const vector<char> &row = map[i];
        bool empty = true;
        for (int j = 0; j < row.size(); j++)
        {
            if (row[j] != '.')
            {
                empty = false;
                break;
            }
        }
        if (empty)
        {
            map.insert(map.begin() + i, vector<char>(row.size(), '.'));
            i++;
        }
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

    int total = 0;

    vector<pair<int, int>> galaxies;

    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == '#')
            {
                galaxies.push_back({x, y});
            }
        }
    }

    for (int i = 0; i < galaxies.size(); i++)
    {
        for (int j = i + 1; j < galaxies.size(); j++)
        {
            total += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
        }
    }

    cout << total << endl;

    return 0;
}