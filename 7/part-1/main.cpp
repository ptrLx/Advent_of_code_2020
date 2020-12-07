#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class bag {
   public:
    string color;
    vector<pair<string, int>> contain;

    bag() {}

    void addContain(string name, int count) {
        contain.push_back(make_pair(name, count));
    }

    ~bag() {}
};

int main() {
    vector<bag> bags;
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            bag newBag;
            string name;
            int count, pos;

            pos = line.find(" bags contain ");
            newBag.color = line.substr(0, pos);

            //for(int i = )

            //newBag.addContain(name, count);

            //name " bags contain " { count " " name " bag"[s](", " | ".") }

            bags.push_back(newBag);
        }
    }
    inputfile.close();

    cout << ""
         << "." << endl;
    return 0;
}