#pragma once

#include "Constants.h"

struct Schema {
	uint64_t id;
	char plane[MAX_TEXT];
	char type[MAX_TEXT];
	uint64_t flights;

	Schema();
	Schema(uint64_t id, const char* plane, const char* type, uint64_t flights);
};


std::ostream& operator<<(std::ostream& os, const Schema& s) {
	return os << s.id << ' ' << s.plane << ' ' << s.type << ' ' << s.flights;
}