#pragma once
#include <string>
#include <vector>

using namespace std;

struct Directory;
struct File;

struct Directory {
public:
	Directory* fatherDir;
	string name;
	vector<File> files;
	vector<Directory> subDirs;
};
struct File
{
public:
	string name;
	Directory* dir;
	int size;
};