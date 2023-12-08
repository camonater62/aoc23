#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long lcm(long a, long b) {
    return (a * b) / (gcd(a, b));
}

long findLCM(vector<long> arr) {
    long ans = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        ans = lcm(ans, arr[i]);
    }

    return ans;
}

int main() {
    ifstream input("input.txt");
    string line;

    string instruction;
    getline(input, instruction);

    // skip a line
    getline(input, line);

    unordered_map<string, pair<string, string>> map;

    while (getline(input, line)) {
        string node = line.substr(0, 3);
        string left = line.substr(7, 3);
        string right = line.substr(12, 3);

        map[node] = make_pair(left, right);
    }

    long step = 0;
    string current = "AAA";

    while (current != "ZZZ") {
        string left = map[current].first;
        string right = map[current].second;

        switch (instruction[step % instruction.length()]) {
        case 'L': current = left; break;
        case 'R': current = right; break;
        default: cout << "Invalid instruction" << endl; return 1;
        }

        step++;
    }

    cout << "P1: " << step << endl;

    vector<long> steps;

    for (const auto &[key, value] : map) {
        if (key[2] == 'A') {
            string current = key;
            long step = 0;
            while (current[2] != 'Z') {
                string left = map[current].first;
                string right = map[current].second;

                switch (instruction[step % instruction.length()]) {
                case 'L': current = left; break;
                case 'R': current = right; break;
                default: cout << "Invalid instruction" << endl; return 1;
                }

                step++;
            }
            steps.push_back(step);
        }
    }

    cout << "P2: " << findLCM(steps) << endl;

    return 0;
}