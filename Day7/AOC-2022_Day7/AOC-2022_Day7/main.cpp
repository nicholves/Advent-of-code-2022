#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "Directory.h"
#include "Funcs.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#else
#define PATH "Puzzle.txt"
#endif

#define PART 2

#define MAXSIZE 100000

#define TOTALDISKSPACE 70000000
#define UPDATESIZE	   30000000

// attempt 1: didn't record
// attempt 2: 1523585
// attempt 3: 1543140 correct!


void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	std::string currPath;
	std::vector<Directory*> dirs;

	int result = 0;

	while (std::getline(file, text)) {
		if (text[0] == '$') {
			if (text[2] == 'c') {
				processCD(currPath, text);
			}

			if (text[2] == 'l') {
				continue;
			}
		}
		else {
			processLSData(currPath, dirs, text);
		}
	}

	for (int i = 0; i < dirs.size(); ++i) {
		Directory* dirTest = dirs[i];
		int size = dirs[i]->getTotalSize();

		if (size <= MAXSIZE)
			result += size;
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	std::cout << std::endl;

	file.close();

	//printFileSystem(*dirs[0]);

	for (int i = 0; i < dirs.size(); ++i) {
		delete dirs[i];
	}
}

// attempt 1: 1117448 correct!

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	std::string currPath;
	std::vector<Directory*> dirs;

	int result = 0;

	while (std::getline(file, text)) {
		if (text[0] == '$') {
			if (text[2] == 'c') {
				processCD(currPath, text);
			}

			if (text[2] == 'l') {
				continue;
			}
		}
		else {
			processLSData(currPath, dirs, text);
		}
	}

	const int AvailableSpace = TOTALDISKSPACE - dirs[0]->getTotalSize();
	const int NeedToFree	 = UPDATESIZE - AvailableSpace;

	int smallest = std::numeric_limits<int>::max();
	for (int i = 0; i < dirs.size(); ++i) {
		int size = dirs[i]->getTotalSize();

		if (size >= NeedToFree && size < smallest)
			smallest = size;
	}
	result = smallest;

	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;

	std::cout << std::endl;

	file.close();

	//printFileSystem(*dirs[0]);

	for (int i = 0; i < dirs.size(); ++i) {
		delete dirs[i];
	}
}


int main() {
#if PART == 1
	part1(PATH);
#endif

#if PART == 2
	part2(PATH);
#endif

	return 0;
}

void processCD(std::string& currPath, const std::string& commandText) {
	if (commandText.substr(5) == "..") {
		currPath = currPath.substr(0, currPath.size() - 1);
		int endIndex = currPath.find_last_of('/');
		currPath = currPath.substr(0, endIndex + 1);
		if (currPath == "")
			currPath = "/";
	}

	else if (commandText.substr(5) == "/") {
		currPath = "/";
	}

	else {
		std::string dir = commandText.substr(5);
		currPath += dir + '/';
	}
}

void processLSData(const std::string& currPath, std::vector<Directory*>& dirs, const std::string& text) {
	Directory* currentDir = nullptr;
	for (int i = 0; i < dirs.size(); ++i) {
		if (dirs[i]->getPath() == currPath)
			currentDir = dirs[i]; // a directory already exists in our knowledge
	}

	if (currentDir == nullptr) { // no directory exists for the current one
		currentDir = new Directory();
		currentDir->setPath(currPath);
		dirs.push_back(currentDir);
	}




	if (text[0] == 'd' ) { // we have a subdirectory
		std::string dirName = text.substr(4);
		std::string potentialPath = currPath + dirName + '/';
		for (int i = 0; i < dirs.size(); ++i) {
			if (dirs[i]->getPath() == potentialPath)
				return; // directory already exists
		}

		Directory* newDir = new Directory();
		newDir->setPath(potentialPath);
		currentDir->addSubdir(newDir);
		dirs.push_back(newDir);
	}


	else { // this is a file
		int fileSize = stoi(text);
		std::string fileName = text.substr(text.find(' ') + 1);

		currentDir->setSizeOfFile(fileName, fileSize);
	}
}

void printFileSystem(const Directory& dir, int depth) {
	std::string space = "";

	fillSpace(space, depth);
	
	std::cout << space << "- " << dir.getDirName() << " (dir)" << std::endl;
	
	const std::map<std::string, int>& map = dir.getFiles();

	fillSpace(space, depth + 2);
	for (std::pair<std::string, int> file : map) {
		std::cout << space << "- " << file.first << " (file, size=" << file.second << ")" << std::endl;
	}

	for (Directory* subdir : dir.getSubDirs()) {
		printFileSystem(*subdir, depth + 2);
	}
}

void fillSpace(std::string& space, int n) {
	space = "";
	for (int i = 0; i < n; ++i) {
		space += ' ';
	}
}