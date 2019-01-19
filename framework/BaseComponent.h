#pragma once

#include <string>

#include "IComponent.h"
#include "IComponentManager.h"
#include "Demangle.h"

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
	///
	/// @param name Name of the component.
	/// @param manager Pointer to the component manager.
	BaseComponent(
		const std::string&  name,
		IComponentManager*	manager);

	/// Destructor.
	virtual ~BaseComponent(
		);

// Partial implementation of IComponent
public:

	/// Get the current state of the component.
	virtual IComponent::State	state(
		) const override final;

	/// Get the name of the component.
	virtual const std::string&	name(
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

	/// The name of the component.
	std::string				_name;

	/// Pointer to the component manager.
	IComponentManager*		_manager;
};


/// Create necessary declaration stuff for component registration
#define DECLARE_COMPONENT(className)																			\
public:																											\
																												\
	static const newNav::framework::ComponentRegistry::ComponentDescription&	getDescription(					\
		);																										\
																												\
	static newNav::framework::IComponent*	create(																\
		const std::string&						name,															\
		newNav::framework::IComponentManager*	manager);														\


/// Implement necessary declaration stuff for component registration
#define IMPLEMENT_COMPONENT(className)																			\
																												\
const newNav::framework::ComponentRegistry::ComponentDescription&	className::getDescription(					\
	)																											\
{																												\
	using newNav::framework::ComponentRegistry;																	\
																												\
	static ComponentRegistry::ComponentDescription		description {											\
															demangle(typeid(className).name()),					\
															className::create };								\
																												\
	return description;																							\
}																												\
																												\
newNav::framework::IComponent*	className::create(																\
	const std::string&						name,																\
	newNav::framework::IComponentManager*	manager)															\
{																												\
	return new className(name, manager);																		\
}																												\

} // namespace framework
} // namespace newNav
