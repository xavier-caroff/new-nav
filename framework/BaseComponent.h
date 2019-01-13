#pragma once

#include <string>

#include "IComponent.h"

namespace newNav {
namespace framework {

///
/// Base class for components.
///
class BaseComponent:
	public IComponent
{
// Construction, destruction
public:

	/// Constructor.
	BaseComponent(
		const std::string&  name);

	/// Destructor.
	virtual ~BaseComponent(
		);

// Partial implementation of IComponent
public:

	/// Get the current state of the component.
	virtual IComponent::State	getState(
		) const override final;

// Protected operations
protected:

	/// Change the state of the component.
	///
	/// @param value The value to set.
	void	setState(
		IComponent::State	value);

// Private attributes
private:

	/// The current state.
	IComponent::State		_state;
};


/// Create necessary declaration stuff for component registration
#define DECLARE_COMPONENT(className)																			\
public:																											\
																												\
	static const newNav::framework::ComponentRegistry::ComponentDescription&	getDescription(					\
		);																										\
																												\
	static newNav::framework::IComponent*	create(																\
		const std::string&	name);																				\


/// Implement necessary declaration stuff for component registration
#define IMPLEMENT_COMPONENT(className)																			\
																												\
const newNav::framework::ComponentRegistry::ComponentDescription&	className::getDescription(					\
	)																											\
{																												\
	using newNav::framework::ComponentRegistry;																	\
																												\
	static ComponentRegistry::ComponentDescription		description {											\
															boost::core::demangle(typeid(className).name()),	\
															className::create };								\
																												\
	return description;																							\
}																												\
																												\
newNav::framework::IComponent*	className::create(																\
	const std::string&	name)																					\
{																												\
	return new className(name);																					\
}																												\


} // namespace framework
} // namespace newNav
