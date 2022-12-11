#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>

#include "Funcs.h"

#define INPUT 1
#if INPUT == 0
#define PATH "Sample.txt"
#else
#define PATH "Puzzle.txt"
#endif

#define PART 2



void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	std::string result = "";

	std::vector<std::stack<char>*> stacks;

	while (std::getline(file, text)) {
		if (text == "")
			break;

		ProcessRow(text, stacks); // build the stacks
	}

	// we now have all the stacks but they are upside down
	for (int i = 0; i < stacks.size(); ++i) {
		ReverseStack(*stacks[i]); // lets reverse them
	}

	while (std::getline(file, text)) {
		ProcessCommand(stacks, text); // process all the commands
	}

	for (int i = 0; i < stacks.size(); ++i) {
		result += stacks[i]->top(); // get the top of each stack
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;

	file.close();
	
	for (int i = 0; i < stacks.size(); ++i) {
		delete stacks[i]; // cleanup
	}
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	std::string result = "";

	std::vector<std::stack<char>*> stacks;

	while (std::getline(file, text)) {
		if (text == "")
			break;

		ProcessRow(text, stacks); // build the stacks
	}

	// we now have all the stacks but they are upside down
	for (int i = 0; i < stacks.size(); ++i) {
		ReverseStack(*stacks[i]); // lets reverse them
	}

	while (std::getline(file, text)) {
		ProcessCommandRetainOrder(stacks, text); // process all the commands
	}

	for (int i = 0; i < stacks.size(); ++i) {
		result += stacks[i]->top(); // get the top of each stack
	}

	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;

	file.close();

	for (int i = 0; i < stacks.size(); ++i) {
		delete stacks[i]; // cleanup
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

void ProcessRow(std::string text, std::vector<std::stack<char>*>& stacks) {
	int stacknum = 0;
	for (int i = 1; i < text.length(); i += 4) {
		char crate = text[i];

		if (isdigit(crate))
			return; // we have loaded all crates

		if (stacknum + 1 > stacks.size()) {
			stacks.push_back(new std::stack<char>);
		}

		if (crate != ' ') // we don't want empty space in our stacks
			stacks[stacknum]->push(crate);
		stacknum++;
	}
}

void ReverseStack(std::stack<char>& stack) {
	std::queue<char> tempQueue;

	while (!stack.empty()) {
		tempQueue.push(stack.top());
		stack.pop();
	}

	while (!tempQueue.empty()) {
		stack.push(tempQueue.front());
		tempQueue.pop();
	}
}

void ProcessCommand(std::vector<std::stack<char>*>& stacks, std::string command) {
	int amount = stoi(command.substr(command.find("move") + 5));
	int from   = stoi(command.substr(command.find("from") + 5)) - 1;
	int to	   = stoi(command.substr(command.find("to") + 3)) - 1;

	for (int i = 0; i < amount; ++i) {
		stacks[to]->push(stacks[from]->top());
		stacks[from]->pop();
	}
}

void ProcessCommandRetainOrder(std::vector<std::stack<char>*>& stacks, std::string command) {
	std::stack<char> tempStack;

	int amount = stoi(command.substr(command.find("move") + 5));
	int from = stoi(command.substr(command.find("from") + 5)) - 1;
	int to = stoi(command.substr(command.find("to") + 3)) - 1;

	for (int i = 0; i < amount; ++i) {
		tempStack.push(stacks[from]->top());
		stacks[from]->pop();
	}

	while (!tempStack.empty()) {
		stacks[to]->push(tempStack.top());
		tempStack.pop();
	}
}