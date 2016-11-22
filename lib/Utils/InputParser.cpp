#include "Utils/InputParser.h"

InputParser::InputParser(int &argc, char **argv) : argc(argc), failure(false) {
	int pos = 0;
	for (int i = 0; i < argc; i++) {
		std::string member = argv[pos++];
		std::vector<std::string> opt_value = get_opt_and_value(member);
		std::string option = opt_value[0];
		std::string value = opt_value[1];
		is_valid_opt(option) ? failure = true : failure;
		params[option] = generate_parameter(option, value);
	}
}

parameter InputParser::generate_parameter(std::string option, std::string value) {
	type_parameter type = get_type_from_argument(option);
	parameter param;
	param.type = type;
	switch (type) {
		case type_parameter::PATH:
			param.data.path = Path(value);
			break;
		case type_parameter::STRING:
			param.data.str = value;
			break;
		case type_parameter::BOOL:
			param.data.is_active = true;
			break;
		case type_parameter::NUMBER:
			param.data.number = atoi(value.c_str());
			break;
	}
	return param;
}

bool InputParser::cmdOptionExists(std::string option) {
	return std::any_of(params.begin(), params.end(),
				  [&](auto key_value) {
					  return key_value.first == option;
				  });
}

bool InputParser::is_valid_opt(std::string arg) {
	return std::any_of(cmd_entries.begin(), cmd_entries.end(),
					   [&](cmd_entry entry) {
						   return entry.short_arg == arg || entry.long_arg == arg;
					   });
}

std::vector<std::string> InputParser::get_opt_and_value(std::string member) {
	std::vector<std::string> res;
	member.erase(0, 1);
	std::string option;
	std::string param;
	if (member[0] == '-') {
		member.erase(0, 1);
		option = member.substr(0, member.find("="));
		param = member.substr(member.find("=")+1, member.size());
	}
	else {
		option = member[0];
		member.erase(0, 1);
		param = member;
	}
	res = { option, param };
	return res;
}

type_parameter InputParser::get_type_from_argument(std::string arg) {
	auto it = std::find_if(cmd_entries.begin(), cmd_entries.end(),
						   [&](cmd_entry entry) {
							   return entry.short_arg == arg || entry.long_arg == arg;
						   });
	return it->type;
}

bool InputParser::is_failure() {
	return failure;
}