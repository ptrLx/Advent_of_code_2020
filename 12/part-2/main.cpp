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
    pair<int, int> pos = {0, 0};      // north, east
    pair<int, int> wayPos = {1, 10};  // north, east
    int temp;

    for (auto [c, val] : instructions) {
        switch (c) {
            case 'N':
                wayPos.first += val;
                break;
            case 'S':
                wayPos.first -= val;
                break;
            case 'E':
                wayPos.second += val;
                break;
            case 'W':
                wayPos.second -= val;
                break;
            case 'L':
                while (val) {
                    temp = wayPos.first;
                    wayPos.first = wayPos.second;
                    wayPos.second = -1 * temp;
                    val -= 90;
                }
                break;
            case 'R':
                while (val) {
                    temp = wayPos.first;
                    wayPos.first = -1 * wayPos.second;
                    wayPos.second = temp;
                    val -= 90;
                }
                break;
            case 'F':
                pos.first += val * wayPos.first;
                pos.second += val * wayPos.second;
        }
    }

    cout << "The Manhattan distance between that location and the ship's starting position is " << abs(pos.first) + abs(pos.second) << "." << endl;
    return 0;
}