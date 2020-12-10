#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long findSum(int start, int end, vector<long> &numbers) {
    long sum = 0;
    for (int i = start; i <= end; i++)
        sum += numbers[i];
    return sum;
}

long findMin(int start, int end, vector<long> &numbers) {
    long minTemp = numbers[start++];
    for (int i = start; i <= end; i++)
        minTemp = (numbers[i] < minTemp) ? numbers[i] : minTemp;
    return minTemp;
}

long findMax(int start, int end, vector<long> &numbers) {
    long maxTemp = numbers[start++];
    for (int i = start; i <= end; i++)
        maxTemp = (numbers[i] > maxTemp) ? numbers[i] : maxTemp;
    return maxTemp;
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

    //Find set
    for (int i1 = 0; i1 < numbers.size(); i1++)
        for (int i2 = i1 + 1; i2 < numbers.size(); i2++)
            if (findSum(i1, i2, numbers) == 217430975)
                cout << "The answer is " << findMin(i1, i2, numbers) + findMax(i1, i2, numbers) << "." << endl;

    return 0;
}