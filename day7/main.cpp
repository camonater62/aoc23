#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<char, int> values = {
    { 'A', 14 },
    { 'K', 13 },
    { 'Q', 12 },
    { 'J', 11 },
    { 'T', 10 },
    { '9', 9 },
    { '8', 8 },
    { '7', 7 },
    { '6', 6 },
    { '5', 5 },
    { '4', 4 },
    { '3', 3 },
    { '2', 2 },
};

class Hand {
public:
    Hand(string cards, int bid, bool part1) {
        this->cards = cards;
        this->bid = bid;

        unordered_map<char, int> counts;

        for (int i = 0; i < cards.size(); i++) {
            if (cards[i] == 'J' && part1) {
                cards[i] = 'X';
            }
        }

        int best = 0;
        string replace = "J23456789TQKA";
        for (int i = 0; i < replace.size(); i++) {
            unordered_map<char, int> counts;
            string temp = cards;
            for (int j = 0; j < cards.size(); j++) {
                if (temp[j] == 'J') {
                    temp[j] = replace[i];
                }
                counts[temp[j]]++;
            }

            int most = 0;
            int pairs = 0;
            for (auto &pair : counts) {
                most = max(most, pair.second);
                if (pair.second == 2) {
                    pairs++;
                }
            }
            if (most > 2) {
                most++;
            }
            if (pairs == 2) {
                most++;
            }
            if (most > 4) {
                most++;
            }
            if (most == 4 && pairs == 1) {
                most++;
            }
            best = max(best, most);
        }

        value[0] = best;

        static string lookup = "J23456789XTQKA";
        for (int i = 0; i < cards.size(); i++) {
            value[i + 1] = lookup.find(cards[i]);
        }
    }

    bool operator<(const Hand &other) const {
        for (int i = 0; i < 6; i++) {
            if (value[i] != other.value[i]) {
                return value[i] < other.value[i];
            }
        }
        return false;
    }
    //253603890
public:
    int value[6];
    int bid;
    string cards;
};

ostream &operator<<(ostream &os, const Hand &hand) {
    os << "(";
    for (int i = 0; i < 6; i++) {
        os << hand.value[i];
        if (i < 5) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<Hand> hands;

    while (getline(input, line)) {
        int spacepos = line.find(" ");
        string cards = line.substr(0, spacepos);
        int bid = stoi(line.substr(spacepos + 1));
        hands.emplace_back(cards, bid, true);
    }

    sort(hands.begin(), hands.end());

    long total = 0;

    for (int i = 0; i < hands.size(); i++) {
        int score = (i + 1) * hands[i].bid;
        total += score;
        // cout << hands[i].bid << endl;
    }

    cout << "P1: " << total << endl;

    // Part 2
    vector<Hand> hands2;
    for (const auto &hand : hands) {
        hands2.emplace_back(hand.cards, hand.bid, false);
    }

    sort(hands2.begin(), hands2.end());

    total = 0;

    for (int i = 0; i < hands2.size(); i++) {
        int score = (i + 1) * hands2[i].bid;
        total += score;
    }

    cout << "P2: " << total << endl;

    return 0;
}