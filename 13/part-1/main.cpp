#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<pair<int, unsigned int>> buses;
    unsigned int now;

    // Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else {
        string line;
        getline(inputfile, line);
        now = stoi(line);
        while (getline(inputfile, line, ','))
            try {
                buses.push_back({stoi(line), 0});
            } catch (invalid_argument e) {}
    }
    inputfile.close();

    pair<int, unsigned int> depart_next = {0, ~0};
    for (auto &[bus, depart_time] : buses) {
        depart_time = now + bus - now % bus;
        if (depart_time < depart_next.second)
            depart_next = {bus, depart_time};
    }

    cout << "The ID of the earliest bus you can take to the airport multiplied by the number of minutes you'll need to wait for that bus is "
         << depart_next.first * (depart_next.second - now)
         << "." << endl;
    return 0;
}