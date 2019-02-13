#pragma once

#include <string>

#include "IComponent.h"
#include "IComponentManager.h"
#include "lang/Demangle.h"

namespace newNav {
namespace framework {
namespace comp {

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
	///
	/// @return The current state of the component.
	virtual IComponent::State	state(
		) const override final;

	/// Get the name of the component.
	///
	/// @return The name of the component.
	virtual const std::string&	name(
		) const override final;

// Protected operations
protected:

	/// Change the state of the component.
	///
	/// @param value The value to set.
	void	setState(
		IComponent::State	value);

	/// Access to the component manager.
	///
	/// @return Pointer to the component manager.
	IComponentManager*	manager(
		) const;

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
	static const newNav::framework::comp::ComponentRegistry::ComponentDescription&	getDescription(				\
		);																										\
																												\
	static newNav::framework::comp::IComponent*	create(															\
		const std::string&							name,														\
		newNav::framework::comp::IComponentManager*	manager);													\


/// Implement necessary declaration stuff for component registration
#define IMPLEMENT_COMPONENT(className)																			\
																												\
const newNav::framework::comp::ComponentRegistry::ComponentDescription&	className::getDescription(				\
	)																											\
{																												\
	using newNav::framework::comp::ComponentRegistry;															\
	using newNav::framework::lang::demangle;																	\
																												\
	static ComponentRegistry::ComponentDescription		description {											\
															demangle(typeid(className).name()),					\
															className::create };								\
																												\
	return description;																							\
}																												\
																												\
newNav::framework::comp::IComponent*	className::create(														\
	const std::string&						name,																\
	newNav::framework::comp::IComponentManager*	manager)														\
{																												\
	return new className(name, manager);																		\
}																												\

} // namespace comp
} // namespace framework
} // namespace newNav
