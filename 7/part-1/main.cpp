#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class bag {
   public:
    string color;
    vector<pair<string, int>> contain;
    vector<pair<bag *, int>> containPointer;
    vector<pair<bag *, int>> containedByPointer;

    bool containGold;

    bag() : color(""), containGold(false) {}

    void addContain(string name, int count) {
        contain.push_back(make_pair(name, count));
    }

    int findContainedByBags() {
        if (containGold) return 0;
        containGold = true;
        int count = 1;
        for (auto &cBy : containedByPointer) {
            count += cBy.first->findContainedByBags();
        }
        return count;
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

            line = line.substr(pos + 14, line.size());

            while (true) {
                try {
                    count = stoi(line.substr(0, 1));
                } catch (const std::invalid_argument &e) {
                    break;
                }

                line = line.substr(2, line.size());

                pos = line.find(" bag");
                name = line.substr(0, pos);

                newBag.addContain(name, count);
                pos += 4;

                if (line[pos] == 's')

                    pos++;
                if (line[pos] == '.')

                    break;
                else
                    line = line.substr(pos + 2, line.size());
            }

            // for (auto bag : newBag.contain) {
            //     if (bag.first == "shiny gold") {
            //         newBag.containGold = true;
            //     }
            // }
            bags.push_back(newBag);
        }
    }
    inputfile.close();

    for (auto &bag : bags) {
        for (auto &containdeBag : bag.contain) {
            for (auto &bagsearch : bags) {
                if (containdeBag.first == bagsearch.color) {
                    bag.containPointer.push_back({&bagsearch, containdeBag.second});
                    bagsearch.containedByPointer.push_back({&bag, containdeBag.second});
                    break;
                }
            }
        }
    }

    for (auto &goldBag : bags) {
        if (goldBag.color == "shiny gold") {
            cout << "Shiny gold is contained by " << goldBag.findContainedByBags()-1 << " bags at least once." << endl;
            break;
        }
    }

    return 0;
}