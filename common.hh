#ifndef UTIXX_COMMON_HH_HEADER_GUARD
#define UTIXX_COMMON_HH_HEADER_GUARD

#define UNUSED(VAR) (void)VAR

#include "utixx.hh"

namespace utixx {

inline const char *shift_args(int &argc, const char **&argv) {
	if (argc == 0)
		return nullptr;

	const char *arg = *argv;
	-- argc;
	++ argv;
	return arg;
}

}

#endif
