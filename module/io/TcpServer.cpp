#include "TcpServer.h"

namespace newNav {
namespace module {
namespace io {

IMPLEMENT_COMPONENT(TcpServer)

// Constructor.
TcpServer::TcpServer(
	const std::string&						name,
	newNav::framework::comp::IComponentManager*	manager)
	: newNav::framework::comp::BaseComponent{ name, manager }
{
}

// Destructor.
TcpServer::~TcpServer(
	)
{
}

// Configure the component.
void    TcpServer::configure(
	const newNav::framework::comp::IComponent::ConfigData&	config)
{
	setState(IComponent::State::initialized);
}

// Start the execution of the component.
void    TcpServer::run(
	)
{
	setState(IComponent::State::running);
}

// Stop the execution of the component.
void	TcpServer::halt(
	)
{
	setState(IComponent::State::halted);
}

} // namespace io
} // namespace module
} // namespace newNav
