#include "TcpServer.h"

namespace newNav {
namespace module {
namespace io {

IMPLEMENT_COMPONENT(TcpServer)

// Constructor.
TcpServer::TcpServer(
	const std::string&						name,
	newNav::framework::IComponentManager*	manager)
	: newNav::framework::BaseComponent{ name, manager }
{
}

// Destructor.
TcpServer::~TcpServer(
	)
{
}

// Configure the component.
void    TcpServer::configure(
	)
{
}

// Start the execution of the component.
void    TcpServer::run(
	)
{
}

// Stop the execution of the component.
void	TcpServer::halt(
	)
{
}

} // namespace io
} // namespace module
} // namespace newNav
