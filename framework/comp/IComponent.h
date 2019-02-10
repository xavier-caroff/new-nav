#pragma once

#include <nlohmann/json.hpp>

namespace newNav {
namespace framework {
namespace comp {

///
/// Base interface for components.
///
class IComponent
{
// Definition
public:

	/// Configuration data is json.
	using ConfigData = nlohmann::json;

	///
	/// The different states of a component.
	///
	enum class State
	{
		/// Component just intancied but not configured, it is the
		/// initial state.
		created,
		/// Component is now fully initialized and ready to run.
		initialized,
		/// Component is now started.
		running,
		/// The component has stopped and is ready to be deleted.
		halted,
	};

// Operations
public:

	/// Configure the component.
	///
	/// @param config The configuration data.
	virtual void    configure(
		const ConfigData&	config) = 0;

	/// Start the execution of the component.
	virtual void    run(
		) = 0;

	/// Stop the execution of the component.
	virtual void	halt(
		) = 0;

// Enquiries
public:

	/// Get the current state of the component.
	///
	/// @return The current state of the component.
	virtual IComponent::State	state(
		) const = 0;

	/// Get the name of the component.
	///
	/// @return The name of the component.
	virtual const std::string&	name(
		) const = 0;
};

} // namespace comp
} // namespace framework
} // namespace newNav
