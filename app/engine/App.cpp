#include <iostream>
#include <fstream>
#include <csignal>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "App.h"

namespace bpo = boost::program_options;

namespace newNav {
namespace app {
namespace engine {


App*	App::_uniqueInstance{ nullptr };


// Constructor.
App::App(
	)
{
	if (_uniqueInstance != nullptr)
	{
		throw std::logic_error("only one instance of newNav::app::engine can exists");
	}
	else
	{
		_uniqueInstance = this;
	}
	
	signal(SIGINT, &App::onSigTerm);
	signal(SIGTERM, &App::onSigTerm);
#if defined(SIGQUIT)
	signal(SIGQUIT, &App::onSigTerm);
#endif // defined(SIGQUIT)
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
	bool				goOn{ true };
	nlohmann::json		config;

	// Load the configuration data from the file.

	if (goOn)
	{
		std::ifstream		file;
		
		file.exceptions(std::ios::failbit);

		try
		{
			file.open(options.configFile.string().c_str());
			file >> config;
		}
		catch(std::exception&	e)
		{
			std::cerr << "failed to read config file: " << e.what() << std::endl;
			goOn = false;
		}
	}

	// Initialize the component manager.

	if (goOn)
	{
		try
		{
			_manager.initialize(config);
		}
		catch(std::exception&	e)
		{
			std::cerr << "failed to initialize the component manager (see log for details): " << e.what() << std::endl;
			goOn = false;
		}
	}

	// Run the component manager main loop.

	if (goOn)
	{
		try
		{
			_manager.run();
		}
		catch(std::exception&	e)
		{
			std::cerr << "unsupported exception occurs (see log for details): " << e.what() << std::endl;
			goOn = false;
		}
	}
}


// Handler for the SIGINT, SIGTERM and SIGQUIT signals.
void	App::onSigTerm(
	int		signum)
{
	(void) signum;	// Unused parameter.
	
	if (_uniqueInstance != nullptr)
	{
		_uniqueInstance->_manager.stop();
	}
}


} // namespace engine
} // namespace app
} // namespace newNav
