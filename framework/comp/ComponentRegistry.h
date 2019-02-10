#pragma once

#include <string>
#include <map>
#include <type_traits>

#include "IComponent.h"
#include "IComponentManager.h"

namespace newNav {
namespace framework {
namespace comp {

///
/// Register the description of components classes and
/// provide services to create components.
///
class ComponentRegistry
{
// Definition
public:

	/// The name of the entry point function.
	static const char constexpr*		ENTRY_POINT_FUNCTION{ "registerComponents" };

	/// Defintion of the signature of the function to create a component.
	using	CreateFunction = std::add_pointer<IComponent* (const std::string&, IComponentManager*)>::type;

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
		/// @param className Class name of the component (including namespaces).
		/// @param create Pointer to the function thzt create the component.
		ComponentDescription(
			const std::string&	className,
			CreateFunction		create)
				: _className{ className },
				  _create{ create } { }

		/// @cond
		ComponentDescription(
			const ComponentDescription&	other) = default;

		ComponentDescription(
			ComponentDescription&&	other) = default;

		ComponentDescription&	operator=(
			const ComponentDescription&	other) = default;

		ComponentDescription&	operator=(
			ComponentDescription&&	other) = default;
		/// @endcond
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

	/// Find the description from a class name.
	///
	/// @param className Class name.
	///
	/// @return Reference to the description.
	///
	/// @throw std::runtime_error When no component description registered with this class name.
	const ComponentRegistry::ComponentDescription&	find(
		const std::string&	className) const;

// Private attributes
private:

	/// Collection of the registered component's descriptions.
	std::map<
		std::string, ComponentDescription>		_descriptions;
};

} // namespace comp
} // namespace framework
} // namespace newNav
