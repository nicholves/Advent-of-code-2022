#pragma once
#include <vector>

typedef std::pair<int64_t, int64_t> Location;

uint64_t ComputeDistance(Location loc1, Location loc2);

uint64_t BinarySearchEndpoint(std::set<int64_t>& checked, Location sensor, Location closest, uint64_t coverage);