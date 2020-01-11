#pragma once

#include <iostream>

const char* FILE_PATH = "Planes.db";

const uint64_t INVALID_FLIGHTS = UINT64_MAX;

const uint64_t MAX_NUMBER = (1ULL << 50);
const uint64_t MAX_TEXT = (1ULL << 8);

//COMMANDS
//create, delete, update, show, optimize, search, exit
const std::string	CREATE = "create",
DELETE = "delete",
UPDATE = "update",
SHOW = "show",
OPTIMIZE = "optimize",
SEARCH = "search",
EXIT = "exit",
HELP = "help";

//ATRIBUTES
//Id, Plane, Type, Flights
const std::string	ID = "Id",
PLANE = "Plane",
TYPE = "Type",
FLIGHTS = "Flights";