#pragma once

#include "IComponent.h"

namespace newNav {
namespace framework {

///
/// Interface of a component manager.
///
class IComponentManager
{
// Operations
public:

	/// Create a component from its class name.
	///
	/// @param name Name of the component.
	/// @param className Class name of the component.
	///
	/// @return Pointer on the component.
	///
	/// @throw std::runtime_error when another existing component has the same name.
	/// @throw std::runtime_error when no component description registered with this class name.
	virtual IComponent*	create(
		const std::string&	name,
		const std::string&	className) = 0;

	/// Find a component from its name.
	///
	/// @return Pointer on the component, nullptr if no component.
	virtual IComponent*	find(
		const std::string&	name) const = 0;
};

} // namespace framework
} // namespace newNav
