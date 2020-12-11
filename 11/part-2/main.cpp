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
                int offset;

                // nRight
                offset = 1;
                while (x + offset < seats[0].size()) {  // Not at end of line
                    if (seats[y][x + offset] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y][x + offset] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nLeft
                offset = 1;
                while (x - offset >= 0) {  // Not at start of line
                    if (seats[y][x - offset] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y][x - offset] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nBottom
                offset = 1;
                while (y + offset < seats.size()) {  // Not at end of vector
                    if (seats[y + offset][x] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y + offset][x] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nTop
                offset = 1;
                while (y - offset >= 0) {
                    if (seats[y - offset][x] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y - offset][x] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nBottomRight
                offset = 1;
                while (y + offset < seats.size() && x + offset < seats[0].size()) {
                    if (seats[y + offset][x + offset] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y + offset][x + offset] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nBottomLeft
                offset = 1;
                while (y + offset < seats.size() && x - offset >= 0) {
                    if (seats[y + offset][x - offset] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y + offset][x - offset] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nTopRight
                offset = 1;
                while (y - offset >= 0 && x + offset < seats[0].size()) {
                    if (seats[y - offset][x + offset] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y - offset][x + offset] == 'L') {
                        break;
                    }
                    offset++;
                }

                // nTopLeft
                offset = 1;
                while (y - offset >= 0 && x - offset >= 0) {
                    if (seats[y - offset][x - offset] == '#') {
                        neighbours++;
                        break;
                    } else if (seats[y - offset][x - offset] == 'L') {
                        break;
                    }
                    offset++;
                }                                  

                if (seats[y][x] == 'L' && neighbours == 0)
                    changes.push_back({y, x, '#'});
                else if (seats[y][x] == '#' && neighbours >= 5)
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