#include "BaseComponent.h"

namespace newNav {
namespace framework {

// Constructor.
BaseComponent::BaseComponent(
	const std::string&  name)
	: _state{ IComponent::State::created }
{
}

// Destructor.
BaseComponent::~BaseComponent(
	)
{
}

// Get the current state of the component.
IComponent::State	BaseComponent::getState(
	) const
{
	return _state;
}

// Change the state of the component.
void	BaseComponent::setState(
	IComponent::State	value)
{
	_state = value;
}

} // namespace framework
} // namespace newNav
