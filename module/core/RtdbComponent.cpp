#include "RtdbComponent.h"

namespace newNav {
namespace module {
namespace core {

IMPLEMENT_COMPONENT(RtdbComponent)

// Constructor.
RtdbComponent::RtdbComponent(
	const std::string&							name,
	newNav::framework::comp::IComponentManager*	manager)
	: newNav::framework::comp::BaseComponent{ name, manager }
{
}

// Destructor.
RtdbComponent::~RtdbComponent(
	)
{
}

// Configure the component.
void    RtdbComponent::configure(
	const newNav::framework::comp::IComponent::ConfigData&	config)
{
	setState(IComponent::State::initialized);
}

// Start the execution of the component.
void    RtdbComponent::run(
	)
{
	setState(IComponent::State::running);
}

// Stop the execution of the component.
void	RtdbComponent::halt(
	)
{
	setState(IComponent::State::halted);
}

} // namespace core
} // namespace module
} // namespace newNav
