#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    vector<pair<char, int>> instructions;

    // Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else
        for (string line; getline(inputfile, line);) {
            instructions.push_back({line[0], stoi(line.substr(1, line.size()))});
        }
    inputfile.close();

    // Simulator
    unsigned int dir = 1;         // N:0    E:1    S:2    W:3
    pair<int, int> pos = {0, 0};  // north, east

    for (auto [c, val] : instructions) {
        switch (c) {
            case 'N':
                pos.first += val;
                break;
            case 'S':
                pos.first -= val;
                break;
            case 'E':
                pos.second += val;
                break;
            case 'W':
                pos.second -= val;
                break;
            case 'L':
                dir = (dir - val / 90) % 4;
                break;
            case 'R':
                dir = (dir + val / 90) % 4;
                break;
            case 'F':
                switch (dir) {
                    case 0:
                        pos.first += val;
                        break;
                    case 1:
                        pos.second += val;
                        break;
                    case 2:
                        pos.first -= val;
                        break;
                    case 3:
                        pos.second -= val;
                }
                break;
        }
    }

    cout << "The Manhattan distance between that location and the ship's starting position is " << abs(pos.first) + abs(pos.second) << "." << endl;
    return 0;
}