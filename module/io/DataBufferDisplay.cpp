#include <cctype>
#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>

#include "DataBufferDisplay.h"

namespace newNav {
namespace module {
namespace io {

IMPLEMENT_COMPONENT(DataBufferDisplay)

// Constructor.
DataBufferDisplay::DataBufferDisplay(
	const std::string&							name,
	newNav::framework::comp::IComponentManager*	manager)
	: newNav::framework::comp::BaseComponent{ name, manager }
{
}

// Destructor.
DataBufferDisplay::~DataBufferDisplay(
	)
{
}

// Configure the component.
void    DataBufferDisplay::configure(
	const newNav::framework::comp::IComponent::ConfigData&	config)
{
	std::string		provider = config.at("provider").get<std::string>();

	// Find the provider.
	newNav::framework::comp::IComponent*	component = manager()->find(provider);

	if (component == nullptr)
	{
		std::string		message;

		message = "'" + provider + "' is not a component";

		throw std::runtime_error(message.c_str());
	}

	// Check the provider is valid.
	_provider = dynamic_cast<newNav::framework::io::IRawDataProvider*>(component);

	if (_provider == nullptr)
	{
		std::string		message;

		message = "'" + provider + "' does not implement the IRawDataProvider interface";

		throw std::runtime_error(message.c_str());
	}

	setState(IComponent::State::initialized);
}

// Start the execution of the component.
void    DataBufferDisplay::run(
	)
{
	_provider->subscribe(this);

	setState(IComponent::State::running);
}

// Stop the execution of the component.
void	DataBufferDisplay::halt(
	)
{
	_provider->unsubscribe(this);

	setState(IComponent::State::halted);
}

// Provide some data to the consumer.
void	DataBufferDisplay::consume(
    std::shared_ptr<newNav::framework::io::DataBuffer>	buffer)
{
	std::cout << "(" << name() << ")[";

	for(size_t idx = 0; idx < buffer->size(); ++idx)
	{
		unsigned char	car = (*buffer)[idx];

		if (std::isprint(car) && car != '\\')
		{
			std::cout << car;
		}
		else
		{
			switch(car)
			{
			case '\\':
				std::cout << "\\\\";
				break;
			case '\r':
				std::cout << "\\r";
				break;
			case '\n':
				std::cout << "\\n";
				break;
			case '\t':
				std::cout << "\\t";
				break;
			case '\f':
				std::cout << "\\f";
				break;
			default:
				std::cout << "\\x" << std::hex << std::nouppercase << std::setw(2) << std::setfill('0') << (int) car;
				break;
			}
		}
	}

	std::cout << "]" << std::endl;
}

} // namespace io
} // namespace module
} // namespace newNav
