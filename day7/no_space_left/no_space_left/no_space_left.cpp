
#include <iostream>
#include <string>
#include <fstream>
#include <load_input.hpp>

constexpr auto MAX_SIZE = 100000;

using namespace std;
//enum to check the kind of command was given
enum Commands {
    NO_COMMAND = 0,
    CHANGE_DIRECTORY = 1,
    LIST = 2
};

Commands findCommand(string line);
bool isDirectory(string line);

//we need to check the currentDir we are at
string currentDir;

int main()
{
    string line;
    auto file = Input::LoadFile("input.txt");
    while (getline(file, line)) {
        cout << line << endl;
        const auto command = findCommand(line);

        if (isDirectory(line)) {
            cout << line << " Is a directory ! " << endl;
        }

        cout << command << endl;
    }
    while (true) {

    }
}

//this method will check if we find the command input in the line, and gather the type of command.
Commands findCommand(string line)
{
    auto s = line.find("$");
    //the command we found in the line.
    Commands currentCommand = NO_COMMAND;
    if (s != string::npos) {
        cout << "Found a command in the line : " << line << " index : " << s << endl;
        //here we get the type of command for this line
        {
            const auto cd = line.find("cd");
            const auto ls = line.find("ls");

            if (cd != string::npos)currentCommand = CHANGE_DIRECTORY;
            if (ls != string::npos)currentCommand = LIST;
        }
    }
    return currentCommand;
}

bool isDirectory(string line)
{
    const auto s = line.find("dir");
    if (s != string::npos) {
        return true;
    }
    return false;
}

