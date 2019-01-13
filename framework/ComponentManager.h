#pragma once

#include <string>
#include <map>
#include <memory>

#include "IComponentManager.h"
#include "ComponentRegistry.h"

namespace newNav {
namespace framework {

///
/// The component manager manage components.
///
class ComponentManager:
	public IComponentManager
{
// Construction, destruction
public:

	/// Constructor.
	///
	/// @param registry The registry of component classes.
	ComponentManager(
		const ComponentRegistry&	registry);

	/// Destructor.
	virtual ~ComponentManager(
		);

// Implementation of IComponentManager
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
		const std::string&	className) override final;

	/// Find a component from its name.const ComponentRegistry&						_registry
	///
	/// @return Pointer on the component, nullptr if no component.
	virtual IComponent*	find(
		const std::string&	name) const override final;

// Private attributes
private:

	/// The registry of component classes.
	const ComponentRegistry&						_registry;

	/// The collection of components owned by this manager.
	std::map<
		std::string, std::unique_ptr<IComponent>>	_components;	
};

} // namespace framework
} // namespace newNav
