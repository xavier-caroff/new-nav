#include <stdexcept>

#include "ComponentManager.h"

namespace newNav {
namespace framework {

// Constructor.
ComponentManager::ComponentManager(
	const ComponentRegistry&	registry)
	: _registry{ registry }
{
}

// Destructor.
ComponentManager::~ComponentManager(
	)
{
}

// Create a component from its class name.
IComponent*	ComponentManager::create(
	const std::string&	name,
	const std::string&	className)
{
	// Check if name is not already used.

	if (_components.find(name) != _components.end())
	{
		throw std::runtime_error("another existing component has the same name");
	}

	// Find the description.

	const ComponentRegistry::ComponentDescription&	description = _registry.find(className);
	IComponent*										component = description._create(name, this);

	_components.emplace(name, component);

	return component;
}

// Find a component from its name.
IComponent*	ComponentManager::find(
	const std::string&	name) const
{
}

} // namespace framework
} // namespace newNav
