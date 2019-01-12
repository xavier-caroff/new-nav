#include <iostream>
#include <boost/filesystem.hpp>

#include "App.h"

namespace newNav {
namespace app {
namespace engine {

// Constructor.
App::App(
	)
{
}

// Destructor.
App::~App(
	)
{
}

// Launch the application
int App::execute(
	int		argc,
	char*	argv[])
{
    loadModules();

	return 0;
}

// Load the external modules.
void	App::loadModules(
	)
{
	boost::filesystem::path		exe = boost::dll::program_location();
	boost::filesystem::path		folder = exe.parent_path();

	folder /= "../lib";

	for(const auto& current : boost::filesystem::directory_iterator(folder))
	{
		if (current.path().extension() == boost::filesystem::path{ ".so" } ||
		    current.path().extension() == boost::filesystem::path{ ".dll" } ||
		    current.path().extension() == boost::filesystem::path{ ".dylib" } )
		{
			try
			{
				boost::dll::shared_library	lib(current.path());
				auto						registerComponents = lib.get<void()>("registerComponents");

				registerComponents();

				_modules.push_back(std::move(lib));
			}
			catch(boost::system::system_error&	e)
			{
				// can't find the entry point.
			}
		}
	}
}

} // namespace engine
} // namespace app
} // namespace newNav
