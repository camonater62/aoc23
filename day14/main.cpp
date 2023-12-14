#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void tumbleNorth(vector<vector<char>> &grid) {
    for (int y = 1; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            int ty = y;
            while (ty > 0 && grid[ty][x] == 'O' && grid[ty - 1][x] == '.') {
                swap(grid[ty][x], grid[ty - 1][x]);
                ty--;
            }
        }
    }
}

void tumbleWest(vector<vector<char>> &grid) {
    for (int x = 1; x < grid[0].size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            int tx = x;
            while (tx > 0 && grid[y][tx] == 'O' && grid[y][tx - 1] == '.') {
                swap(grid[y][tx], grid[y][tx - 1]);
                tx--;
            }
        }
    }
}

void tumbleSouth(vector<vector<char>> &grid) {
    for (int y = grid.size() - 2; y >= 0; y--) {
        for (int x = 0; x < grid[y].size(); x++) {
            int ty = y;
            while (ty < grid.size() - 1 && grid[ty][x] == 'O' && grid[ty + 1][x] == '.') {
                swap(grid[ty][x], grid[ty + 1][x]);
                ty++;
            }
        }
    }
}

void tumbleEast(vector<vector<char>> &grid) {
    for (int x = grid[0].size() - 2; x >= 0; x--) {
        for (int y = 0; y < grid.size(); y++) {
            int tx = x;
            while (tx < grid[0].size() - 1 && grid[y][tx] == 'O' && grid[y][tx + 1] == '.') {
                swap(grid[y][tx], grid[y][tx + 1]);
                tx++;
            }
        }
    }
}

size_t getHash(const vector<vector<char>> &vec) {
    string s = "";
    for (const auto &row : vec) {
        for (const auto &c : row) {
            s += c;
        }
    }
    return hash<string>()(s);
}

int main() {
    ifstream input("input.txt");
    string line;

    vector<vector<char>> grid;

    while (getline(input, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    tumbleNorth(grid);

    int total = 0;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == 'O') {
                total += grid.size() - y;
            }
        }
    }

    cout << "P1: " << total << endl;

    int target = int(1e9);
    unordered_map<size_t, int> hashes;

    for (int i = 0; i < target; i++) {
        tumbleNorth(grid);
        tumbleWest(grid);
        tumbleSouth(grid);
        tumbleEast(grid);
        size_t h = getHash(grid);
        if (hashes.find(h) != hashes.end()) {
            int start = hashes[h];
            int length = i - start;
            target = i + (target - start) % length;
        } else {
            hashes[h] = i;
        }
    }

    total = 0;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == 'O') {
                total += grid.size() - y;
            }
            // cout << grid[y][x];
        }
        // cout << endl;
    }

    cout << "P2: " << total << endl;
}