// Part 2 Thanks to charr3 on reddit

#include "../common.hpp"

#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

char getFromRepeating(const vector<vector<char>> &grid, int x, int y) {
    while (y < 0) {
        y += grid.size();
    }
    y %= grid.size();

    while (x < 0) {
        x += grid[y].size();
    }
    x %= grid[y].size();

    return grid[y][x];
};

int f(const vector<vector<char>> &grid, int n) {
    unordered_set<pair<int, int>> current;
    current.insert({ grid[0].size() / 2, grid.size() / 2 });

    for (int i = 0; i < n; i++) {
        unordered_set<pair<int, int>> next;
        for (auto [x, y] : current) {
            if (getFromRepeating(grid, x - 1, y) != '#') {
                next.insert({ x - 1, y });
            }
            if (getFromRepeating(grid, x + 1, y) != '#') {
                next.insert({ x + 1, y });
            }
            if (getFromRepeating(grid, x, y - 1) != '#') {
                next.insert({ x, y - 1 });
            }
            if (getFromRepeating(grid, x, y + 1) != '#') {
                next.insert({ x, y + 1 });
            }
        }
        current = next;
    }
    return current.size();
};

int main() {
    ifstream input("input.txt");
    string line;

    vector<vector<char>> grid;

    while (getline(input, line)) {
        vector<char> row;
        int x = 0;
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    cout << "P1: " << f(grid, 64) << endl;

    long a0 = f(grid, grid.size() / 2 + 1);
    long a1 = f(grid, grid.size() / 2 + 1 + 1 * grid.size());
    long a2 = f(grid, grid.size() / 2 + 1 + 2 * grid.size());

    long b0 = a0;
    long b1 = a1 - a0;
    long b2 = a2 - a1;

    auto answer = [&](long n) { return b0 + b1 * n + (n * (n - 1) / 2) * (b2 - b1); };

    cout << "P2: " << answer(26501365 / 131) << endl;

    return 0;
}