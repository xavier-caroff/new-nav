#pragma once

#include <list>
#include <boost/dll.hpp>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>

#include "ComponentRegistry.h"
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
	int execute(
		int		argc,
		char*	argv[]);

// Implementation
private:

	/// Load all possible modules.
	void	loadModules(
	);

	/// Load the external modules located into a given folder.
	///
	/// @param folder Absolute path to the folder to search modules.
	void	loadModules(
		const boost::filesystem::path&	folder);

	/// Create the components described into the configuration file.
	///
	/// @return true if all the components has been created, false otherwise.
	bool	createComponents(
		);

	/// Configure each component.
	void	configureComponents(
		);
	
// Private attributes
private:

	/// Collection of modules loaded dynamically.
	std::list<boost::dll::shared_library>	_modules;

	/// Registry of components description.
	newNav::framework::ComponentRegistry	_registry;

	/// Manager of components.
	newNav::framework::ComponentManager		_manager;

	/// The configuration data.
	nlohmann::json							_config;
};

} // namespace engine
} // namespace app
} // namespace newNav
