#pragma once

#include <boost/core/demangle.hpp>
#include <boost/algorithm/string/predicate.hpp>

/// Demangle the name of a symbol.
///
/// @param name Name of the symbol to demangle.
///
/// @return Human readable name of the symbol.
inline
std::string demangle(
    const char*     name)
{
	std::string     demangled{ boost::core::demangle(name) };

	// Handle MSVC prefix

	if (boost::algorithm::starts_with(demangled, "class "))			demangled = demangled.substr(6);
	else if (boost::algorithm::starts_with(demangled, "struct "))	demangled = demangled.substr(7);

	return demangled;
}
