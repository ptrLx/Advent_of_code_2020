#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
    
    //Count trees
    int pos = 0;
    int treesCount = 0;
    for(auto line : lines) {
        pos %= line.size();

        if(line[pos] == '#')
            treesCount ++;

        pos += 3;
    }

    cout << "We encountered " << treesCount << " trees." << endl;

    return 0;
}