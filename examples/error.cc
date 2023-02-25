#include <iostream>

#include <error.hh>
#include <format.hh>

using namespace utixx;

auto idiv(int a, int b) {
	if (b == 0)
		return error_or<int>(error::make("Division by 0"));

	return error_or<int>(a / b);
}

int main() {
	int a = 5, b = 0;

	auto res = idiv(a, b);
	if (not res.get_error().ok())
		panic(res.get_error());

	std::cout << fmt("%v / %v = %v", a, b, res.get_value()) << std::endl;

	return 0;
}
