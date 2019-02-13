#include "BaseComponent.h"

namespace newNav {
namespace framework {
namespace comp {

// Constructor.
BaseComponent::BaseComponent(
	const std::string&  name,
	IComponentManager*	manager)
	: _state{ IComponent::State::created },
	  _name{ name },
	  _manager{ manager }
{
}

// Destructor.
BaseComponent::~BaseComponent(
	)
{
}

// Get the current state of the component.
IComponent::State	BaseComponent::state(
	) const
{
	return _state;
}

// Get the name of the component.
const std::string&	BaseComponent::name(
	) const
{
	return _name;
}

// Change the state of the component.
void	BaseComponent::setState(
	IComponent::State	value)
{
	_state = value;
}

// Access to the component manager.
IComponentManager*	BaseComponent::manager(
	) const
{
	return _manager;
}

} // namespace comp
} // namespace framework
} // namespace newNav
