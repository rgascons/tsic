#ifndef __TSIC_UTILS_INPUTPARSER__
#define __TSIC_UTILS_INPUTPARSER__

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "Utils/Path.h"

enum class type_parameter {
	PATH,
	STRING,
	NUMBER,
	BOOL,
};

struct cmd_entry {
	std::string long_arg;
	std::string short_arg;
	type_parameter type;
	std::string name;
};

struct parameter {
	type_parameter type;
	struct {
		Path path;
		std::string str;
		int number;
		bool is_active;
	} data;
};

std::vector<cmd_entry> cmd_entries = {
		{.long_arg = "output", .short_arg = "o", .type = type_parameter::PATH, .name = "Output"},
};

class InputParser {
private:
	int argc;
	std::unordered_map<std::string, parameter> params;
	bool failure;

	bool is_valid_opt(std::string);
	type_parameter get_type_from_argument(std::string arg);
	parameter generate_parameter(std::string option, std::string value);

public:
	InputParser(int &argc, char **argv);

	bool cmdOptionExists(std::string option);
	bool is_failure();
	std::vector<std::string> get_opt_and_value(std::string member);

	void init_list_cmd_entries();
};

#endif