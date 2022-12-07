#include "load_input.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace Input {
	ifstream LoadFile(string fileName)
	{
		ifstream file;file.open(fileName);
		if (!file.is_open()) {
			cout << "unable to open the file" << endl;
		}
		return file;
	}
}
