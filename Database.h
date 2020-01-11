#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Constants.h"
#include "Schema.h"

class Database final {
	std::vector<Schema> db;
	std::string filePath;
	bool sorted;
private:
	void save() const;
	Schema* binarySearch(uint64_t id);

public:

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	Database(const char* FilePath = FILE_PATH);

	bool create(uint64_t id, const char* plane, const char* type, uint64_t flights);
	bool del(uint64_t id);
	bool update(uint64_t id, const char* type_plane, bool flag);
	bool update(uint64_t id, uint64_t id_flights, bool flag);
	void show(unsigned offset, unsigned limit) const;
	void optimize();

	Schema* search(uint64_t id);

	~Database();
};

