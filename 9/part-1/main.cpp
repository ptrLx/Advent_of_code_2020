#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> findPair(int index, vector<long> &numbers) {
    for(int i1 = index-25; i1 < index; i1++)
        for(int i2 = i1+1; i2 < index; i2++)
            if(numbers[i1] + numbers[i2] == numbers[index])
                return {i1, i2};
    throw invalid_argument("Not found");
    return {-1, -1};
}

int main() {
    vector<long> numbers;

    //Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile)
        cout << "No such file" << endl;
    else
        for (string line; getline(inputfile, line);)
            numbers.push_back(stol(line));
    inputfile.close();

    //Find pair
    for(int i = 25; i < numbers.size(); i++)
        try {
            pair<int, int> indexes = findPair(i, numbers);
        } catch (invalid_argument e) {
            cout << numbers[i] << ": no pair possible." << endl;
        }

    return 0;
}
