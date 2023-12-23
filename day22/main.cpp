// Solution inspired/based off leijurv on reddit

#include "../common.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Cube
{
    union
    {
        struct
        {
            int x, y, z;
        };
        int coords[3];
    };

    bool operator==(const Cube &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Brick
{
    vector<Cube> cubes;
};

pair<vector<Brick>, int> dropBricks(vector<Brick> bricks)
{
    sort(bricks.begin(), bricks.end(), [](const Brick a, const Brick b)
         {
        int mina = INT_MAX;
        for (Cube cube : a.cubes)
        {
            mina = min(mina, cube.z);
        }
        int minb = INT_MAX;
        for (Cube cube : b.cubes)
        {
            minb = min(minb, cube.z);
        }

        return mina < minb; });

    vector<Cube> settled;
    vector<Brick> finalBricks;
    int numFell = 0;

    for (Brick brick : bricks)
    {
        bool moved = false;
        while (true)
        {
            vector<Cube> next;
            for (Cube cube : brick.cubes)
            {
                next.push_back({cube.x, cube.y, cube.z - 1});
            }

            if (all_of(next.begin(), next.end(), [&settled](const Cube &cube)
                       { return cube.z != 0 && find(settled.begin(), settled.end(), cube) == settled.end(); }))
            {
                moved = true;
                brick.cubes = next;
            }
            else
            {
                break;
            }
        }

        for (Cube cube : brick.cubes)
        {
            settled.push_back(cube);
        }
        finalBricks.push_back(brick);
        if (moved)
        {
            numFell++;
        }
    }

    return {finalBricks, numFell};
}

int main()
{
    ifstream input("example.txt");
    string line;

    vector<Brick> bricks;

    while (getline(input, line))
    {
        vector<string> parts = split(line, "~");
        vector<string> startVec = split(parts[0], ",");
        vector<string> endVec = split(parts[1], ",");
        Cube start = {stoi(startVec[0]), stoi(startVec[1]), stoi(startVec[2])};
        Cube end = {stoi(endVec[0]), stoi(endVec[1]), stoi(endVec[2])};
        vector<Cube> cubes;

        cubes.push_back(start);

        for (int i = 0; i < 3; i++)
        {
            if (start.coords[i] != end.coords[i])
            {
                for (int j = start.coords[i] + 1; j < end.coords[i]; j++)
                {
                    Cube cube = start;
                    cube.coords[i] = j;
                    cubes.push_back(cube);
                }
            }
        }

        cubes.push_back(end);

        bricks.push_back({cubes});
    }

    vector<Brick> dropped = dropBricks(bricks).first;

    int p1 = 0;
    int p2 = 0;

    for (int i = 0; i < dropped.size(); i++)
    {
        vector<Brick> without = dropped;
        without.erase(without.begin() + i);
        int num_fell = dropBricks(without).second;
        if (num_fell == 0)
        {
            p1++;
        }
        p2 += num_fell;
    }

    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    return 0;
}