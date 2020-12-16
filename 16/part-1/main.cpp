#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct attribute {
    string name;
    int firstStart, firstEnd, secStart, secEnd;
};

int main() {
    vector<attribute> attributes;
    vector<array<int, 20>> nearbys;

    // Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else {
        regex attributeRE{R"(^[A-Za-z ]+: \d+-\d* or \d*-\d*)"};
        regex attributeNameRE{R"(^[A-Za-z ]+)"};
        regex nearbyRE{R"(^(\d+,){19}\d+)"};
        regex numberRE{R"(\d+)"};

        for (string line; getline(inputfile, line);) {
            if (regex_match(line, attributeRE)) {
                attribute attr;
                int offset = 0;
                cmatch match;
                regex_search(line.c_str(), match, attributeNameRE); // Name
                attr.name = match.str();
                offset += match.length() + 2;
                regex_search(line.c_str() + offset, match, numberRE); // firstStart
                attr.firstStart = stoi(match.str());
                offset += match.length() + 1;
                regex_search(line.c_str() + offset, match, numberRE); // firstEnd
                attr.firstEnd = stoi(match.str());
                offset += match.length() + 4;
                regex_search(line.c_str() + offset, match, numberRE); // secStart
                attr.secStart = stoi(match.str());
                offset += match.length() + 1;
                regex_search(line.c_str() + offset, match, numberRE); // secEnd
                attr.secEnd = stoi(match.str());
                attributes.push_back(attr);
            } else if (line == "your ticket:") {
                getline(inputfile, line);
                cout << "Your ticket:    " << line << endl;
            } else if (regex_match(line, nearbyRE)) {
                array<int, 20> next;
                int offset = 0;
                cmatch match;
                for (int i = 0; i < 20; i++) {
                    regex_search(line.c_str() + offset, match, numberRE);
                    next[i] = stoi(match.str());
                    offset += match.length() + 1;
                }
                nearbys.push_back(next);
            }
        }
    }
    inputfile.close();

    //Check nearbys in rage?
    int sum = 0;
    for(auto n : nearbys)
        for(auto i : n) {
            bool valid = false;
            for(auto a : attributes) {
                if((i >= a.firstStart && i <= a.firstEnd) || (i >= a.secStart && i <= a.secEnd)) {
                    valid = true;
                    break;
                }
            }
        if(!valid)
            sum += i;
        }

    cout << "The ticket scanning error rate is " << sum << "." << endl;

    return 0;
}