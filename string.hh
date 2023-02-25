#ifndef UTIXX_STRING_HH_HEADER_GUARD
#define UTIXX_STRING_HH_HEADER_GUARD

#include <string>  // std::string, std::stoll, std::stoi, std::stod
#include <vector>  // std::vector
#include <cstdint> // std::int64_t
#include <cctype>  // std::tolower, std::toupper

#include "utixx.hh"
#include "maybe.hh"

namespace utixx {

namespace string {
	constexpr const char *whitespaces = " \f\n\r\t\v";

	std::vector<std::string> split(const std::string &str, const std::string &delim,
	                               size_t count = std::string::npos) {
		std::vector<std::string> list;
		for (size_t i = 0, pos = 0; i < count and pos < str.length(); ++ i) {
			size_t next = str.find_first_of(delim, pos);
			list.push_back(str.substr(pos, next == std::string::npos? next : next - pos));

			if (next == std::string::npos)
				break;
			else
				pos = next + delim.length();
		}
		return list;
	}

	std::string join(const std::vector<std::string> &list, const std::string &delim = "") {
		std::string str;
		bool        first = true;
		for (const auto &elem : list) {
			if (first)
				first = false;
			else
				str += delim;

			str += elem;
		}
		return str;
	}

	size_t replace(std::string &str, const std::string &to_replace, const std::string &with,
	             size_t count = std::string::npos) {
		size_t i = 0;
		for (size_t pos = 0; i < count and pos < str.length(); ++ i) {
			pos = str.find(to_replace, pos);
			if (pos == std::string::npos)
				return i;

			str.replace(pos, to_replace.length(), with);
			pos += with.length();
		}
		return i;
	}

	inline void trim_right(std::string &str, const std::string &to_trim) {
		str.erase(str.find_last_not_of(to_trim) + 1);
	}

	inline void trim_left(std::string &str, const std::string &to_trim) {
		str.erase(0, str.find_first_not_of(to_trim));
	}

	inline void trim(std::string &str, const std::string &to_trim) {
		trim_right(str, to_trim);
		trim_left( str, to_trim);
	}

	inline void to_lower(std::string &str) {
		for (auto &ch : str)
			ch = std::tolower(ch);
	}

	inline void to_upper(std::string &str) {
		for (auto &ch : str)
			ch = std::toupper(ch);
	}

	auto to_bool(std::string str) {
		to_lower(str);


		if (str == "true" or str == "t" or str == "yes" or str == "y" or str == "on" or str == "1")
			return maybe<bool>(true);
		else if (str == "false" or str == "f"   or str == "no" or
		         str == "n"     or str == "off" or str == "0")
			return maybe<bool>(false);
		else
			return maybe<bool>::none();
	}

	auto to_int(const std::string &str, size_t base = 10) {
		try {
			return maybe<int>(std::stoi(str, nullptr, base));
		} catch (...) {
			return maybe<int>::none();
		}
	}

	auto to_int64(const std::string &str, size_t base = 10) {
		try {
			return maybe<std::int64_t>(static_cast<std::int64_t>(std::stoll(str, nullptr, base)));
		} catch (...) {
			return maybe<std::int64_t>::none();
		}
	}

	auto to_size(const std::string &str, size_t base = 10) {
		try {
			return maybe<std::size_t>(static_cast<std::size_t>(std::stoll(str, nullptr, base)));
		} catch (...) {
			return maybe<std::size_t>::none();
		}
	}

	auto to_float(const std::string &str) {
		try {
			return maybe<double>(std::stod(str));
		} catch (...) {
			return maybe<double>::none();
		}
	}
}

}

#endif
