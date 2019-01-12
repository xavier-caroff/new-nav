#pragma once

namespace newNav {
namespace framework {

///
/// Base interface for components.
///
class IComponent
{
// Definition
public:

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
		run,
		/// The component has stopped and is ready to be deleted.
		halted,
	};

// Operations
public:

	/// Configure the component.
	virtual void    configure(
		) = 0;

	/// Start the execution of the component.
	virtual void    run(
		) = 0;

	/// Stop the execution of the component.
	virtual void	halt(
		) = 0;

// Enquiries
public:

	/// Get the current state of the component.
	virtual IComponent::State	getState(
		) const = 0;
};

} // namespace framework
} // namespace newNav
