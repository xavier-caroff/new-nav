#pragma once

#include <string>
#include <map>
#include <memory>
#include <list>

#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <nlohmann/json.hpp>

#include "IComponentManager.h"
#include "ComponentRegistry.h"

namespace newNav {
namespace framework {

///
/// The component manager manage components.
///
class ComponentManager:
	public IComponentManager
{
// Définition
public:

	/// Configuration data is json.
	using ConfigData = nlohmann::json;

// Construction, destruction
public:

	/// Constructor.
	ComponentManager(
		);

	/// Destructor.
	virtual ~ComponentManager(
		);

// Implementation of IComponentManager
public:

	/// Create a component from its class name.
	///
	/// @param name Name of the component.
	/// @param className Class name of the component.
	///
	/// @return Pointer on the component.
	///
	/// @throw std::runtime_error when another existing component has the same name.
	/// @throw std::runtime_error when no component description registered with this class name.
	virtual IComponent*	create(
		const std::string&	name,
		const std::string&	className) override final;

	/// Find a component from its name.
	///
	/// @return Pointer on the component, nullptr if no component.
	virtual IComponent*	find(
		const std::string&	name) const override final;

// Operations
public:

	/// Prepare the execution.
	///
	/// This method loads the external modules and the create and configure components.
	///
	/// @param config The configuration data.
	///
	/// @throw std::exception if unhandled error occurs during the processing.
	void    initialize(
		const ConfigData&	config);

	/// Start the components and wait for terminaison request.
	///
	/// @throw std::exception if unhandled error occurs during the processing.
	void	run(
		);

// Implementation
private:

	/// Load all possible modules.
	///
	/// Modules localted in the same folder as the executable and modules located
	/// in the additional folders described in the configuration file.
	///
	/// @param config The configuration data.
	void	loadModules(
		const ConfigData&	config);

	/// Load the external modules located into a given folder.
	///
	/// @param folder Absolute path to the folder to search modules.
	void	loadModules(
		const boost::filesystem::path&	folder);

	/// Create the components described into the configuration file.
	///
	/// @param config The configuration data.
	///
	/// @return true if all the components has been created, false otherwise.
	void	createComponents(
		const ConfigData&	config);

	/// Configure each component.
	///
	/// @param config The configuration data.
	void	configureComponents(
		const ConfigData&	config);

// Private attributes
private:

	/// Registry of components description.
	newNav::framework::ComponentRegistry			_registry;

	/// Collection of modules loaded dynamically.
	std::list<boost::dll::shared_library>			_modules;

	/// The collection of components owned by this manager.
	std::map<
		std::string, std::unique_ptr<IComponent>>	_components;	
};

} // namespace framework
} // namespace newNav
