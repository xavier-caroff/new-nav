#include <stdexcept>

#include "ComponentManager.h"

namespace newNav {
namespace framework {

// Constructor.
ComponentManager::ComponentManager(
	)
{
}

// Destructor.
ComponentManager::~ComponentManager(
	)
{
}

// Create a component from its class name.
IComponent*	ComponentManager::create(
	const std::string&	name,
	const std::string&	className)
{
	// Check if name is not already used.

	if (_components.find(name) != _components.end())
	{
		throw std::runtime_error("another existing component has the same name");
	}

	// Find the description.

	const ComponentRegistry::ComponentDescription&	description = _registry.find(className);
	IComponent*										component = description._create(name, this);

	_components.emplace(name, component);

	return component;
}

// Find a component from its name.
IComponent*	ComponentManager::find(
	const std::string&	name) const
{
	auto		itr = _components.find(name);
	IComponent*	result = nullptr;

	if (itr != _components.end())
	{
		result = itr->second.get();
	}

	return result;
}


// Initialize the object from configuration data.
void    ComponentManager::initialize(
	const ConfigData&	config)
{
	// Load modules.

	loadModules(config);

	// Create the components.

	createComponents(config);

	// Configure the components.

	configureComponents(config);
}

// Start the components and wait for terminaison request.
void	ComponentManager::run(
	)
{
}

// Load all possible modules.
void	ComponentManager::loadModules(
	const ConfigData&	config)
{
	boost::filesystem::path		exe = boost::dll::program_location();
	boost::filesystem::path		exeFolder = exe.parent_path();

	// Load modules installed in the same folder as the executable.

	loadModules(exeFolder);

	// Load the modules located in the additional folders of the configuration file.

	if (config.find("additionalPackageFolders") != config.end())
	{
		for(const auto& current : config["additionalPackageFolders"])
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
void	ComponentManager::loadModules(
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
				auto						registerComponents = lib.get<void(newNav::framework::ComponentRegistry&)>(ComponentRegistry::ENTRY_POINT_FUNCTION);

				registerComponents(_registry);

				_modules.push_back(std::move(lib));
			}
			catch(boost::system::system_error&)
			{
				// can't find the entry point, not a new-nav module :-(.
			}
		}
	}
}

// Create the components described into the configuration file.
void	ComponentManager::createComponents(
	const ConfigData&	config)
{
	for(const auto& current : config["components"])
	{
		std::string		name = current["name"].get<std::string>();
		std::string		className = current["className"].get<std::string>();

		try
		{
			this->create(name, className);
		}
		catch(std::runtime_error&	e)
		{
			// @todo Write into the log
			// std::cerr << "failed to create component " << name << " of class " << className << ": " << e.what() << std::endl;
			throw e;
		}
	}
}

// Configure each component.
void	ComponentManager::configureComponents(
	const ConfigData&	config)
{
	for(const auto& current : config["components"])
	{
		std::string		name = current["name"].get<std::string>();
		nlohmann::json	empty;
		nlohmann::json&	componentConfig{ empty };

		if (current.find("config") != current.end())
		{
			componentConfig = current["config"];
		}

		try
		{
			this->find(name)->configure(componentConfig);
		}
		catch(std::exception&	e)
		{
			// @todo Write into the log
			// std::cerr << "failed to configure component " << name << ": " << e.what() << std::endl;
			throw e;
		}
	}
}

} // namespace framework
} // namespace newNav
