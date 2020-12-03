#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countTrees(const vector<string> &lines, int shiftR, int shiftD) {
    int pos = 0;
    int treesCount = 0;
    for (int i = 0; i < lines.size(); i += shiftD) {
        pos %= lines[i].size();

        if (lines[i][pos] == '#')
            treesCount++;

        pos += shiftR;
    }

    return treesCount;
}

int main() {
    vector<string> lines;

    //Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            lines.push_back(line);
        }
    }
    inputfile.close();

    int count[5];
    long prod = 1;

    count[0] = countTrees(lines, 1, 1);
    count[1] = countTrees(lines, 3, 1);
    count[2] = countTrees(lines, 5, 1);
    count[3] = countTrees(lines, 7, 1);
    count[4] = countTrees(lines, 1, 2);

    for (int i : count) {
        cout << i << endl;
        prod *= i;
    }

    cout << endl << "Multiplied together the number of trees encounter " << prod << endl;
    
    return 0;
}