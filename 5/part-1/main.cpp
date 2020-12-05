#include <fstream>
#include <iostream>

using namespace std;

int calcSeatID(string IDString) {
    unsigned int row, column = 0;

    for(int i = 0; i < 7; i++) {
        row <<= 1;
        if(IDString[i] == 'B')
            row++;
    }

    for (int i = 7; i < 10; i++) {
        column <<= 1;
        if (IDString[i] == 'R')
            column++;
    }
    
    return row * 8 + column;
}

int main() {
    int highest, current = 0;

    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            current = calcSeatID(line);
            if(current > highest)
                highest = current;
        }
    }
    inputfile.close();

    cout << "The highest seat ID on a boarding pass is " << highest << "." << endl;
    return 0;
}