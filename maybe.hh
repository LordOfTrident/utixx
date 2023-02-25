#ifndef UTIXX_MAYBE_HH_HEADER_GUARD
#define UTIXX_MAYBE_HH_HEADER_GUARD

#include <ostream>   // std::ostream

#include "utixx.hh"
#include "error.hh"

namespace utixx {

template<typename T>
class maybe {
public:
	static inline auto none() {
		return maybe();
	}

	maybe():             has_val(false) {}
	maybe(const T &val): has_val(true), val(val) {}
	maybe(T &&val):      has_val(true), val(val) {}

	void erase() {has_val = false;}

	bool has_value() const {return has_val;}

	T &unwrap() {
		if (not has_val)
			FUNC_FAIL(__func__, "value is none");

		return val;
	}

	const T &unwrap() const {
		if (not has_val)
			FUNC_FAIL(__func__, "value is none");

		return val;
	}

	bool operator ==(const maybe &m) const {return has_val? val == m.val : has_val == m.has_val;}
	bool operator !=(const maybe &m) const {return not (*this == m);}

	bool operator ==(const T &val) {
		if (not has_val)
			return false;

		return this->val == val;
	}

	bool operator !=(const T &val) {return not (*this == val);}

	template<typename... args>
	T &unwrap_or_panic(args... a) {
		if (not has_val)
			panic(a...);

		return val;
	}

	template<typename... args>
	const T &unwrap_or_panic(args... a) const {
		if (not has_val)
			panic(a...);
		else
			return val;
	}

	friend std::ostream &operator <<(std::ostream &stream, const maybe &m) {
		if (m.has_val)
			stream << m.val;
		else
			stream << "(none)";

		return stream;
	}

private:
	bool has_val;
	T    val;
};

}

#endif
