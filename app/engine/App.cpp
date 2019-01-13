#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

#include "App.h"

namespace newNav {
namespace app {
namespace engine {

// Constructor.
App::App(
	)
	: _registry{ },
	  _manager{ _registry }
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
	int		result{ 0 };

	// Load the configuration file.

	if (result == 0)
	{
		std::ifstream	file("/home/xca/DEV/new-nav/my-config.json");

		file >> _config;
	}

	// Load the modules located into the executable folder and additional folder
	// provided into the configuration.

	if (result == 0)
	{
		loadModules();
	}

	// Create the components.

	if (result == 0)
	{
		if (createComponents() == false)
		{
			result = 1;
		}
	}

	// Configure the components.

	if (result == 0)
	{
		configureComponents();
	}

	return result;
}

// Load all possible modules.
void	App::loadModules(
	)
{
	boost::filesystem::path		exe = boost::dll::program_location();
	boost::filesystem::path		exeFolder = exe.parent_path();

	loadModules(exeFolder);

	if (_config.find("additionalPackageFolders") != _config.end())
	{
		for(const auto& current : _config["additionalPackageFolders"])
		{
			if (current.is_string())
			{
				boost::filesystem::path		path{ current.get<std::string>() };

				if (path.is_relative())
				{
					path = exeFolder / path;
				}

				loadModules(path);
			}
		}
	}
}

// Load the external modules located into a given folder.
void	App::loadModules(
	const boost::filesystem::path&	folder)
{
	for(const auto& current : boost::filesystem::directory_iterator(folder))
	{
		if (current.path().extension() == boost::filesystem::path{ ".so" } ||
		    current.path().extension() == boost::filesystem::path{ ".dll" } ||
		    current.path().extension() == boost::filesystem::path{ ".dylib" } )
		{
			try
			{
				boost::dll::shared_library	lib(current.path());
				auto						registerComponents = lib.get<void(newNav::framework::ComponentRegistry&)>("registerComponents");

				registerComponents(_registry);

				_modules.push_back(std::move(lib));
			}
			catch(boost::system::system_error&	e)
			{
				// can't find the entry point.
			}
		}
	}
}

// Create the components described into the configuration file.
bool	App::createComponents(
	)
{
	bool	result { true };

	for(const auto& current : _config["components"])
	{
		std::string		name = current["name"].get<std::string>();
		std::string		className = current["className"].get<std::string>();

		try
		{
			_manager.create(name, className);
		}
		catch(std::runtime_error&	e)
		{
			std::cerr << "failed to create component " << name << " of class " << className << ": " << e.what() << std::endl;
			result = false;
		}
	}

	return result;
}

// Configure each component.
void	App::configureComponents(
	)
{
	for(const auto& current : _config["components"])
	{
		std::string		name = current["name"].get<std::string>();
		nlohmann::json	empty;
		nlohmann::json&	config{ empty };

		if (current.find("config") != current.end())
		{
			config = current["config"];
		}

		try
		{
			_manager.find(name)->configure(config);
		}
		catch(std::exception&	e)
		{
			std::cerr << "failed to configure component " << name << ": " << e.what() << std::endl;
		}
	}
}

} // namespace engine
} // namespace app
} // namespace newNav
