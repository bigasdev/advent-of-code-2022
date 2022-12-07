
#include <iostream>
#include <string>
#include <fstream>
#include <load_input.hpp>
#include "inputs.hpp"
#include <vector>
#include <map>
#include <sstream>
#include <chrono>

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
File getFile(string line);

//we need to check the currentDir we are at
Directory* currentDir;
map<string, Directory> dirs;

int main()
{
    //just to check the time it is taking to execute my algorithm
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    //creating the first structure
    Directory dir;
    dir.name = "/";
    dirs.insert(pair<string,Directory>("/", dir));

    string line;
    auto file = Input::LoadFile("input.txt");
    //creation of the filesystem
    while (getline(file, line)) {
        const auto command = findCommand(line);

        switch (command) {
        case NO_COMMAND:
            break;
        case CHANGE_DIRECTORY: {
            string name = line.substr(5, line.size() - 1);
            if (name == "..")continue;

            auto d = dirs.find(name);
            currentDir = &d->second;
            continue;
            break;
        }
        case LIST:
            continue;
            break;
        }

        if (isDirectory(line)) {
            auto s = line.substr(4, line.size() - 1);
            Directory d;
            d.name = s;

            currentDir->subDirs.push_back(d);
            dirs.insert(pair<string, Directory>(s, d));
        }
        else {
            File f = getFile(line);

            //cout << "The file has: " << f.size << " bytes of memory, and its from the : " << f.dir->name << " directory" << endl;
        }
    }
    //debug
    {
        for (auto const& d : dirs) {
            int value = 0;
            cout << "- " << d.second.name << " (dir)" << endl;
            for (auto const& subdirs : d.second.subDirs) {
                cout << subdirs.name << endl;
            }
            for (auto const& f : d.second.files) {
                cout << " ";
                cout << "- (file, " << f.name << ") " << endl;
                value += f.size;
            }
            if (value >= MAX_SIZE) {
                cout << "- " << d.second.name << " (dir)" << "Has more than " << MAX_SIZE << " Size! So it should be counted" << endl;
            }
        }

        //checking the duration of the operation
        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        duration<double, std::milli> ms_double = t2 - t1;

        cout << endl;
        std::cout << ms_int.count() << "ms\n";
        std::cout << ms_double.count() << "ms\n";
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
        //cout << "Found a command in the line : " << line << " index : " << s << endl;
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

File getFile(string line)
{
    stringstream ss;
    ss << line;
    string temp;
    int found = 0;
    int size = 0;

    File file;

    //extracting all the integers from the file
    while (!ss.eof()) {
        ss >> temp;

        if (stringstream(temp) >> found) {
            size = found;
        }
            
        temp = "";
    }

    file.name = line;
    file.dir = currentDir;
    file.size = size;
    currentDir->files.push_back(file);

    return file;
}

