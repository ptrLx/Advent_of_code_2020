#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class operation { acc,
                       jmp,
                       nop };

class instruction {
   public:
    operation op;
    int value;
    bool executedOnce;

    instruction() : executedOnce(false) {}
    ~instruction() {}
};

int main() {
    vector<instruction> instructions;

    //Fileinput
    fstream inputfile;
    inputfile.open("inputfile", ios::in);
    if (!inputfile) {
        cout << "No such file" << endl;
    } else {
        for (string line; getline(inputfile, line);) {
            instruction instr;
            switch (line[0]) {
                case 'a':
                    instr.op = operation::acc;
                    break;
                case 'j':
                    instr.op = operation::jmp;
                    break;
                case 'n':
                    instr.op = operation::nop;
            }

            instr.value = stoi(line.substr(4, line.size()));
            instructions.push_back(instr);
        }
    }
    inputfile.close();

    //Bruteforce
    for (int i = 0; i < instructions.size(); i++) {
        //Modify
        if(instructions[i].op == operation::jmp)
            instructions[i].op = operation::nop;
        else if (instructions[i].op == operation::nop)
            instructions[i].op = operation::jmp;
        else
            continue;
        
        //Simulate
        int pc, acc = 0;
        while (pc < 646 && !instructions[pc].executedOnce) {
            instructions[pc].executedOnce = true;
            switch (instructions[pc].op) {
                case operation::acc:
                    acc += instructions[pc].value;
                    pc++;
                    break;
                case operation::jmp:
                    pc += instructions[pc].value;
                    break;
                case operation::nop:
                    pc++;
            }
        }

        //Undo modifications
        if (instructions[i].op == operation::jmp)
            instructions[i].op = operation::nop;
        else if (instructions[i].op == operation::nop)
            instructions[i].op = operation::jmp;
        for(auto inst : instructions)
            instructions[pc].executedOnce = false;

        // cout << "Modified " << i << ", pc " << pc << endl;

        if (pc > 645) {
            cout << "Success when changing instruction " << i << "." << endl;
            break;
        }
    }

    return 0;
}