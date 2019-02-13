#pragma once

#include <atomic>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>

#include "comp/BaseComponent.h"
#include "comp/ComponentRegistry.h"
#include "io/IRawDataConsumer.h"
#include "io/IRawDataProvider.h"

namespace newNav {
namespace module {
namespace io {

///
/// Component that displays the content of a buffer of data.
///
class DataBufferDisplay:
	public newNav::framework::comp::BaseComponent,
	public newNav::framework::io::IRawDataConsumer
{
	DECLARE_COMPONENT(DataBufferDisplay)

// Construction, destruction
private:

	/// Constructor.
	///
	/// @param name Name of the component.
	/// @param manager Pointer to the component manager.
	DataBufferDisplay(
		const std::string&							name,
		newNav::framework::comp::IComponentManager*	manager);

	/// Destructor.
	virtual ~DataBufferDisplay(
		);

// Partial implementation of IComponent
public:

	/// Configure the component.
	///
	/// @param config The configuration data.
	virtual void    configure(
		const newNav::framework::comp::IComponent::ConfigData&	config) override final;

	/// Start the execution of the component.
	virtual void    run(
		) override final;

	/// Stop the execution of the component.
	virtual void	halt(
		) override final;

// Implementation of IRawDataConsumer
public:

	/// Provide some data to the consumer.
	///
	/// @param buffer Data to be consumed.
	virtual void	consume(
		std::shared_ptr<newNav::framework::io::DataBuffer>	buffer) override final;

// Private attributes
private:

	/// Pointer to the provider of data to display.
	newNav::framework::io::IRawDataProvider*	_provider{ nullptr };
};

} // namespace io
} // namespace module
} // namespace newNav
