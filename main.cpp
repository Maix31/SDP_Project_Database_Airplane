#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const uint64_t INVALID_FLIGHTS = UINT64_MAX;

const uint64_t MAX_NUMBER = (1ULL << 50);
const uint64_t MAX_TEXT = (1ULL << 8);

struct Schema {
	uint64_t id;
	char plane[MAX_TEXT];
	char type [MAX_TEXT];
	uint64_t flights;

	Schema(){}

	Schema(uint64_t id, const char * plane, const char * type, uint64_t flights)
	: id(id)
	, flights(flights) {
		strcpy_s(this->plane, plane);
		strcpy_s(this->type, type);
	}
};

std::ostream& operator<<(std::ostream& os, const Schema& s) {
	return os << s.id << ' ' << s.plane << ' ' << s.type << ' ' << s.flights;
}

class Database {
	std::vector<Schema> db;
	std::string filePath;
	bool sorted;
private:
	void save() {
		std::ofstream file(filePath, std::ios::binary);
		for (const Schema& plane : db) {
			if (plane.flights == INVALID_FLIGHTS)
				continue;
			file.write((const char*)&plane, sizeof(Schema));
		}
	}

public:
	Database(const char * FilePath = "Planes.db") {
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

	bool create(uint64_t id, const char * plane, const char * type, uint64_t flights) {  
		std::cout <<id << strlen(plane) << ' ' << strlen(type);
		
		if ((id > MAX_NUMBER) || (flights > MAX_NUMBER) ||
		    (strlen(plane) >= MAX_TEXT) || (strlen(type) >= MAX_TEXT))
			return false;

		db.push_back(Schema(id, plane, type, flights));

		sorted = false;
		return true;
	}

	bool del(uint64_t id) {
		Schema* plane = search(id);
		if (plane == nullptr)
			return false;
		plane->flights = INVALID_FLIGHTS;
		return true;
	}

	bool update(uint64_t id, const char * type_plane, bool flag) {
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
	
	bool update(uint64_t id, uint64_t id_flights, bool flag) {
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

	void show() const {
		for (const Schema& plane : db)
			std::cout << plane << '\n';
	}

	void optimize() {
		std::sort(db.begin(), db.end(), 
			[] (const Schema& lhs, const Schema& rhs) -> bool {
				return lhs.id < rhs.id;
		    }
		);
		sorted = true;
	}

	Schema* search(uint64_t id) {
		if (id > MAX_NUMBER)
			return nullptr;
		
		if (!sorted) {
			for (Schema& plane : db)
				if (plane.id == id && plane.flights != INVALID_FLIGHTS)
					return &plane;
		} else {
			throw std::exception("Not implemented!");
		}
		return nullptr;
	}

	~Database() { save(); }
};

//COMMANDS
//create, delete, update, show, optimize, search, exit
const std::string	CREATE   = "create",
					DELETE   = "delete",
					UPDATE   = "update",
					SHOW     = "show",
					OPTIMIZE = "optimize",
					SEARCH   = "search",
					EXIT     = "exit";
//ATRIBUTES
//Id, Plane, Type, Flights
const std::string	ID      = "Id",
					PLANE   = "Plane",
					TYPE    = "Type",
					FLIGHTS = "Flights";
int main() {
	Database db;

	std::string command,attribute,type,plane;
	uint64_t id, flights;

	while (true) {
		std::cin >> command;
		if (command == CREATE) {
			std::cin >> id;
			std::cin >> type;
			std::cin >> plane;
			std::cin >> flights;
			bool flag = db.create(id, type.c_str(), plane.c_str(), flights);
			if(!flag) std::cout << "create failed\n";
		}
		else if (command == DELETE) {
			std::cin >> id;
			bool flag = db.del(id);
			if (!flag) std::cout << "delete failed\n";
		}
		else if (command == UPDATE) {
			std::cin >> id;
			std::cin >> attribute;
			if (attribute == ID) {
				uint64_t new_id;
				std::cin >> new_id;
				db.update(id, new_id, true);
			}
			else if (attribute == PLANE) {
				std::cin >> plane;
				db.update(id, plane.c_str(), true);
			}
			else if (attribute == TYPE) {
				std::cin >> type;
				db.update(id, type.c_str(), false);
			}
			else if (attribute == FLIGHTS) {
				std::cin >> flights;
				db.update(id, flights, true);
			}
			else {
				std::cout << "Invalid command!\n";
			}
		}
		else if (command == SHOW) {
			db.show();
		}
		else if (command == OPTIMIZE) {
			db.optimize();
		}
		else if (command == EXIT) {
			break;
		}
		else if (command == SEARCH) {
			std::cin >> id;
			db.search(id);
		}
		else {
			std::cout << "Invalid command!\n";
		}
	}
}
