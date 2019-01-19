#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "App.h"

namespace bpo = boost::program_options;

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
	int					result{ 0 };
	CommandLineOptions	options;
	bool				startEngine = true;

	// Read command line options.

	if (result == 0)
	{
		try
		{
			parseCmdLine(argc, argv, options);
		}
		catch(std::exception&	e)
		{
			std::cerr << "command line error: " << e.what() << std::endl;
			result = 1;
		}
	}

	// Show help eventually.

	if (result == 0 && options.printHelp)
	{
		// Help message already displayed by parseCmdLine().
		startEngine = false;
	}

	// Start the engine

	if (result == 0 && startEngine)
	{
		start(options);
	}

	return result;
}

// Parse the options from the command line.
void	App::parseCmdLine(
	int					argc,
	char*				argv[],
	CommandLineOptions&	options)
{
	// Description of general options

	bpo::options_description	general("General options");

	general.add_options()
		("help,h",		"Print usage information and exit");

	// Description of runtime options

	bpo::options_description	runtime("Runtime options");

	runtime.add_options()
		("config,c", bpo::value<boost::filesystem::path>(&options.configFile)->required(),		"Specify the configuration file");

	// Description des options visibles

	bpo::options_description	visible("Allowed options");

	visible.add(general).add(runtime);

	// Description of all options supported on the command line

	bpo::options_description	all("Allowed options");
	
	all.add(general).add(runtime);

	// Parse command line

	bpo::variables_map			vm;

	bpo::store(bpo::parse_command_line(argc, argv, all), vm);

	bpo::notify(vm);

	// Analyze parsed values

	options.printHelp = vm.count("help") != 0;

	// Print help if required

	if (options.printHelp)
	{
		std::cout << "Usage" << std::endl;
		std::cout << "    new-nav-engine [options] --config <file>" << std::endl << std::endl;

		std::cout << general << std::endl;

		std::cout << runtime << std::endl;
	}
}

// Start the engine
void	App::start(
	const CommandLineOptions&	options)
{
	bool	goOn{ true };

	// Load the configuration file.

	if (goOn)
	{
		std::ifstream		file;
		
		file.exceptions(std::ios::failbit);

		try
		{
			file.open(options.configFile.string().c_str());
			file >> _config;
		}
		catch(std::exception&	e)
		{
			std::cerr << "failed to read config file: " << e.what() << std::endl;
			goOn = false;
		}
	}

	// Load the modules located into the executable folder and additional folder
	// provided into the configuration.

	if (goOn)
	{
		loadModules();
	}

	// Create the components.

	if (goOn)
	{
		goOn = createComponents();
	}

	// Configure the components.

	if (goOn)
	{
		configureComponents();
	}
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
