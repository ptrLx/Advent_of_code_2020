#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class passport {
    //byr, iyr, eyr, hgt, hcl, ecl, pid, cid
    string attr[8];

   public:
    passport() {
        for (int i = 0; i < 8; i++)
            attr[i] = "";
    }

    void scan(const string &line) {
        stringstream ssline(line);
        string attrstr;
        string attrname;
        string attrwert;
        while (getline(ssline, attrstr, ' ')) {
            stringstream ssattr(attrstr);
            getline(ssattr, attrname, ':');
            getline(ssattr, attrwert, ':');
            if (attrname == "byr")
                attr[0] = attrwert;
            else if (attrname == "iyr")
                attr[1] = attrwert;
            else if (attrname == "eyr")
                attr[2] = attrwert;
            else if (attrname == "hgt")
                attr[3] = attrwert;
            else if (attrname == "hcl")
                attr[4] = attrwert;
            else if (attrname == "ecl")
                attr[5] = attrwert;
            else if (attrname == "pid")
                attr[6] = attrwert;
            else if (attrname == "cid")
                attr[7] = attrwert;
        }
    }

    bool valid() {
        //cid is optional
        for (int i = 0; i < 7; i++)
            if (attr[i] == "")
                return false;
        return true;
    }

    void reset() {
        for (int i = 0; i < 8; i++)
            attr[i] = "";
    }

    friend ostream &operator<<(ostream &out, const passport &pp) {
        for (string s : pp.attr)
            out << s << "\t";
        return out;
    }

    ~passport() {}
};

int main() {
    passport pp;
    int counter = 0;

    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            if (line == "") {
                if (pp.valid()) {
                    counter++;
                    cout << pp << endl;
                // } else {
                //     cout << pp << "\tunvalid!" << endl;
                }
                pp.reset();
            } else {
                pp.scan(line);
            }
        }
        if (pp.valid()) {
            counter++;
            cout << pp << endl;
        }
    }
    inputfile.close();

    cout << counter << " passports are valid!" << endl;
    return 0;
}