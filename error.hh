#ifndef UTIXX_ERROR_HH_HEADER_GUARD
#define UTIXX_ERROR_HH_HEADER_GUARD

#include <cstdlib> // std::exit, EXIT_FAILURE, std::size_t
#include <sstream> // std::stringstream
#include <string>  // std::string

#include "utixx.hh"

#define UNREACHABLE() \
	utixx::panic(__FILE__, ":", __LINE__, ": Unreachable")

#define TODO(...) \
	utixx::panic(__FILE__, ":", __LINE__, " TODO: ", __VA_ARGS__)

#define FUNC_FAIL(FUNC, ...) \
	utixx::panic(__FILE__, ":", __LINE__, ": ", FUNC, "() fail: ", __VA_ARGS__)

namespace utixx {

template<typename... args>
void panic(args... a) {
	std::cerr << "panic(): ";
	((std::cerr << a), ...);
	std::cerr << std::endl;

	std::exit(EXIT_FAILURE);
}

class error {
public:
	static inline auto none() {
		return error();
	}

	template<typename... args>
	static inline auto make(args... a) {
		std::stringstream ss;
		((ss << a), ...);
		return error(ss.str());
	}

	const std::string &what() const {return msg;}

	bool ok() const {return not err;}

private:
	error():                       err(false), msg("")  {}
	error(const std::string &msg): err(true),  msg(msg) {}

	bool        err;
	std::string msg;
};

inline void panic(const error &err) {
	panic(err.what());
}

template<typename T>
class error_or {
public:
	error_or(const error &err): err(err) {}
	error_or(const T     &val): err(error::none()), val(val) {}

	const error &get_error() {return err;}

	T       &get_value()       {return val;}
	const T &get_value() const {return val;}

private:
	error err;
	T     val;
};

}

#endif
