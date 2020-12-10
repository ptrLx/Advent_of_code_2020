#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<unsigned int> numbers;

    //Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            numbers.push_back(stoi(line));
        }
    }
    inputfile.close();

    //Bruteforce
    for(auto number : numbers) {
        for(auto other : numbers) {
            if(number + other == 2020) {
                cout << number << "\t" << other << endl;
            }
        }
    }
    return 0;
}