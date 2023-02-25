#include <iostream>
#include <cstdlib> // EXIT_FAILURE, EXIT_SUCCESS;

#include <match.hh>
#include <format.hh>

using namespace utixx;

int main(int argc, const char **argv) {
	if (argc != 2) {
		std::cerr << fmt("Usage: %v tree/bowl/table/desk", argv[0]) << std::endl;
		return EXIT_FAILURE;
	}

	// You could simply use if else here, but when theres a lot of things to match, it will
	// get very long
	MATCH(std::string(argv[1]),
		TO("tree") {
			std::cout << " ^\n"
			          << "/ \\\n"
			          << "/ \\\n"
			          << " M" << std::endl;
		}

		TO("bowl") std::cout << "\\_/" << std::endl;

		TO("table", "desk") {
			std::cout << "------\n"
			          << "|    |" << std::endl;
		}

		ELSE {
			std::cout << fmt("Invalid option '%v'\n", argv[1])
			          << "Pick one of these: tree, bowl, table" << std::endl;
			return EXIT_FAILURE;
		}
	);

	return EXIT_SUCCESS;
}
