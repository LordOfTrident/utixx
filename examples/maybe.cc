#include <iostream>
#include <cstdlib> // EXIT_FAILURE, EXIT_SUCCESS
#include <cstring> // strcmp

#include <error.hh>
#include <format.hh>
#include <maybe.hh>

using namespace utixx;

// This function is already implemented in utixx string.hh
auto to_bool(const char *str) {
	if (strcmp(str, "true") == 0)
		return maybe<bool>(true);
	else if (strcmp(str, "false") == 0)
		return maybe<bool>(false);
	else
		return maybe<bool>::none();
}

int main(int argc, const char **argv) {
	if (argc != 2) {
		std::cout << fmt("Usage: %v true/false", argv[0]) << std::endl;
		return EXIT_FAILURE;
	}

	auto res = to_bool(argv[1]);
	std::cout << fmt("argv[1] == %v", res.unwrap_or_panic("Expected true/false")) << std::endl;
	// same as
	//     if (not res.has_value())
	//         panic("Expected true/false");
	//     else
	//         std::cout << fmt("argv[1] == %v", res.unwrap()) << std::endl;

	return EXIT_SUCCESS;
}
