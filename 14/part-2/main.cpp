#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

void recursion(vector<uint64_t> &addresses, uint64_t address, string mask) {
    size_t pos = mask.find("X");
    if (pos == string::npos)
        addresses.push_back(address);
    else {
        pos = 35 - pos;
        uint64_t address0 = (address & ~(1ULL << pos)), address1 = (address | (1ULL << pos));
        mask[35 - pos] = '0';
        recursion(addresses, address0, mask);
        recursion(addresses, address1, mask);
    }
}

vector<uint64_t> applyMask(uint64_t address, string mask) {
    vector<uint64_t> addresses;
    string s = mask;
    replace(s.begin(), s.end(), 'X', '0');
    address |= stoull(s, 0, 2);
    recursion(addresses, address, mask);
    return addresses;
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

                for (auto a : applyMask(address, mask)) {
                    memory[a] = stoull(valueMatch.str());
                }
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