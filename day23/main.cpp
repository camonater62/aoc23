#include "../common.hpp"

#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

// '.' is empty
// '#' is wall
// '>'/ 'v' / '<' / '^' is one way

int findLongestPath(vector<vector<char>> &grid, int x, int y, int pathLength, int endx)
{
    if (y == grid.size() - 1)
    {
        return pathLength;
    }

    if (grid[y][x] == '#')
    {
        return 0;
    }

    int longestPath = 0;

    char c = grid[y][x];
    grid[y][x] = '#';
    // Go left
    if (x > 0 && grid[y][x - 1] != '#' && (c == '<' || c == '.'))
    {
        longestPath = max(longestPath, findLongestPath(grid, x - 1, y, pathLength + 1, endx));
    }
    // Go right
    if (x < grid[y].size() - 1 && grid[y][x + 1] != '#' && (c == '>' || c == '.'))
    {
        longestPath = max(longestPath, findLongestPath(grid, x + 1, y, pathLength + 1, endx));
    }
    // Go up
    if (y > 0 && grid[y - 1][x] != '#' && (c == '^' || c == '.'))
    {
        longestPath = max(longestPath, findLongestPath(grid, x, y - 1, pathLength + 1, endx));
    }
    // Go down
    if (y < grid.size() - 1 && grid[y + 1][x] != '#' && (c == 'v' || c == '.'))
    {

        longestPath = max(longestPath, findLongestPath(grid, x, y + 1, pathLength + 1, endx));
    }
    grid[y][x] = c;

    return longestPath;
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

    // Find the starting point
    int startx = 0;
    for (int i = 0; i < grid[0].size(); i++)
    {
        if (grid[0][i] == '.')
        {
            startx = i;
            break;
        }
    }
    // Find the ending point
    int endx = 0;
    for (int i = 0; i < grid[grid.size() - 1].size(); i++)
    {
        if (grid[grid.size() - 1][i] == '.')
        {
            endx = i;
            break;
        }
    }
    int longestPath = findLongestPath(grid, startx, 0, 0, endx);

    cout << "P1: " << longestPath << endl;

    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[y].size(); x++)
        {
            if (grid[y][x] == 'v' || grid[y][x] == '^' || grid[y][x] == '<' || grid[y][x] == '>')
            {
                grid[y][x] = '.';
            }
            // cout << grid[y][x];
        }
        // cout << endl;
    }

    longestPath = findLongestPath(grid, startx, 0, 0, endx);

    cout << "P2: " << longestPath << endl;

    return 0;
}