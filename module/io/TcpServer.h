#pragma once

#include <string>

namespace newNav {
namespace module {
namespace io {

///
/// Tcp server component
///
class TcpServer
{
// Construction, destruction
public:

	/// Constructor.
	TcpServer(
		const std::string&  name);

	/// Destructor.
	virtual ~TcpServer(
		);
};

} // namespace io
} // namespace module
} // namespace newNav
