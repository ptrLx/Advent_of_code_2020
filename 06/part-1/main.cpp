#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class answer {
   public:
    string answerstring;

    answer() : answerstring("") {}

    void addLine(const string &line) {
        for (char c : line) {
            if (answerstring.find(c) == string::npos) {
                answerstring += c;
            }
        }
    }
    void clear() {
        answerstring = "";
    }

    ~answer() {}
};

int main() {
    vector<answer> answers;
    int sum = 0;
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        answer current;
        for (string line; getline(inputfile, line);) {
            if (line == "") {
                answers.push_back(current);
                sum += current.answerstring.size();
                current.clear();
            } else {
                current.addLine(line);
            }
        }
    }
    inputfile.close();

    cout << "The sum of counts is " << sum << "." << endl;
    return 0;
}