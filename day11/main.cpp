#include "../common.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream input("input.txt");
    string line;

    vector<vector<char>> map;

    while (getline(input, line)) {
        vector<char> row;
        for (char c : line) {
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
    for (int x = 0; x < map[0].size(); x++) {
        bool empty = true;
        for (int y = 0; y < map.size(); y++) {
            if (map[y][x] != '.') {
                empty = false;
                break;
            }
        }
        if (empty) {
            columns.push_back(x);
        }
    }

    vector<int> rows;

    // add new rows to the map
    for (int y = 0; y < map.size(); y++) {
        const vector<char> &row = map[y];
        bool empty = true;
        for (int x = 0; x < row.size(); x++) {
            if (row[x] != '.') {
                empty = false;
                break;
            }
        }
        if (empty) {
            rows.push_back(y);
        }
    }

    vector<pair<long, long>> p1points;
    vector<pair<long, long>> p2points;

    int yoffset = 0;

    for (int y = 0; y < map.size(); y++) {
        int xoffset = 0;
        if (find(rows.begin(), rows.end(), y) != rows.end()) {
            yoffset++;
            continue;
        }
        for (int x = 0; x < map[y].size(); x++) {
            if (find(columns.begin(), columns.end(), x) != columns.end()) {
                xoffset++;
                continue;
            }
            if (map[y][x] == '#') {
                p1points.push_back({ x + xoffset, y + yoffset });
                p2points.push_back({ x + 999999L * xoffset, y + 999999L * yoffset });
            }
        }
    }

    long p1total = 0;

    for (int i = 0; i < p1points.size(); i++) {
        for (int j = i + 1; j < p1points.size(); j++) {
            long diffx = p1points[i].first - p1points[j].first;
            long diffy = p1points[i].second - p1points[j].second;
            p1total += abs(diffx) + abs(diffy);
        }
    }

    cout << "P1: " << p1total << endl;

    long p2total = 0;

    for (int i = 0; i < p2points.size(); i++) {
        for (int j = i + 1; j < p2points.size(); j++) {
            long diffx = p2points[i].first - p2points[j].first;
            long diffy = p2points[i].second - p2points[j].second;
            p2total += abs(diffx) + abs(diffy);
        }
    }

    cout << "P2: " << p2total << endl;

    return 0;
}