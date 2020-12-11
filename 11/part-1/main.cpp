#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct change {
    int y, x;
    char v;

    void apply(vector<string> &seats) {
        seats[y][x] = v;
    }
};

int main() {
    vector<string> seats;

    //Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else
        for (string line; getline(inputfile, line);) {
            seats.push_back(line);
        }
    inputfile.close();

    // Simulate people
    while (true) {
        vector<change> changes;
        for (int y = 0; y < seats.size(); y++) {
            for (int x = 0; x < seats[0].size(); x++) {
                if (seats[y][x] == '.')
                    continue;

                int neighbours = 0;
                bool neighbourDir[8];
                neighbourDir[0] = (x < seats[0].size() - 1 && seats[y][x + 1] == '#');                              // nRight
                neighbourDir[1] = (x > 0 && seats[y][x - 1] == '#');                                                // nLeft
                neighbourDir[2] = (y < seats.size() - 1 && seats[y + 1][x] == '#');                                 // nBottom
                neighbourDir[3] = (y > 0 && seats[y - 1][x] == '#');                                                // nTop
                neighbourDir[4] = (y < seats.size() - 1 && x < seats[0].size() - 1 && seats[y + 1][x + 1] == '#');  // nBottomRight
                neighbourDir[5] = (y < seats.size() - 1 && x > 0 && seats[y + 1][x - 1] == '#');                    // nBottomLeft
                neighbourDir[6] = (y > 0 && x < seats[0].size() - 1 && seats[y - 1][x + 1] == '#');                 // nTopRight
                neighbourDir[7] = (y > 0 && x > 0 && seats[y - 1][x - 1] == '#');                                   // nTopLeft

                for (bool b : neighbourDir)
                    if (b)
                        neighbours++;

                if (seats[y][x] == 'L' && neighbours == 0)
                    changes.push_back({y, x, '#'});
                else if (seats[y][x] == '#' && neighbours >= 4)
                    changes.push_back({y, x, 'L'});
            }
        }

        // Apply changes
        if (changes.size() == 0)
            break;
        else
            for (auto ch : changes) {
                ch.apply(seats);
            }
    }

    // How many seats end up occupied?
    int count = 0;
    for (int y = 0; y < seats.size(); y++)
        for (int x = 0; x < seats[0].size(); x++)
            if (seats[y][x] == '#')
                count++;
    cout << count << " seats end up occupied." << endl;
    return 0;
}