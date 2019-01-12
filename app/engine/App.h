#pragma once

#include <list>
#include <boost/dll.hpp>

namespace newNav {
namespace app {
namespace engine {

///
/// Application class for engine.
///
class App
{
// Construction, destruction
public:

	/// Constructor.
	App(
		);

	/// Destructor.
	virtual ~App(
		);

// Operation
public:

	/// Launch the application.
	int execute(
		int		argc,
		char*	argv[]);

// Implementation
private:

	/// Load the external modules.
	void	loadModules(
		);

// Private attributes
private:

	std::list<boost::dll::shared_library>	_modules;
};

} // namespace engine
} // namespace app
} // namespace newNav
