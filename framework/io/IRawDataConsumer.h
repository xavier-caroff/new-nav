#pragma once

#include <memory>

#include "DataBuffer.h"

namespace newNav {
namespace framework {
namespace io {

///
/// Interface of components that consume raw data provided by a
/// component that implements IRawDataProvider.
///
/// The method IRawDataConsumer::consume() is called when new data are available.
///
class IRawDataConsumer
{
public:

	/// Provide some data to the consumer.
	///
	/// @param buffer Data to be consumed.
	virtual void	consume(
		std::shared_ptr<newNav::framework::io::DataBuffer>	buffer) = 0;
};

} // namespace io
} // namespace framework
} // namespace newNav
