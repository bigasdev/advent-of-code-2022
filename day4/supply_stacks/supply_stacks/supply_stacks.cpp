#include "load_input.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

//the crate class, here we'll have the index for the start and finish of the line
//and the string of the crate itself.
class Crate {
public:
    vector<int> subIndex;
    int line = 0;
    string crate;
};

void supply_debug();

//lists and what not
map<string, string> lines;
vector<Crate> crates;
vector<vector<int>> instructions;

int main()
{
    //debug purpouses
    bool working = true;

    //the load of the input
    std:ifstream file = Input::LoadFile("input.txt");
    string line;
    int currentLine = 0;

    //main loop, we want to execute the advent logic here
    while (getline(file, line)) {
        cout << line << endl;

        //we want to register the crates.
        int currentLineIndex = 0; 
        //we loop through the characters to extract the exact keywrod
        for (auto key : line) {
            if (key == '[') {
                auto crate = line.substr(currentLineIndex, currentLineIndex + 3);
                auto realCrate = crate.substr(0, 3);

                //creation of the crate object and adding the line to the vector
                auto c = Crate();
                c.subIndex.push_back(currentLineIndex);
                c.subIndex.push_back(currentLineIndex + 3);
                c.crate = realCrate;
                c.line = currentLine;
                crates.push_back(c);

                lines.insert(pair<string,string>(line,line));
            }
            currentLineIndex++;
        }

        //we know the line that registers an input has move on the start.
        auto key = line.substr(0, 4);
        int amount = 0;int fromAmt = 0; int toAmt = 0;
        vector<int> inst;
        if (key == "move") {
            auto number = line.substr(5, 2);
            amount = stoi(number);
            cout << amount << endl;
        }
        auto from = line.find("from");
        if (from != string::npos) {
            fromAmt = stoi(line.substr(from + 5, 2));
        }
        auto to = line.find("to");
        if (to != string::npos) {
            toAmt = stoi(line.substr(to + 3, 2));

            //loading the instructions
            inst.push_back(amount);
            inst.push_back(fromAmt);
            inst.push_back(toAmt);
            instructions.push_back(inst);
        }

        currentLine++;
    }
    file.close();
    //solving logic
    supply_debug();

    while (working) {

    }
    return 0;
}

void supply_debug()
{
    cout << endl;
    cout << "Lines on the app : " << endl;
    for (auto const& line : lines) {
        cout << line.second << endl;
    }

    cout << "Crates on the app : " << endl;
    for (auto const& crate : crates) {
        cout << crate.crate << " At : " << crate.line << " Index : " << crate.subIndex[0] << " " << crate.subIndex[1] << endl;
    }

    for (auto const& inst : instructions) {
        cout << "Move : " << inst[0] << " From : " << inst[1] << " To : " << inst[2] << endl;
    }
}

