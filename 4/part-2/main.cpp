#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class passport {
   public:
    //byr, iyr, eyr, hgt, hcl, ecl, pid, cid
    string attr[8];

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
        //0-6 required; cid is optional
        for (int i = 0; i < 7; i++)
            if (attr[i] == "") {
                // cout << *this << "unvalid! Lack of attributes!" << endl;
                return false;
            }

        //validate byr
        if (attr[0].size() != 4 || stoi(attr[0]) < 1920 || stoi(attr[0]) > 2002) {
            // cout << *this << "unvalid (byr)!" << endl;
            return false;
        }

        //validate iyr
        if (attr[1].size() != 4 || stoi(attr[1]) < 2010 || stoi(attr[1]) > 2020) {
            // cout << *this << "unvalid (iyr)!" << endl;
            return false;
        }

        //validate eyr
        if (attr[2].size() != 4 || stoi(attr[2]) < 2020 || stoi(attr[2]) > 2030) {
            // cout << *this << "unvalid (eyr)!" << endl;
            return false;
        }

        //validate hgt
        switch (attr[3][attr[3].size() - 2]) {
            case 'c':
                if (attr[3][attr[3].size() - 1] != 'm' || stoi(attr[3]) < 150 || stoi(attr[3]) > 193) {
                    // cout << *this << "unvalid (hgt - c)!" << endl;
                    return false;
                } break;
            case 'i':
                if (attr[3][attr[3].size() - 1] != 'n' || stoi(attr[3]) < 59 || stoi(attr[3]) > 76) {
                    // cout << *this << "unvalid (hgt - i)!" << endl;
                    return false;
                } break;
            default:
                return false;
        }

        //validate hcl
        if (attr[4][0] != '#' || attr[4].size() != 7) {
            // cout << *this << "unvalid (hcl)!" << endl;
            return false;
        }

        //validate ecl
        string valid[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        if (find(begin(valid), end(valid), attr[5]) == end(valid)) {
            // cout << *this << "unvalid (ecl)!" << endl;
            return false;
        }

        //validate pid
        if (attr[6].size() != 9) {
            // cout << *this << "unvalid (pid)!" << endl;
            return false;
        }

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
    // vector<passport> validpp;
    // vector<passport> unvalidpp;
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
                    // cout << pp << endl;
                    // validpp.push_back(pp);
                    // } else {
                    //     cout << pp << "\tunvalid!" << endl;
                    //     unvalidpp.push_back(pp);
                }
                pp.reset();
            } else {
                pp.scan(line);
            }
        }
        if (pp.valid()) {
            counter++;
            // cout << pp << endl;
            // validpp.push_back(pp);
        }
    }
    inputfile.close();

    cout << counter << " passports are valid!" << endl;
    return 0;
}