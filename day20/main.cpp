// Part 2 Thanks to Jonathon Paulson on Reddit

#include "../common.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum Pulse { LOW, HIGH };

enum ModuleType { FLIPFLOP, CONJUNCTION, BROADCAST };

struct Module {
    string name;
    ModuleType type;
    vector<string> outputs;
    Pulse pulse = LOW;
    unordered_map<string, Pulse> inputs;
};

int main() {
    unordered_map<string, Module> modules;
    ifstream infile("input.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> parts = split(line, " -> ");

        string input = parts[0];
        string outputs = parts[1];

        Module mod;
        mod.name = input.substr(1);
        mod.outputs = split(outputs, ", ");

        if (mod.name == "roadcaster") {
            mod.name = "broadcaster";
            mod.type = BROADCAST;
        } else if (input[0] == '%') {
            mod.type = FLIPFLOP;
        } else {
            mod.type = CONJUNCTION;
        }

        modules[mod.name] = mod;
    }

    string intoRx;

    for (auto &[name, mod] : modules) {
        for (auto &output : mod.outputs) {
            modules[output].inputs[name] = LOW;
            if (output == "rx") {
                intoRx = name;
            }
        }
    }

    vector<string> intoIntoRx;

    for (auto &[name, mod] : modules) {
        for (auto &output : mod.outputs) {
            if (output == intoRx) {
                intoIntoRx.push_back(name);
            }
        }
    }

    long high = 0;
    long low = 0;
    bool foundrx = false;

    unordered_map<string, long> count;
    unordered_map<string, long> prev;
    vector<long> toLCM;

    queue<pair<string, pair<string, Pulse>>> Q;

    for (long i = 0; !foundrx; i++) {
        Q.emplace("broadcaster", make_pair("button", LOW));

        while (!Q.empty()) {
            auto [name, pp] = Q.front();
            auto [sender, pulse] = pp;
            Q.pop();

            if (pulse == LOW) {
                if (prev.find(name) != prev.end() && count[name] == 2
                    && find(intoIntoRx.begin(), intoIntoRx.end(), name) != intoIntoRx.end()) {
                    toLCM.push_back(i - prev[name]);
                }
                prev[name] = i;
                count[name]++;
            }
            if (toLCM.size() == intoIntoRx.size()) {
                cout << "Part 2: " << findLCM(toLCM) << endl;
                foundrx = true;
                break;
            }

            Module &mod = modules[name];
            // cout << sender << " -" << (pulse == LOW ? "low" : "high") << "-> " << mod.name << endl;

            if (pulse == HIGH) {
                high++;
            } else {
                low++;
            }

            if (mod.type == FLIPFLOP) {
                if (pulse == LOW) {
                    if (mod.pulse == LOW) {
                        for (auto &output : mod.outputs) {
                            Q.emplace(output, make_pair(mod.name, HIGH));
                        }

                        mod.pulse = HIGH;
                    } else {
                        for (auto &output : mod.outputs) {
                            Q.emplace(output, make_pair(mod.name, LOW));
                        }

                        mod.pulse = LOW;
                    }
                }

            } else if (mod.type == CONJUNCTION) {
                mod.inputs[sender] = pulse;

                bool allHigh = true;
                for (auto &input : mod.inputs) {
                    if (input.second == LOW) {
                        allHigh = false;
                        break;
                    }
                }
                if (allHigh) {
                    for (auto &output : mod.outputs) {
                        Q.emplace(output, make_pair(mod.name, LOW));
                    }
                } else {
                    for (auto &output : mod.outputs) {
                        Q.emplace(output, make_pair(mod.name, HIGH));
                    }
                }
            } else {
                for (auto &output : mod.outputs) {
                    Q.emplace(output, make_pair(mod.name, pulse));
                }
            }
        }

        if (i == 999) {
            cout << "Part 1: " << high * low << endl;
        }
    }
}