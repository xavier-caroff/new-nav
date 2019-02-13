#pragma once

#include <atomic>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>

#include <boost/asio/io_context.hpp>
#include <boost/asio/serial_port.hpp>

#include "comp/BaseComponent.h"
#include "comp/ComponentRegistry.h"
#include "io/IRawDataProvider.h"

namespace newNav {
namespace module {
namespace io {

///
/// Implement a component that read data on a serial port.
///
class SerialReader:
	public newNav::framework::comp::BaseComponent,
	public newNav::framework::io::IRawDataProvider
{
	DECLARE_COMPONENT(SerialReader)

// Construction, destruction
private:

	/// Constructor.
	///
	/// @param name Name of the component.
	/// @param manager Pointer to the component manager.
	SerialReader(
		const std::string&							name,
		newNav::framework::comp::IComponentManager*	manager);

	/// Destructor.
	virtual ~SerialReader(
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

// Implementation of IRawDataProvider
public:

	/// Register a new subscriber.
	///
	/// @param consumer Pointer to the component to register.
	virtual void	subscribe(
		newNav::framework::io::IRawDataConsumer*	consumer) override final;

	/// Unregister a subscriber.
	///
	/// @param consumer Pointer to the component to unregister.
	virtual void	unsubscribe(
		newNav::framework::io::IRawDataConsumer*	consumer) override final;

// Private definitions
private:

	/// Configuration of a serial port.
	struct Config
	{
		/// Baud rate in number of bits per second.
		boost::asio::serial_port::baud_rate			baudRate;
		/// Flow control.
		boost::asio::serial_port::flow_control		flowControl;
		/// Parity.
		boost::asio::serial_port::parity			parity;
		/// Number of stop bits.
		boost::asio::serial_port::stop_bits			stopBits;
		/// Size of a character in bits.
		boost::asio::serial_port::character_size	characterSize;

		/// Construct a configuration.
		Config()
			:	baudRate(4800),
				flowControl(boost::asio::serial_port::flow_control::none),
				parity(boost::asio::serial_port::parity::none),
				stopBits(boost::asio::serial_port::stop_bits::one),
				characterSize(8)	{}
	};

	/// Size of the read buffer.
	static const size_t		BUFFER_SIZE{ 512 };

// Implementation
private:

	/// Control function of the component running in a dedicated thread.
	void	execute(
		);

	/// Do the read of a sentence.
	void	doRead(
		);

// Private attributes
private:

	/// Boost::asio io context.
	boost::asio::io_context							_ioContext;

	/// The serial port.
	boost::asio::serial_port						_port{ _ioContext };

	/// The name of the serial port.
	std::string										_portName;
	
	/// The configuration of the serial port.
	Config											_config;

	/// The thread that perform readings.
	std::thread										_reader;

	/// The buffer to store read data.
	unsigned char									_readBuffer[BUFFER_SIZE + 1];

	/// Mutex to implement stop request.
	std::mutex										_mtxStop;

	/// Condition variable to implement stop request.
	std::condition_variable							_cvStop;

	// Indicate a request to stop.
	std::atomic_bool								_stopRequested{ false };

	/// Mutex to protect concurrent acces to _consumers.
	std::mutex										_mtxConsumers;

	/// Collection of pointers to consumers of the received data.
	std::list<
		newNav::framework::io::IRawDataConsumer*>	_consumers;
};

} // namespace io
} // namespace module
} // namespace newNav
