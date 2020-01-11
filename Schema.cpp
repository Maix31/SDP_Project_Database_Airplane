#include "Schema.h"

Schema::Schema() {}

Schema::Schema(uint64_t id, const char* plane, const char* type, uint64_t flights)
	: id(id)
	, flights(flights) {
	strcpy_s(this->plane, plane);
	strcpy_s(this->type, type);
}
