#pragma once

#include <boost/filesystem.hpp>

#include "ComponentManager.h"

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
	///
	/// @param argc Command line argument count.
	/// @param argv Command line arguments.
	///
	/// @return The exit code to pass to the operating system.
	int execute(
		int		argc,
		char*	argv[]);

// Definition
private:

	/// Command line options
	struct CommandLineOptions
	{
		/// Print usage information.
		bool					printHelp{ false };
		/// Configuration file name.
		boost::filesystem::path	configFile;
	};

// Implementation
private:

	/// Parse the options from the command line.
	///
	/// @param argc Command line argument count.
	/// @param argv Command line arguments.
	/// @param options [out] Options read from the command line.
	void	parseCmdLine(
		int					argc,
		char*				argv[],
		CommandLineOptions&	options);

	/// Start the engine
	///
	/// @param options Options read from the command line.
	void	start(
		const CommandLineOptions&	options);

	/// Handler for the SIGINT, SIGTERM and SIGQUIT signals.
	///
	/// @param signum The received signal. 
	static void	onSigTerm(
		int		signum);
	
// Private attributes
private:

	/// Manager of components.
	newNav::framework::ComponentManager		_manager;

	/// Pointer to the unique instance.
	static App*								_uniqueInstance;
};

} // namespace engine
} // namespace app
} // namespace newNav
