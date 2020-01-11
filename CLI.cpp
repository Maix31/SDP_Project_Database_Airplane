#include "CLI.h"

void help() {
	std::cout
		<< "Commands:\n"
		<< "\tcreate Id Plane Type Flights\n"
		<< "\tdelete Id \n"
		<< "\tupdate Id attribute(Id or Plane or Type or Flights) \n"
		<< "\tshow offset limit\n"
		<< "\toptimize \n"
		<< "\tsearch Id \n"
		<< "\texit\n";
}

void CLI::run() {
	Database db;

	help();

	std::string command, attribute, type, plane;
	uint64_t id, flights;
	unsigned offset, limit;

	while (true) {
		std::cin >> command;
		if (command == CREATE) {
			std::cin >> id;
			std::cin >> type;
			std::cin >> plane;
			std::cin >> flights;
			bool flag = db.create(id, type.c_str(), plane.c_str(), flights);
			if (!flag) std::cout << "create failed\n";
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
			std::cin >> offset >> limit;
			db.show(offset, limit);
		}
		else if (command == OPTIMIZE) {
			db.optimize();
		}
		else if (command == EXIT) {
			break;
		}
		else if (command == SEARCH) {
			std::cin >> id;
			Schema* plane = db.search(id);
			if (plane != nullptr)
				std::cout << *plane << '\n';
			else
				std::cout << "No such plane!\n";
		}
		else if (command == HELP) {
			help();
		}
		else {
			std::cout << "Invalid command!\n";
		}
	}
}