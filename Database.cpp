#include "Database.h"

void Database::save() const {
	std::ofstream file(filePath, std::ios::binary);
	for (const Schema& plane : db) {
		if (plane.flights == INVALID_FLIGHTS)
			continue;
		file.write((const char*)&plane, sizeof(Schema));
	}
}

Schema* Database::binarySearch(uint64_t id) {
	int64_t first = 0,
		last = db.size() - 1,
		mid = 0;
	while (first <= last && mid >= 0) {
		mid = first + (last - first) / 2;
		if (db[mid].id == id && db[mid].flights != INVALID_FLIGHTS)
			return &db[mid];
		else if (db[mid].id < id)
			first = mid + 1;
		else
			last = mid - 1;
	}

	return nullptr;
}

Database::Database(const char* FilePath) {
	filePath = FilePath;
	sorted = false;

	std::ifstream file(FilePath, std::ios::binary | std::ios::ate);
	int size = file.tellg();
	if (size != -1) {
		file.seekg(std::ios::beg);
		db.reserve(size / sizeof(Schema));
		Schema temp;
		while (file.read((char*)&temp, sizeof(Schema)))
			db.push_back(temp);
	}
}

bool Database::create(uint64_t id, const char* plane, const char* type, uint64_t flights) {

	if (search(id) != nullptr)
		return false;

	if ((id > MAX_NUMBER) || (flights > MAX_NUMBER) ||
		(strlen(plane) >= MAX_TEXT) || (strlen(type) >= MAX_TEXT))
		return false;

	db.push_back(Schema(id, plane, type, flights));

	sorted = false;
	return true;
}

bool Database::del(uint64_t id) {
	Schema* plane = search(id);
	if (plane == nullptr)
		return false;
	plane->flights = INVALID_FLIGHTS;
	return true;
}

bool Database::update(uint64_t id, const char* type_plane, bool flag) {
	if (strlen(type_plane) >= MAX_TEXT)
		return false;

	Schema* plane = search(id);
	if (plane == nullptr)
		return false;
	if (flag)
		strcpy_s(plane->type, type_plane);
	else
		strcpy_s(plane->plane, type_plane);
	return true;
}

bool Database::update(uint64_t id, uint64_t id_flights, bool flag) {
	if (id_flights > MAX_NUMBER)
		return false;

	Schema* plane = search(id);
	if (plane == nullptr)
		return false;
	if (flag)
		plane->id = id_flights;
	else
		plane->flights = id_flights;
	return true;
}

void Database::show(unsigned offset, unsigned limit) const {
	const std::size_t min = (db.size() < limit) ? (db.size()) : (limit);
	for (std::size_t index = offset; index < min; index++) {
		if(db[index].flights != INVALID_FLIGHTS)
			std::cout << db[index] << '\n';
	}
}

void Database::optimize() {
	std::sort(db.begin(), db.end(),
		[](const Schema& lhs, const Schema& rhs) -> bool {
		return lhs.id < rhs.id;
	}
	);
	sorted = true;
}

Schema* Database::search(uint64_t id) {
	//std::cout << "SORTED: " << ((sorted) ? ("TRUE") : ("FALSE")) << '\n';

	if (id > MAX_NUMBER)
		return nullptr;

	if (sorted) 
		return binarySearch(id);

	for (Schema& plane : db)
		if (plane.id == id && plane.flights != INVALID_FLIGHTS)
			return &plane;
	return nullptr;
}

Database::~Database() { save(); std::cout << "Saved!\n";  }