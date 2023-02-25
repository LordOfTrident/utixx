#include <iostream>

#include <format.hh>

using namespace utixx;

int main() {
	std::cout << fmt("Hello, %v!", "world") << std::endl;

	return 0;
}
