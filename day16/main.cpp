#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include "../common.hpp"

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Node
{
    Direction direction;
    int x;
    int y;

    bool operator==(const Node &other) const
    {
        return direction == other.direction && x == other.x && y == other.y;
    }
};

template <>
struct hash<Node>
{
    std::size_t operator()(const Node &node) const
    {
        std::size_t seed = 0;
        hash_combine(seed, node.direction);
        hash_combine(seed, node.x);
        hash_combine(seed, node.y);
        return seed;
    }
};

int search(const vector<vector<char>> &grid, Node start)
{
    queue<Node> Q;
    unordered_set<Node> visited;

    Q.push(start);

    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();

        if (visited.find(node) != visited.end())
        {
            continue;
        }

        if (node.x < 0 || node.x >= grid[0].size() || node.y < 0 || node.y >= grid.size())
        {
            continue;
        }

        // cout << node.x << " " << node.y << grid[node.y][node.x];

        visited.insert(node);

        switch (node.direction)
        {
        case UP:
            // cout << " UP" << endl;
            switch (grid[node.y][node.x])
            {
            case '/':
                Q.push({RIGHT, node.x + 1, node.y});
                break;
            case '\\':
                Q.push({LEFT, node.x - 1, node.y});
                break;
            case '-':
                Q.push({RIGHT, node.x + 1, node.y});
                Q.push({LEFT, node.x - 1, node.y});
                break;
            case '.':
            case '|':
            default:
                Q.push({UP, node.x, node.y - 1});
                break;
            }
            break;
        case DOWN:
            // cout << " DOWN" << endl;
            switch (grid[node.y][node.x])
            {
            case '/':
                Q.push({LEFT, node.x - 1, node.y});
                break;
            case '\\':
                Q.push({RIGHT, node.x + 1, node.y});
                break;
            case '-':
                Q.push({RIGHT, node.x + 1, node.y});
                Q.push({LEFT, node.x - 1, node.y});
                break;
            case '.':
            case '|':
            default:
                Q.push({DOWN, node.x, node.y + 1});
                break;
            }
            break;
        case LEFT:
            // cout << " LEFT" << endl;
            switch (grid[node.y][node.x])
            {
            case '/':
                Q.push({DOWN, node.x, node.y + 1});
                break;
            case '\\':
                Q.push({UP, node.x, node.y - 1});
                break;
            case '|':
                Q.push({DOWN, node.x, node.y + 1});
                Q.push({UP, node.x, node.y - 1});
                break;
            case '.':
            case '-':
            default:
                Q.push({LEFT, node.x - 1, node.y});
                break;
            }
            break;
        case RIGHT:
            // cout << " RIGHT" << endl;
            switch (grid[node.y][node.x])
            {
            case '/':
                Q.push({UP, node.x, node.y - 1});
                break;
            case '\\':
                Q.push({DOWN, node.x, node.y + 1});
                break;
            case '|':
                Q.push({DOWN, node.x, node.y + 1});
                Q.push({UP, node.x, node.y - 1});
                break;
            case '.':
            case '-':
            default:
                Q.push({RIGHT, node.x + 1, node.y});
                break;
            }

            break;
        }
    }

    unordered_set<pair<int, int>> energized;
    for (auto &node : visited)
    {
        energized.insert({node.x, node.y});
    }
    return energized.size();
}

int main()
{
    ifstream input("input.txt");

    string line;
    vector<vector<char>> grid;

    while (getline(input, line))
    {
        vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    cout << "P1: " << search(grid, {RIGHT, 0, 0}) << endl;

    int best = 0;

    // Top row
    for (int x = 0; x < grid[0].size(); x++)
    {
        best = max(best, search(grid, {DOWN, x, 0}));
    }

    // Bottom row
    for (int x = 0; x < grid[grid.size() - 1].size(); x++)
    {
        best = max(best, search(grid, {UP, x, (int)grid.size() - 1}));
    }

    // Left column
    for (int y = 0; y < grid.size(); y++)
    {
        best = max(best, search(grid, {RIGHT, 0, y}));
    }

    // Right column
    for (int y = 0; y < grid.size(); y++)
    {
        best = max(best, search(grid, {LEFT, (int)grid[0].size() - 1, y}));
    }

    cout << "P2: " << best << endl;
}