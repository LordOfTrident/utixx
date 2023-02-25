#include <iostream>
#include <vector>

#include <error.hh>
#include <string.hh>
#include <format.hh>

using namespace utixx;

auto parse_int_list(const std::string &str) {
	auto list = string::split(str, ",");

	std::vector<int> parsed;
	size_t idx = 0;
	for (auto &elem : list) {
		string::trim(elem, string::whitespaces);

		auto res = string::to_int(elem);
		if (not res.has_value())
			return error_or<std::vector<int>>(error::make("Element '", elem, "' (#", idx,
			                                              ") is not an integer"));

		parsed.push_back(res.unwrap());
		++ idx;
	}

	return error_or(parsed);
}

int main() {
	std::string list = "5, 128, 45, 1024, error!, 56";

	// Comment this for an error
	string::replace(list, "error!", "33");

	auto res = parse_int_list(list);
	if (not res.get_error().ok())
		panic(res.get_error());

	std::cout << "Parsed list:\n";
	for (const auto &elem : res.get_value())
		std::cout << elem << std::endl;

	return 0;
}
