#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>

#include "Funcs.h"

#define INPUT 0
#if INPUT == 0
#define PATH "Sample.txt"
#elif INPUT == 1
#define PATH "Puzzle.txt"
#endif

#define PART 1

#define INTERESTINGLINE 10

int64_t minx = std::numeric_limits<int64_t>::max(), miny = std::numeric_limits<int64_t>::max(), maxx = 0, maxy = 0;

// attempt 1: 

void part1(std::string path) {
	std::ifstream file(path);
	std::string text;

	int64_t result = 0;

	std::set<int64_t> checked;

	while (std::getline(file, text)) {
		int64_t x = 0, y = 0;
		int cursor = 0;

		// sensors
		cursor = text.find("x=", cursor) + 2;
		x = stoi(text.substr(cursor, text.find(',', cursor) - cursor));
		cursor = text.find("y=", cursor) + 2;
		y = stoi(text.substr(cursor, text.find(',', cursor) - cursor));

		Location sensor = Location(x, y);

		// beacons
		cursor = text.find("x=", cursor) + 2;
		x = stoi(text.substr(cursor, text.find(',', cursor) - cursor));
		cursor = text.find("y=", cursor) + 2;
		y = stoi(text.substr(cursor, text.find(',', cursor) - cursor));

		Location beacon = Location(x, y);

		uint64_t distance = ComputeDistance(sensor, beacon);
		Location closest(sensor.first, INTERESTINGLINE);
		uint64_t distanceToIntersection = ComputeDistance(sensor, closest);

		if (distanceToIntersection > distance || ) {
			continue; // there is no intersection at all
		}
		result++;

		result += BinarySearchEndpoint(checked, sensor, closest, distance);
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

uint64_t ComputeDistance(Location loc1, Location loc2) {
	return abs(loc1.first - loc2.first) + abs(loc1.second - loc2.second);
}

uint64_t BinarySearchEndpoint(std::set<int64_t>& checked, Location sensor, Location closest, uint64_t coverage) {
	uint64_t result = 0;
	
	// check right
	int64_t bottom = closest.first;
	int64_t top = closest.first + coverage;
	int64_t maxRight = 0;
	while (true) {
		int64_t mid = (bottom + top) / 2;
		Location check(closest.first + mid, INTERESTINGLINE);
		if (ComputeDistance(check, sensor) == coverage) {
			maxRight = closest.first + coverage;
			break;
		}
		if (ComputeDistance(check, sensor) > coverage) {
			top = mid - 1;
		}
		else {
			bottom = mid + 1;
		}

		if (abs(bottom - top) <= 1) {
			Location check(closest.first + top, INTERESTINGLINE);
			if (ComputeDistance(check, sensor) < coverage)
				maxRight = top;
			else 
				maxRight = bottom;

			break;
		}
	}

	// check left
	bottom = closest.first - coverage;
	top = closest.first;
	int64_t maxLeft = 0;
	while (true) {
		int64_t mid = (bottom + top) / 2;
		Location check(closest.first + mid, INTERESTINGLINE);
		if (ComputeDistance(check, sensor) == coverage) {
			maxLeft = closest.first - coverage;
			break;
		}
		if (ComputeDistance(check, sensor) > coverage) {
			top = mid - 1;
		}
		else {
			bottom = mid + 1;
		}

		if (abs(bottom - top) <= 1) {
			Location check(closest.first + top, INTERESTINGLINE);
			if (ComputeDistance(check, sensor) < coverage)
				maxLeft = top;
			else
				maxLeft = bottom;

			break;
		}
	}

	checked.insert(Location(maxLeft, INTERESTINGLINE));
	checked.insert(Location(maxRight, INTERESTINGLINE));

	return abs(maxLeft) + abs(maxRight);
}