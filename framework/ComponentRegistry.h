#pragma once

#include <string>
#include <map>
#include <type_traits>

#include "IComponent.h"

namespace newNav {
namespace framework {

///
/// Register the description of components classes and
/// provide services to create components.
///
class ComponentRegistry
{
// Definition
public:

	/// Defintion of the signature of the function to create a component.
	using	CreateFunction = std::add_pointer<IComponent* (const std::string&)>::type;

	///
	/// Description of a component class.
	///
	struct ComponentDescription
	{
		/// Name of the class.
		std::string		_className;

		/// Creation function.
		CreateFunction	_create;

		/// Constructor with initialization.
		///
		/// @param
		ComponentDescription(
			const std::string&	className,
			CreateFunction		create)
				: _className{ className },
				  _create{ create } { }

		/// Copy constructor
		ComponentDescription(
			const ComponentDescription&	other) = default;

		/// Move constructor
		ComponentDescription(
			ComponentDescription&&	other) = default;

		/// Copy operator
		ComponentDescription&	operator=(
			const ComponentDescription&	other) = default;

		/// Move operator
		ComponentDescription&	operator=(
			ComponentDescription&&	other) = default;
	};

// Construction, destruction
public:

	/// Constructor.
	ComponentRegistry(
		);

	/// Destructor.
	virtual ~ComponentRegistry(
		);

// Operations
public:

	/// Add a new component description to the registry.
	///
	/// @param description Description of the component.
	void	registerDescription(
		const ComponentDescription&	description);

// Private attributes
private:

	std::map<
		std::string, ComponentDescription>		_descriptions;
};

} // namespace framework
} // namespace newNav
