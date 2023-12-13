#include "../common.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map {
public:
    Map() = default;

    void addRow(string line) {
        grid.push_back(line);
    }

    int score(int allowed = 0) {
        int horz = findHorizontal(allowed);
        int vert = findVertical(allowed);

        int value = 0;

        if (horz != -1) {
            value += 100 * horz;
        }
        if (vert != -1) {
            value += vert;
        }

        return value;
    }

private:
    vector<string> grid;

    vector<string> transpose(const vector<string> &vec) {
        vector<string> result;
        for (int x = 0; x < vec[0].size(); x++) {
            string row;
            for (int y = 0; y < vec.size(); y++) {
                row.push_back(vec[y][x]);
            }
            result.push_back(row);
        }
        return result;
    }

    int findHorizontal(int allowed) {
        for (int i = 1; i < grid.size(); i++) {
            int errors = 0;

            int count = min(i, (int) grid.size() - i);

            for (int j = 1; j <= count; j++) {
                for (int k = 0; k < grid[0].size(); k++) {
                    if (grid[i - j][k] != grid[i + j - 1][k]) {
                        errors++;
                    }
                }
            }

            if (errors == allowed) {
                return i;
            }
        }

        return -1;
    }

    int findVertical(int allowed) {
        grid = transpose(grid);
        int value = findHorizontal(allowed);
        grid = transpose(grid);
        return value;
    }
};

int main() {
    ifstream input("input.txt");
    string line;

    vector<Map> maps;
    Map currentMap;

    while (getline(input, line)) {
        if (line.size() == 0) {
            maps.push_back(currentMap);
            currentMap = Map();
        } else {
            currentMap.addRow(line);
        }
    }
    maps.push_back(currentMap);

    int p1total = 0;
    int p2total = 0;

    for (auto &map : maps) {
        p1total += map.score();
        p2total += map.score(1);
    }

    cout << "P1: " << p1total << endl;
    cout << "P2: " << p2total << endl;
}