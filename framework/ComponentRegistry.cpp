#include <stdexcept>

#include "ComponentRegistry.h"

namespace newNav {
namespace framework {

// Constructor.
ComponentRegistry::ComponentRegistry(
	)
{
}

// Destructor.
ComponentRegistry::~ComponentRegistry(
	)
{
}

// Add a new component description to the registry.
void	ComponentRegistry::registerDescription(
	const ComponentDescription&	description)
{
	if (_descriptions.find(description._className) == _descriptions.end())
	{
		_descriptions.emplace(description._className, description);
	}
}

// Find the description from a class name.
const ComponentRegistry::ComponentDescription&	ComponentRegistry::find(
	const std::string&	className) const
{
	auto	itr = _descriptions.find(className);

	if (itr == _descriptions.end())
	{
		throw std::runtime_error("no component description registered with this class name");
	}

	return itr->second;
}

} // namespace framework
} // namespace newNav
