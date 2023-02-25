#ifndef UTIXX_FORMAT_HH_HEADER_GUARD
#define UTIXX_FORMAT_HH_HEADER_GUARD

#include <sstream> // std::stringstream
#include <string>  // std::string
#include <cstring> // std::strlen

#include "utixx.hh"
#include "error.hh"

namespace utixx {

#define _FMT_SEQ "%v"

template<typename... args>
std::string fmt(std::string fmt, args... a) {
	std::stringstream ss;

	([&] {
		auto start = fmt.find(_FMT_SEQ);
		if (start == std::string::npos)
			FUNC_FAIL(__func__, "missing format in format string");

		if (start > 0) {
			if (fmt[start - 1] == '%')
				return;
		}

		ss << fmt.substr(0, start);
		ss << a;

		fmt = fmt.substr(start + std::strlen(_FMT_SEQ));
	} (), ...);

	ss << fmt;

	return ss.str();
}

template<typename T>
std::string operator %(const std::string &p_fmt, T &p_val) {
	return fmt(p_fmt, p_val);
}

}

#endif
