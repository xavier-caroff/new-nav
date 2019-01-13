#include "RtdbComponent.h"

namespace newNav {
namespace module {
namespace core {

IMPLEMENT_COMPONENT(RtdbComponent)

// Constructor.
RtdbComponent::RtdbComponent(
	const std::string&						name,
	newNav::framework::IComponentManager*	manager)
	: newNav::framework::BaseComponent{ name, manager }
{
}

// Destructor.
RtdbComponent::~RtdbComponent(
	)
{
}

// Configure the component.
void    RtdbComponent::configure(
	)
{
}

// Start the execution of the component.
void    RtdbComponent::run(
	)
{
}

// Stop the execution of the component.
void	RtdbComponent::halt(
	)
{
}

} // namespace core
} // namespace module
} // namespace newNav
