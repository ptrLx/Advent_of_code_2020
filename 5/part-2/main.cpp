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
    bool reserved[913] = {0};

    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            reserved[calcSeatID(line)] = true;
        }
    }
    inputfile.close();

    for(int i = 0; i < sizeof(reserved)/sizeof(reserved[0]); i++) {
        if(!reserved[i] && reserved[i-1] && reserved[i+1]) {
            cout << "Your seat ID is " << i << "." << endl;
        }
    }

    return 0;
}