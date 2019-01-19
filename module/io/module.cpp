#include <boost/dll.hpp>

#include "ComponentRegistry.h"
#include "TcpServer.h"

#define API extern "C" BOOST_SYMBOL_EXPORT

/// Module entry point.
///
/// @param registry The registry to store the components published by the
/// module.
API void	registerComponents(
	newNav::framework::ComponentRegistry&	registry)
{
	registry.registerDescription(newNav::module::io::TcpServer::getDescription());
}