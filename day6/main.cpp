#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string str, string delimiter) {
    vector<string> result;
    int pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

int main() {
    ifstream input("input.txt");

    string fullTime;
    string fullDistance;

    getline(input, fullTime);
    getline(input, fullDistance);

    fullTime = split(fullTime, ":")[1];
    fullDistance = split(fullDistance, ":")[1];

    vector<int> times;
    vector<int> distances;

    for (string s : split(fullTime, " ")) {
        if (s.size() > 0) {
            times.push_back(stoi(s));
        }
    }

    for (string s : split(fullDistance, " ")) {
        if (s.size() > 0) {
            distances.push_back(stoi(s));
        }
    }

    int total = 1;

    for (int i = 0; i < times.size(); i++) {
        int count = 0;
        for (int j = 0; j <= times[i]; j++) {
            int delay = j;
            int speed = j;
            int travelled = (times[i] - j) * speed;
            // cout << travelled << endl;
            if (travelled > distances[i]) {
                count++;
            }
        }
        total *= count;
    }

    cout << total << endl;

    for (int i = fullTime.size() - 1; i >= 0; i--) {
        if (fullTime[i] == ' ') {
            fullTime.erase(fullTime.begin() + i);
        }
    }

    for (int i = fullDistance.size() - 1; i >= 0; i--) {
        if (fullDistance[i] == ' ') {
            fullDistance.erase(fullDistance.begin() + i);
        }
    }

    long T = stol(fullTime);
    long D = stol(fullDistance);

    long S = long(sqrt(T * T - 4 * D));

    long lower = (T - S) / 2;
    long upper = (T + S) / 2;

    cout << (upper - lower) << endl;

    return 0;
}