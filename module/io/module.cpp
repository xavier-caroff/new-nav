#include <boost/dll.hpp>

#include "comp/ComponentRegistry.h"
#include "DataBufferDisplay.h"
#include "SerialReader.h"
#include "TcpServer.h"

#define API extern "C" BOOST_SYMBOL_EXPORT

/// Module entry point.
///
/// @param registry The registry to store the components published by the
/// module.
API void	registerComponents(
	newNav::framework::comp::ComponentRegistry&	registry)
{
	registry.registerDescription(newNav::module::io::DataBufferDisplay::getDescription());
	registry.registerDescription(newNav::module::io::SerialReader::getDescription());
	registry.registerDescription(newNav::module::io::TcpServer::getDescription());
}
