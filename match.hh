#ifndef UTIXX_MATCH_HH_HEADER_GUARD
#define UTIXX_MATCH_HH_HEADER_GUARD

#include <algorithm> // std::find
#include <vector>    // std::vector

#include "utixx.hh"

#define MATCH(VAR, ...) \
	do { \
		const auto &__switched_val = VAR; \
		if (false) {} \
		__VA_ARGS__ \
	} while (0)

#define TO(...) else if (_match_to({__VA_ARGS__}, __switched_val))
#define ELSE    else

namespace utixx {

template <typename T>
bool _match_to(const std::vector<T> &list, const T &val) {
	return std::find(list.begin(), list.end(), val) != list.end();
}

}

#endif
