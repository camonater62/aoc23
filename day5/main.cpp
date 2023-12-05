#include <climits>
#include <condition_variable>
#include <fstream>
#include <functional>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
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

class Mapping {
public:
    Mapping(long destination, long source, long range)
        : destination(destination)
        , source(source)
        , range(range) {
    }

    bool inRange(long source) const {
        return source >= this->source && source <= this->source + range;
    }

    long sourceToDestination(long source) const {
        return destination + (source - this->source);
    }

public:
    long destination;
    long source;
    long range;
};

class Range {
public:
    Range(long start, long end)
        : start(start)
        , end(end) {
    }

    optional<Range> overlap(Mapping m) {
        if (end < m.source || start > m.source + m.range) {
            return nullopt;
        }

        long newStart = max(start, m.source);
        long newEnd = min(end, m.source + m.range);

        return Range(newStart, newEnd);
    }

public:
    long start;
    long end;
};

int main() {
    ifstream input("input.txt");
    string line;

    getline(input, line);
    line = split(line, ": ")[1];

    vector<long> seeds;
    for (string s : split(line, " ")) {
        seeds.push_back(stol(s));
    }

    // Skip 2 lines
    getline(input, line);
    getline(input, line);

    vector<vector<Mapping>> mappings;
    vector<Mapping> currentMappings;

    while (getline(input, line)) {
        if (line.length() == 0)
            continue;
        if (line.find(":") != string::npos) {
            mappings.push_back(currentMappings);
            currentMappings.clear();
            continue;
        }

        vector<string> parts = split(line, " ");
        long destination = stol(parts[0]);
        long source = stol(parts[1]);
        long range = stol(parts[2]);

        currentMappings.push_back(Mapping(destination, source, range));
    }

    mappings.push_back(currentMappings);

    long minLocation = LONG_MAX;

    for (long seed : seeds) {
        for (int i = 0; i < mappings.size(); i++) {
            for (Mapping mapping : mappings[i]) {
                if (mapping.inRange(seed)) {
                    seed = mapping.sourceToDestination(seed);
                    break;
                }
            }
        }
        if (seed < minLocation) {
            minLocation = seed;
        }
    }

    cout << minLocation << endl;

    minLocation = LONG_MAX;

    for (int i = 0; i < seeds.size(); i += 2) {
        vector<Range> ranges;
        ranges.emplace_back(seeds[i], seeds[i] + seeds[i + 1]);

        for (int j = 0; j < mappings.size(); j++) {

            sort(mappings[j].begin(), mappings[j].end(),
                [](Mapping a, Mapping b) { return a.source < b.source; });
            sort(ranges.begin(), ranges.end(), [](Range a, Range b) { return a.start < b.start; });

            // for (Range r : ranges) {
            //     cout << "[" << r.start << ", " << r.end << "]";
            // }
            // cout << endl;
            vector<Range> newRanges;
            while (ranges.size() > 0) {
                Range r = ranges[ranges.size() - 1];
                ranges.erase(ranges.begin() + ranges.size());
                bool found = false;
                for (Mapping mapping : mappings[j]) {
                    optional<Range> overlap = r.overlap(mapping);
                    if (overlap.has_value()) {
                        Range o = *overlap;
                        newRanges.emplace_back(mapping.sourceToDestination(o.start),
                            mapping.sourceToDestination(o.end));
                        if (o.start > r.start) {
                            ranges.emplace_back(r.start, o.start - 1);
                        }
                        if (o.end < r.end) {
                            ranges.emplace_back(o.end + 1, r.end);
                        }

                        found = true;
                        break;
                    }
                }
                if (!found) {
                    newRanges.push_back(r);
                }
            }

            ranges = newRanges;
        }

        for (Range r : ranges) {
            // Not sure why -1
            minLocation = min(minLocation, r.start) - 1;
        }
    }

    cout << minLocation << endl;

    return 0;
}