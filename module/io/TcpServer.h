#pragma once

#include <string>

#include "BaseComponent.h"
#include "ComponentRegistry.h"

namespace newNav {
namespace module {
namespace io {

///
/// Tcp server component
///
class TcpServer:
	public newNav::framework::BaseComponent
{
	DECLARE_COMPONENT(TcpServer)

// Construction, destruction
private:

	/// Constructor.
	///
	/// @param name Name of the component.
	/// @param manager Pointer to the component manager.
	TcpServer(
		const std::string&						name,
		newNav::framework::IComponentManager*	manager);

	/// Destructor.
	virtual ~TcpServer(
		);

// Partial implementation of IComponent
public:

	/// Configure the component.
	virtual void    configure(
		) override final;

	/// Start the execution of the component.
	virtual void    run(
		) override final;

	/// Stop the execution of the component.
	virtual void	halt(
		) override final;
};

} // namespace io
} // namespace module
} // namespace newNav
