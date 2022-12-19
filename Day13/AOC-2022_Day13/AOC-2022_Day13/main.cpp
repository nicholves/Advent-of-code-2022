#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#include "Funcs.h"

#define INPUT 0
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#endif

#define PART 1


void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;

	std::pair<std::string, std::string> pair;
	size_t counter = 0;
	size_t pairNum = 0;

	while (std::getline(file, text)) {
		if (counter % 3 == 0)
			pair.first = text.substr(1, text.size() - 2); // we don't care that the packet itself is a list

		if (counter % 3 == 1)
			pair.second = text.substr(1, text.size() - 2); // we don't care that the packet itself is a list

		if (counter % 3 == 2) {
			pairNum++;
			if (CheckPair(pair)) {
				result += pairNum;
			}
		}

		counter++;
	}

	std::cout << "Answer to Part 1 with " << PATH << ": " << result << std::endl;
}

void part2(std::string path) {
	std::ifstream file(path);
	std::string text;

	int result = 0;


	while (std::getline(file, text)) {
		
	}

	


	std::cout << "Answer to Part 2 with " << PATH << ": " << result << std::endl;
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

int CheckPair(const std::pair<std::string, std::string>& pair) {
	std::vector<std::string> elementsFirst, elementsSecond;

	int index = 0;
	 do {
		 if (pair.first[index] == '[') {
			 int endex = index + 1;
			 int depth = 1;
			 for (size_t i = endex; i < pair.first.size(); ++i) {
				 if (pair.first[i] == '[') {
					 depth++;
				 }
				 else if (pair.first[i] == ']') {
					 depth--;
				 }
				 if (depth == 0) {
					 endex = i;
					 break;
				 }
			 }
			 elementsFirst.push_back(pair.first.substr(index, endex - index + 1));
			 index = endex + 2;
		 }
		 else {
			 elementsFirst.push_back(pair.first.substr(index, pair.first.find(',', index) - index));
			 index = pair.first.find(',', index) + 1;
		 }
	 } while (index < pair.first.size() && pair.first.find(',', index) != std::string::npos);
	 // we still might need one more element
	 if (index < pair.first.size()) {
		 if (pair.first[index] == '[') {
			 elementsFirst.push_back(pair.first.substr(index));
		 }
		 else {
			 elementsFirst.push_back(pair.first.substr(index));
		 }
	 }


	 index = 0;
	 do {
		 if (pair.second[index] == '[') {
			 int endex = index + 1;
			 int depth = 1;
			 for (size_t i = endex; i < pair.second.size(); ++i) {
				 if (pair.second[i] == '[') {
					 depth++;
				 }
				 else if (pair.second[i] == ']') {
					 depth--;
				 }
				 if (depth == 0) {
					 endex = i;
					 break;
				 }
			 }
			 elementsSecond.push_back(pair.second.substr(index, endex - index + 1));
			 index = endex + 2;
		 }
		 else {
			 elementsSecond.push_back(pair.second.substr(index, pair.second.find(',', index) - index));
			 index = pair.second.find(',', index) + 1;
		 }
	 } while (index < pair.second.size() && pair.second.find(',', index) != std::string::npos);
	 // we still might need one more element
	 if (index < pair.second.size()) {
		 if (pair.second[index] == '[') {
			 elementsSecond.push_back(pair.second.substr(index));
		 }
		 else {
			 elementsSecond.push_back(pair.second.substr(index));
		 }
	 }

	 return LeftvRight(elementsFirst, elementsSecond) ? 1 : 0;
}

// make copies so we can mess them up
bool LeftvRight(std::vector<std::string> left, std::vector<std::string> right, bool recursiveCall) {
	while (left.size() > 0 && right.size() > 0) {
		std::string currLeft = left[0];
		std::string currRight = right[0];

		if (currLeft == "") { return true; }
		if (currLeft[0] != '[') { // left is an integer
			if (currRight == "") { return false; }
			if (currRight[0] != '[') { // right is an integer
				if (stoi(currRight) < stoi(currLeft)) {
					return false;
				}
				else if (recursiveCall) {
					return true;
				}

				left.erase(left.begin()); // if this is too slow we can flip to a queue
				right.erase(right.begin());
				continue;
			}

			// right is a list
			Winner winner = ListvInt(currRight, stoi(currLeft));

			if (winner == FIRSTARG) { // right was bigger
				return false;
			}

			left.erase(left.begin()); // if this is too slow we can flip to a queue
			right.erase(right.begin());
			continue;
		}

		else { // left is a list
			if (currRight == "") { return false; }
			if (currRight[0] != '[') { // right is an integer
				Winner winner = ListvInt(currLeft, stoi(currRight));

				if (winner == SECONDARG) { // right was bigger
					return false;
				}

				left.erase(left.begin()); // if this is too slow we can flip to a queue
				right.erase(right.begin());
				continue;
			}

			// left is a list and right is a list
			Winner winner = ListvList(currLeft, currRight);

			if (winner == SECONDARG) {
				return false;
			}

			left.erase(left.begin()); // if this is too slow we can flip to a queue
			right.erase(right.begin());
			continue;
		}
		

		assert(0); // unreachable
	}

	return right.size() >= left.size(); // both equal to zero is fine also
}



Winner ListvList(std::string list1, std::string list2, bool recursiveCall) {
	list1 = list1.substr(1, list1.size() - 2); // remove the beggining & ending square brackets
	list2 = list2.substr(1, list2.size() - 2); // remove the beginning & ending square brackets
	std::vector<std::string> elementsFirst, elementsSecond;

	int index = 0;
	do {
		if (list1[index] == '[') {
			int endex = index + 1;
			int depth = 1;
			for (size_t i = endex; i < list1.size(); ++i) {
				if (list1[i] == '[') {
					depth++;
				}
				else if (list1[i] == ']') {
					depth--;
				}
				if (depth == 0) {
					endex = i;
					break;
				}
			}
			elementsFirst.push_back(list1.substr(index, endex - index + 1));
			index = endex + 2;
		}
		else {
			elementsFirst.push_back(list1.substr(index, list1.find(',', index) - index));
			index = list1.find(',', index) + 1;
		}
	} while (index < list1.size() && list1.find(',', index) != std::string::npos);
	// we still might need one more element
	if (index < list1.size()) {
		if (list1[index] == '[') {
			elementsFirst.push_back(list1.substr(index));
		}
		else {
			elementsFirst.push_back(list1.substr(index));
		}
	}


	index = 0;
	do {
		if (list2[index] == '[') {
			int endex = index + 1;
			int depth = 1;
			for (size_t i = endex; i < list2.size(); ++i) {
				if (list2[i] == '[') {
					depth++;
				}
				else if (list2[i] == ']') {
					depth--;
				}
				if (depth == 0) {
					endex = i;
					break;
				}
			}
			elementsSecond.push_back(list2.substr(index, endex - index + 1));
			index = endex + 2;
		}
		else {
			elementsSecond.push_back(list2.substr(index, list2.find(',', index) - index));
			if (list2.find(',', index) != std::string::npos) {
				index = list2.find(',', index) + 1;
			}
			else {
				index++;
			}
		}
	} while (index < list2.size() && list2.find(',', index) != std::string::npos);
	// we still might need one more element
	if (index < list2.size()) {
		if (list2[index] == '[') {
			elementsSecond.push_back(list2.substr(index));
		}
		else {
			elementsSecond.push_back(list2.substr(index));
		}
	}

	if (recursiveCall) {
		for (size_t i = 0; i < elementsFirst.size(); ++i) {
			if (elementsFirst[i].find('[') != std::string::npos) {
				recursiveCall = false;
				break;
			}
		}
		for (size_t i = 0; i < elementsSecond.size(); ++i) {
			if (elementsSecond[i].find('[') != std::string::npos) {
				recursiveCall = false;
				break;
			}
		}
	}

	return LeftvRight(elementsFirst, elementsSecond, recursiveCall) ? FIRSTARG : SECONDARG;
}

Winner ListvInt(std::string list, int integer) {
	std::string integerList = "[" + std::to_string(integer) + "]";
	return ListvList(list, integerList, true);
}