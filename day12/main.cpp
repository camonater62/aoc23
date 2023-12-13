#include "../common.hpp"

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct countMatchesSignature {
    const string &pattern;
    const vector<int> &splits;
};

template <> struct hash<countMatchesSignature> {
    size_t operator()(const countMatchesSignature &sig) const {
        std::size_t seed1(0);
        ::hash_combine(seed1, sig.pattern);
        ::hash_combine(seed1, sig.splits);

        return seed1;
    }
};

long countMatches(const string &pattern, vector<int> &splits) {
    // I got stuck on part 2, so this solution is a C++ rewrite of morgoth1145's algorithm
    // See the base Python code here: https://github.com/morgoth1145/advent-of-code/blob/2023-python/2023/12/solution.py
    countMatchesSignature sig { pattern, splits };
    size_t sigHash = hash<countMatchesSignature>()(sig);
    static unordered_map<size_t, long> cache;
    if (cache.find(sigHash) != cache.end()) {
        return cache[sigHash];
    }

    long a = splits[0];
    vector<int> rest = subvec(splits);
    long after = sum(rest) + rest.size();

    long count = 0;

    for (long before = 0; before <= pattern.size() - after - a; before++) {
        bool valid = true;

        for (int i = before; i < before + a; i++) {
            if (pattern[i] != '#' && pattern[i] != '?') {
                valid = false;
                break;
            }
        }

        if (valid) {
            if (rest.size() == 0) {
                for (int i = before + a; i < pattern.size(); i++) {
                    if (pattern[i] != '.' && pattern[i] != '?') {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    count += 1;
                }
            } else if (pattern[before + a] == '.' || pattern[before + a] == '?') {
                count += countMatches(pattern.substr(before + a + 1), rest);
            }
        }

        if (pattern[before] != '.' && pattern[before] != '?') {
            break;
        }
    }

    cache[sigHash] = count;

    return count;
}

int main() {
    ifstream input("input.txt");
    string line;

    vector<string> records;
    vector<vector<int>> goals;

    while (getline(input, line)) {
        vector<string> parts = split(line, " ");
        vector<string> sNums = split(parts[1], ",");
        records.push_back(parts[0]);
        vector<int> nums;
        for (string s : sNums) {
            nums.push_back(stoi(s));
        }
        goals.push_back(nums);
    }

    long total = 0;

    for (int i = 0; i < records.size(); i++) {
        int solutions = countMatches(records[i], goals[i]);
        total += solutions;
    }

    cout << "P1: " << total << endl;

    total = 0;

    for (int i = 0; i < records.size(); i++) {
        string bigstring = records[i];
        vector<int> bigvec = goals[i];
        for (int j = 0; j < 4; j++) {
            bigstring += '?' + records[i];
            for (int i : goals[i]) {
                bigvec.push_back(i);
            }
        }
        long solutions = countMatches(bigstring, bigvec);
        // cout << solutions << endl;
        total += solutions;
    }

    cout << "P2: " << total << endl;

    return 0;
}

// Old method for p1

// for (int i = 0; i < records.size(); i++) {
//     int unknowns = 0;
//     for (char c : records[i]) {
//         if (c == '?') {
//             unknowns++;
//         }
//     }

//     int maxBinary = 1 << unknowns;
//     // cout << (1 << (unknowns + 1)) << endl;

//     for (int j = 0; j < maxBinary; j++) {
//         int index = 0;

//         string test;
//         for (char c : records[i]) {
//             if (c == '?') {
//                 if (j >> index & 1) {
//                     test += '#';
//                 } else {
//                     test += '.';
//                 }
//                 index++;
//             } else {
//                 test += c;
//             }
//         }

//         if (equal(count(test), goals[i])) {
//             total++;
//         }
//     }
// }