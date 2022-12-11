#pragma once

struct Range {
	int start;
	int end;
};

bool FullyContained(Range elf1, Range elf2);

bool Overlap(Range elf1, Range elf2);