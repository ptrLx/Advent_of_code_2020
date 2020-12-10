#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class token {
    int min;
    int max;
    char c;
    string password;
public:
    token(const string &line) {
        string temp;
        char tempc;
        stringstream ss(line);
        getline(ss, temp, '-');
        min = stoi(temp);
        getline(ss, temp, ' ');
        max = stoi(temp);
        ss.get(c);
        ss.get(tempc);
        ss.get(tempc);
        getline(ss, password);
    }

    bool valid() {
        if((password[min-1] == c) != (password[max-1] == c))
            return true;
        else
            return false;
        
    }

    friend ostream &operator<<(ostream &out, token tk) {
        out << tk.min << " - " << tk.max << " " << tk.c << ": " << tk.password;
        return out;
    }

    ~token() {}
};

int main() {
    unsigned int countTokens = 0;

    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            token tk(line);
            if(tk.valid()) {
                cout << tk << endl;
                countTokens++;
            }
        }
    }
    inputfile.close();

    cout << "Count of valid passwords: " << countTokens << endl;
    
    return 0;
}