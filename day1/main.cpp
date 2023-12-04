#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream input("input.txt");

    int total = 0;

    string line = "";
    while (getline(input, line))
    {
        int first = -1;
        int last = -1;

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                if (first == -1)
                {
                    first = line[i] - '0';
                }
                last = line[i] - '0';
            }
        }

        total += 10 * first + last;
    }

    std::cout << total << endl;
    return 0;
}