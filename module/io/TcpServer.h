#pragma once

#include <string>
#include <boost/core/demangle.hpp>

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
	TcpServer(
		const std::string&  name);

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
