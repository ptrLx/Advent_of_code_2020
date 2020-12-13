#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool in_a_row(vector<pair<int, unsigned long>> &buses) {
    unsigned long depart_last = buses[0].second - 1;
    for (auto &[bus, depart_time] : buses) {
        if (depart_time != depart_last + 1)
            return false;
        depart_last = depart_time;
    }
    return true;
}

int main() {
    vector<pair<int, unsigned long>> buses;

    // Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else {
        string line;
        getline(inputfile, line);
        while (getline(inputfile, line, ','))
            try {
                buses.push_back({stoi(line), 0});
            } catch (invalid_argument e) {
                buses.push_back({-1, 0});
            }
    }
    inputfile.close();

    // May take a while ...
    long now = 0;
    unsigned long depart_last = 0;
    while (!in_a_row(buses)) {
        for (auto &[bus, depart_time] : buses) {
            if (bus == -1)
                depart_time = ++depart_last;
            else {
                depart_time  = now + bus - (now % bus);
                while(depart_time <= depart_last) {
                    depart_time += bus;
                }
                depart_last = depart_time;
            }
        }
        depart_last = 0;
        now += buses[0].first;
        // if(!(now % 10000))
        //     cout << now << endl;
    }

    cout << "The earliest timestamp such that all of the listed bus IDs depart at offsets matching their positions in the list is "
         << buses[0].second
         << "." << endl;
    return 0;
}