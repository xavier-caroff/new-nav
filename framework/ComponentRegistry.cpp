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

} // namespace framework
} // namespace newNav
