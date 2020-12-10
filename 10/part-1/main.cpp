#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> adapters;

    adapters.push_back(0);  // charging outlet

    //Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else
        for (string line; getline(inputfile, line);) {
            adapters.push_back(stoi(line));
        }
    inputfile.close();

    sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters[adapters.size() - 1] + 3);  // built-in

    //Find differences
    int count1J = 0, count3J = 0;
    for (int i = 0; i < adapters.size() - 1; i++) {
        if (adapters[i] == adapters[i + 1] - 1)
            count1J++;
        else if (adapters[i] == adapters[i + 1] - 3)
            count3J++;
    }

    cout << "The answer is " << count1J * count3J << "." << endl;
    return 0;
}
