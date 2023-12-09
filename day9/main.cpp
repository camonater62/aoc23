#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> result;
    int pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

int main()
{
    ifstream input("input.txt");
    string line;

    long part1 = 0;
    long part2 = 0;

    while (getline(input, line))
    {
        vector<vector<int>> pyramid;
        vector<string> split_line = split(line, " ");
        vector<int> row;
        for (auto &item : split_line)
        {
            row.push_back(stoi(item));
        }
        pyramid.push_back(row);

        auto allZeros = [](const vector<int> &row)
        {
            for (auto &item : row)
            {
                if (item != 0)
                {
                    return false;
                }
            }
            return true;
        };

        while (!allZeros(pyramid.back()))
        {
            vector<int> row;
            for (int i = 0; i < pyramid.back().size() - 1; i++)
            {
                row.push_back(pyramid.back()[i + 1] - pyramid.back()[i]);
            }
            pyramid.push_back(row);
        }

        for (int i = pyramid.size() - 2; i >= 0; i--)
        {
            pyramid[i].push_back(pyramid[i].back() + pyramid[i + 1].back());
            pyramid[i].insert(pyramid[i].begin(), pyramid[i].front() - pyramid[i + 1].front());
        }

        part1 += pyramid[0].back();
        part2 += pyramid[0][0];
    }

    cout << part1 << endl;
    cout << part2 << endl;

    return 0;
}