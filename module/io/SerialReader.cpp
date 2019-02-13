#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "SerialReader.h"

namespace boost {
namespace asio {

	NLOHMANN_JSON_SERIALIZE_ENUM( serial_port_base::flow_control::type, {
		{ serial_port_base::flow_control::type::none,		"none" },
		{ serial_port_base::flow_control::type::software,	"software" },
		{ serial_port_base::flow_control::type::hardware,	"hardware" },
	})

	NLOHMANN_JSON_SERIALIZE_ENUM( serial_port_base::parity::type, {
		{ serial_port_base::parity::type::none,		"none" },
		{ serial_port_base::parity::type::odd,		"odd" },
		{ serial_port_base::parity::type::even,		"even" },
	})

	NLOHMANN_JSON_SERIALIZE_ENUM( serial_port_base::stop_bits::type, {
		{ serial_port_base::stop_bits::type::one,			"one" },
		{ serial_port_base::stop_bits::type::onepointfive,	"onepointfive" },
		{ serial_port_base::stop_bits::type::two,			"two" },
	})

} // namespace asio
} // namespace boost

namespace nlohmann {

	/// Implementation of serialization of boost::asio::serial_port::baud_rate
	/// for JSON jor modern C++ library.
	template<>
    struct adl_serializer<boost::asio::serial_port::baud_rate>
	{
		using type = boost::asio::serial_port::baud_rate;
		
		/// Store a boost::asio::serial_port::baud_rate object into a json
		/// object.
		static void to_json(
			json&			j,
			const type&		value)
		{
			j = value.value();
        }
		
		/// Load a boost::asio::serial_port::baud_rate object from a json
		/// object.
        static void from_json(
			const json&		j,
			type&			value)
		{
			value = type(j.get<unsigned int>());
        }
    };

	/// Implementation of serialization of boost::asio::serial_port::flow_control
	/// for JSON jor modern C++ library.
	template<>
    struct adl_serializer<boost::asio::serial_port::flow_control>
	{
		using type = boost::asio::serial_port::flow_control;
		
		/// Store a boost::asio::serial_port::flow_control object into a json
		/// object.
		static void to_json(
			json&			j,
			const type&		value)
		{
			j = value.value();
        }
		
		/// Load a boost::asio::serial_port::flow_control object from a json
		/// object.
        static void from_json(
			const json&		j,
			type&			value)
		{
			value = type(j.get<boost::asio::serial_port::flow_control::type>());
        }
    };

	/// Implementation of serialization of boost::asio::serial_port::parity
	/// for JSON jor modern C++ library.
	template<>
    struct adl_serializer<boost::asio::serial_port::parity>
	{
		using type = boost::asio::serial_port::parity;
		
		/// Store a boost::asio::serial_port::parity object into a json
		/// object.
		static void to_json(
			json&			j,
			const type&		value)
		{
			j = value.value();
        }
		
		/// Load a boost::asio::serial_port::parity object from a json
		/// object.
        static void from_json(
			const json&		j,
			type&			value)
		{
			value = type(j.get<boost::asio::serial_port::parity::type>());
        }
    };

	/// Implementation of serialization of boost::asio::serial_port::stop_bits
	/// for JSON jor modern C++ library.
	template<>
    struct adl_serializer<boost::asio::serial_port::stop_bits>
	{
		using type = boost::asio::serial_port::stop_bits;
		
		/// Store a boost::asio::serial_port::stop_bits object into a json
		/// object.
		static void to_json(
			json&			j,
			const type&		value)
		{
			j = value.value();
        }
		
		/// Load a boost::asio::serial_port::stop_bits object from a json
		/// object.
        static void from_json(
			const json&		j,
			type&			value)
		{
			value = type(j.get<boost::asio::serial_port::stop_bits::type>());
        }
    };

	/// Implementation of serialization of boost::asio::serial_port::character_size
	/// for JSON jor modern C++ library.
	template<>
    struct adl_serializer<boost::asio::serial_port::character_size>
	{
		using type = boost::asio::serial_port::character_size;
		
		/// Store a boost::asio::serial_port::character_size object into a json
		/// object.
		static void to_json(
			json&			j,
			const type&		value)
		{
			j = value.value();
        }
		
		/// Load a boost::asio::serial_port::character_size object from a json
		/// object.
        static void from_json(
			const json&		j,
			type&			value)
		{
			value = type(j.get<unsigned int>());
        }
    };
}

namespace newNav {
namespace module {
namespace io {

IMPLEMENT_COMPONENT(SerialReader)

// Constructor.
SerialReader::SerialReader(
	const std::string&							name,
	newNav::framework::comp::IComponentManager*	manager)
	: newNav::framework::comp::BaseComponent{ name, manager }
{
}

// Destructor.
SerialReader::~SerialReader(
	)
{
}

// Configure the component.
void    SerialReader::configure(
	const newNav::framework::comp::IComponent::ConfigData&	config)
{
	config.at("port").get_to(_portName);
	config.at("baudRate").get_to(_config.baudRate);
	config.at("flowControl").get_to(_config.flowControl);
	config.at("parity").get_to(_config.parity);
	config.at("stopBits").get_to(_config.stopBits);
	config.at("characterSize").get_to(_config.characterSize);

	setState(IComponent::State::initialized);
}

// Start the execution of the component.
void    SerialReader::run(
	)
{
	// The thread can be started only one time.

	if (_reader.joinable())
	{
		throw std::logic_error("the component has already been started");
	}

	// Start the worker thread.

	_reader = std::thread(std::bind(&SerialReader::execute, this));
}

// Stop the execution of the component.
void	SerialReader::halt(
	)
{
	if (state() == IComponent::State::running)
	{
		_stopRequested.store(true);
		try
		{
			_port.cancel();
		}
		catch(std::exception&)
		{
			// Nothing to do
		}
		_cvStop.notify_one();
	}
}

// Register a new subscriber.
void	SerialReader::subscribe(
	newNav::framework::io::IRawDataConsumer*	consumer)
{
	std::lock_guard<std::mutex>		lock(_mtxConsumers);

	if (std::find(_consumers.begin(), _consumers.end(), consumer) == _consumers.end())
	{
		_consumers.push_back(consumer);
	}
}

// Unregister a subscriber.
void	SerialReader::unsubscribe(
	newNav::framework::io::IRawDataConsumer*	consumer)
{
	std::lock_guard<std::mutex>		lock(_mtxConsumers);

	auto	itr = std::find(_consumers.begin(), _consumers.end(), consumer);

	if (itr != _consumers.end())
	{
		_consumers.erase(itr);
	}
}

// Control function of the component running in a dedicated thread.
void	SerialReader::execute(
	)
{
	setState(IComponent::State::running);

	do
	{
		// Try to read data.

		try
		{
			// Open and configure the port.
			_port.open(_portName);

			_port.set_option(_config.baudRate);
			_port.set_option(_config.flowControl);
			_port.set_option(_config.parity);
			_port.set_option(_config.stopBits);
			_port.set_option(_config.characterSize);

			doRead();

			_ioContext.run();

			_port.close();
		}
		catch(const std::exception& e)
		{
			// @todo Write into the log
			// std::cerr << "failed to receive through serial port " << _portName << ": " << e.what() << std::endl;
		}

		// Read failed, wait few seconds before a new attempt.

		if (_stopRequested.load() == false)
		{
			std::unique_lock<std::mutex> lock(_mtxStop);

			_cvStop.wait_for(lock, std::chrono::seconds{ 20 }, [this]{
				return
					_stopRequested.load() == true;
			});
		}
	}
	while(_stopRequested.load() == false);

	setState(IComponent::State::halted);
}

// Do the read of a sentence.
void	SerialReader::doRead(
	)
{
	_port.async_read_some(
		boost::asio::buffer(_readBuffer, BUFFER_SIZE), [this](
			const boost::system::error_code&	error,
			std::size_t							bytesTransferred)
		{
			if (!error && bytesTransferred > 0)
			{
				// Forward the data to the consumers.
				using newNav::framework::io::DataBuffer;

				std::shared_ptr<DataBuffer>		sharedBuffer = std::make_shared<DataBuffer>(_readBuffer, bytesTransferred);
				std::lock_guard<std::mutex>		lock(_mtxConsumers);

				for (auto consumer : _consumers)
				{
					consumer->consume(sharedBuffer);
				}

				// Start a new read.
				doRead();
			}
		});
}

} // namespace io
} // namespace module
} // namespace newNav
