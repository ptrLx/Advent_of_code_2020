#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

void applyMask(uint64_t &value, string &mask) {
    uint64_t maskOr = 0, maskAnd = 0b1111111111111111111111111111000000000000000000000000000000000000;

    string s = mask;
    replace(s.begin(), s.end(), 'X', '1');
    maskAnd |= stoull(s, 0, 2);

    s = mask;
    replace(s.begin(), s.end(), 'X', '0');
    maskOr = stoull(s, 0, 2);

    (value &= maskAnd) |= maskOr;
}

int main() {
    map<uint64_t, uint64_t> memory;
    string mask;

    // Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else {
        regex maskRE{"([01X]{36}$)"};
        regex memRE{R"(^mem\[[0-9]+\] = [0-9]+)"};
        regex addressRE{R"([0-9]+)"};
        regex valueRE{R"([0-9]+$)"};
        smatch match, valueMatch, addressMatch;
        uint64_t address;

        for (string line; getline(inputfile, line);) {
            if (regex_search(line, match, maskRE)) {
                mask = match.str();
            } else if (regex_search(line, match, memRE)) {
                regex_search(line, addressMatch, addressRE);
                regex_search(line, valueMatch, valueRE);
                address = stoull(addressMatch.str());
                memory[address] = stoull(valueMatch.str());

                applyMask(memory[address], mask);

                // cout << bitset<36>(memory[address]) << "        -> mask" << endl
                //      << mask << "        =>" << endl
                //      << bitset<36>(memory[address]) << endl
                //      << endl;
            }
        }
    }
    inputfile.close();

    uint64_t sum = 0;
    for (auto &[address, value] : memory)
        sum += value;

    cout << "The sum of all values left in memory after it completes is " << sum << "." << endl;

    return 0;
}