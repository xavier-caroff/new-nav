#pragma once

#include <string>
#include <boost/core/demangle.hpp>

#include "comp/BaseComponent.h"
#include "comp/ComponentRegistry.h"

namespace newNav {
namespace module {
namespace core {

///
/// Real-time database component
///
class RtdbComponent:
	public newNav::framework::comp::BaseComponent
{
	DECLARE_COMPONENT(RtdbComponent)

// Construction, destruction
private:

	/// Constructor.
	///
	/// @param name Name of the component.
	/// @param manager Pointer to the component manager.
	RtdbComponent(
		const std::string&							name,
		newNav::framework::comp::IComponentManager*	manager);

	/// Destructor.
	virtual ~RtdbComponent(
		);

// Partial implementation of IComponent
public:

	/// Configure the component.
	///
	/// @param config The configuration data.
	virtual void    configure(
		const newNav::framework::comp::IComponent::ConfigData&	config) override final;

	/// Start the execution of the component.
	virtual void    run(
		) override final;

	/// Stop the execution of the component.
	virtual void	halt(
		) override final;
};

} // namespace core
} // namespace module
} // namespace newNav
