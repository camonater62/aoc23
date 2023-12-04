#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <optional>

using namespace std;

namespace std
{
    template <class T>
    inline void hash_combine(std::size_t &seed, const T &v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>>
    {
        size_t operator()(const std::pair<T1, T2> &p) const
        {
            std::size_t seed1(0);
            ::hash_combine(seed1, p.first);
            ::hash_combine(seed1, p.second);

            return seed1;
        }
    };
}

int numLength(int num)
{
    return to_string(num).length();
}

int getNum(int x, int y, vector<vector<char>> map)
{
    string numStr = "";
    while (x < map[y].size() && isdigit(map[y][x]))
    {
        numStr += map[y][x];
        x++;
    }
    return stoi(numStr);
}

optional<pair<int, int>> checkBounds(int x, int y, int numLength, const vector<vector<char>> &map)
{
    static set<char> symbols = {
        '#',
        '$',
        '%',
        '&',
        '*',
        '+',
        '-',
        '/',
        '=',
        '@',
    };

    // Check left of the number
    if (x > 0 && symbols.find(map[y][x - 1]) != symbols.end())
    {
        return make_pair(x - 1, y);
    }

    // Check right of the number
    if (x + numLength < map[y].size() && symbols.find(map[y][x + numLength]) != symbols.end())
    {
        return make_pair(x + numLength, y);
    }

    // Check above the number
    if (y > 0)
    {
        for (int i = -1; i <= numLength; i++)
        {
            if (x + i >= 0 && symbols.find(map[y - 1][x + i]) != symbols.end())
            {
                return make_pair(x + i, y - 1);
            }
        }
    }

    // Check below the number
    if (y + 1 < map.size())
    {
        for (int i = -1; i <= numLength; i++)
        {
            if (x + i >= 0 && symbols.find(map[y + 1][x + i]) != symbols.end())
            {
                return make_pair(x + i, y + 1);
            }
        }
    }

    return nullopt;
}

int main()
{
    ifstream input("input.txt");
    string line;

    vector<vector<char>> map;

    int total = 0;

    while (getline(input, line))
    {
        vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        map.push_back(row);
    }

    unordered_map<pair<int, int>, vector<int>> gears;

    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (isdigit(map[y][x]))
            {
                int num = getNum(x, y, map);
                int numLen = numLength(num);
                optional<pair<int, int>> found = checkBounds(x, y, numLen, map);
                if (found != nullopt)
                {
                    pair<int, int> coord = found.value();
                    if (gears.find(coord) == gears.end())
                    {
                        gears[coord] = vector<int>();
                    }
                    gears[coord].push_back(num);
                    total += num;
                }
                x += numLen;
            }
        }
    }

    cout << "Total (P1): " << total << endl;

    int p2total = 0;
    for (auto gear : gears)
    {
        const vector<int> &nums = gear.second;
        if (nums.size() == 2)
        {
            p2total += nums[0] * nums[1];
        }
    }

    cout << "Total (P2): " << p2total << endl;

    return 0;
}