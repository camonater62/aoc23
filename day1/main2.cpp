#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int stringToInt(string str) {
    static unordered_map<string, int> table = {
        { "one", 1 },
        { "two", 2 },
        { "three", 3 },
        { "four", 4 },
        { "five", 5 },
        { "six", 6 },
        { "seven", 7 },
        { "eight", 8 },
        { "nine", 9 },
    };

    if (str.size() == 1) {
        return str[0] - '0';
    } else {
        return table[str];
    }
}

int main() {
    ifstream input("input.txt");

    int total = 0;

    regex numberRegex("(?=([1-9]|one|two|three|four|five|six|seven|eight|nine)).");

    string line = "";
    while (getline(input, line)) {
        vector<string> numberMatches;

        sregex_iterator next(line.begin(), line.end(), numberRegex);
        sregex_iterator end;
        while (next != end) {
            smatch match = *next;
            numberMatches.push_back(match.str(1));
            next++;
        }

        if (numberMatches.size() == 1) {
            total += 11 * stringToInt(numberMatches[0]);
        } else {
            total += 10 * stringToInt(numberMatches[0]) + stringToInt(numberMatches[1]);
        }
    }

    std::cout << total << endl;
    return 0;
}