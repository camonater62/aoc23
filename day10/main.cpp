#include "../common.hpp"

#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class direction { north, south, east, west, start };

struct cell {
    int x;
    int y;
    direction dir;
    int distance;
};

int main() {
    ifstream input("input.txt");
    string line;

    vector<vector<char>> map;

    int startx, starty;

    int x, y = 0;

    while (getline(input, line)) {
        vector<char> row;
        for (int x = 0; x < line.size(); x++) {
            row.push_back(line[x]);

            if (line[x] == 'S') {
                startx = x;
                starty = y;
            }
        }
        map.push_back(row);
        y++;
    }

    /*
    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    */

    set<pair<int, int>> visited;
    set<pair<int, int>> walls;
    queue<cell> q;

    q.push({ startx, starty, direction::start, 0 });

    while (!q.empty()) {
        auto [x, y, dir, distance] = q.front();
        q.pop();

        if (visited.find({ x, y }) != visited.end()) {
            continue;
        }

        visited.insert({ x, y });

        bool found = true;
        switch (dir) {
        case direction::north:
            if (map[y - 1][x] == '|') {
                q.push({ x, y - 1, direction::north, distance + 1 });
            } else if (map[y - 1][x] == 'F') {
                q.push({ x, y - 1, direction::east, distance + 1 });
            } else if (map[y - 1][x] == '7') {
                q.push({ x, y - 1, direction::west, distance + 1 });
            } else if (map[y - 1][x] == 'S') {
                cout << "P1: " << (distance + 1) / 2 << endl;
            } else {
                found = false;
            }
            break;
        case direction::south:
            if (map[y + 1][x] == '|') {
                q.push({ x, y + 1, direction::south, distance + 1 });
            } else if (map[y + 1][x] == 'L') {
                q.push({ x, y + 1, direction::east, distance + 1 });
            } else if (map[y + 1][x] == 'J') {
                q.push({ x, y + 1, direction::west, distance + 1 });
            } else if (map[y + 1][x] == 'S') {
                cout << "P1: " << (distance + 1) / 2 << endl;
            } else {
                found = false;
            }
            break;
        case direction::east:
            if (map[y][x + 1] == '-') {
                q.push({ x + 1, y, direction::east, distance + 1 });
            } else if (map[y][x + 1] == '7') {
                q.push({ x + 1, y, direction::south, distance + 1 });
            } else if (map[y][x + 1] == 'J') {
                q.push({ x + 1, y, direction::north, distance + 1 });
            } else if (map[y][x + 1] == 'S') {
                cout << "P1: " << (distance + 1) / 2 << endl;
            } else {
                found = false;
            }
            break;
        case direction::west:
            if (map[y][x - 1] == '-') {
                q.push({ x - 1, y, direction::west, distance + 1 });
            } else if (map[y][x - 1] == 'F') {
                q.push({ x - 1, y, direction::south, distance + 1 });
            } else if (map[y][x - 1] == 'L') {
                q.push({ x - 1, y, direction::north, distance + 1 });
            } else if (map[y][x - 1] == 'S') {
                cout << "P1: " << (distance + 1) / 2 << endl;
            } else {
                found = false;
            }
            break;
        case direction::start:
            if (map[y][x + 1] == '-') {
                q.push({ x + 1, y, direction::east, distance + 1 });
            } else if (map[y][x - 1] == '-') {
                q.push({ x - 1, y, direction::west, distance + 1 });
            } else if (map[y - 1][x] == '|') {
                q.push({ x, y - 1, direction::north, distance + 1 });
            } else if (map[y + 1][x] == '|') {
                q.push({ x, y + 1, direction::south, distance + 1 });
            } else if (map[y][x + 1] == '7') {
                q.push({ x + 1, y, direction::south, distance + 1 });
            } else if (map[y][x + 1] == 'J') {
                q.push({ x + 1, y, direction::north, distance + 1 });
            } else if (map[y][x - 1] == 'F') {
                q.push({ x - 1, y, direction::south, distance + 1 });
            } else if (map[y][x - 1] == 'L') {
                q.push({ x - 1, y, direction::north, distance + 1 });
            }
            break;
        }
        if (found) {
            walls.insert({ x, y });
        }
    }

    int top = INT_MAX;
    int bottom = INT_MIN;
    int left = INT_MAX;
    int right = INT_MIN;

    for (auto [x, y] : walls) {
        if (x < left) {
            left = x;
        }
        if (x > right) {
            right = x;
        }
        if (y < top) {
            top = y;
        }
        if (y > bottom) {
            bottom = y;
        }
    }

    int count = 0;
    for (int y = top; y <= bottom; y++) {
        bool inside = false;
        for (int x = left; x <= right; x++) {
            if (walls.find({ x, y }) != walls.end()) {
                switch (map[y][x]) {
                case '|':
                case 'J':
                case 'L':
                case 'S': inside = !inside; break;
                default: break;
                }
            } else if (inside) {
                count++;
            }
        }
    }

    cout << "P2: " << count << endl;

    return 0;
}