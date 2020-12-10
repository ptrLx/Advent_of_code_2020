#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<pair<int, int>> adapters;

    adapters.push_back({0, 1});  // charging outlet

    // Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else
        for (string line; getline(inputfile, line);) {
            adapters.push_back({stoi(line), 1});
        }
    inputfile.close();

    sort(adapters.begin(), adapters.end());
    adapters.push_back({(adapters[adapters.size() - 1].first + 3), 1});  // built-in

    // Find factors for multiplication
    for(int i = 1; i < adapters.size() - 2; i++) {
        if(adapters[i+1].first - adapters[i-1].first <= 3)
            adapters[i].second = 2;
        if(adapters[i-2].second == 2 && adapters[i-1].second == 2 && adapters[i].second == 2) { // Remove duplicates
            adapters[i-2].second = adapters[i-1].second = 1;
            adapters[i].second = 7;
        }
    }

    unsigned long prod = 1;
    for(auto i : adapters)
        prod *= i.second;

    cout << "The answer is " <<  prod << "." << endl;
    return 0;
}
