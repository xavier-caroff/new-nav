#pragma once

#include "IRawDataConsumer.h"

namespace newNav {
namespace framework {
namespace io {

///
/// Interface for components that provide data.
///
/// The components that consume data (implementing IRawDataConsumer) can
/// subscribe. When some new data are available the component will
/// call the IRawDataConsumer::consume() method on each subscriber.
///
class IRawDataProvider
{
public:

	/// Register a new subscriber.
	///
	/// @param consumer Pointer to the component to register.
	virtual void	subscribe(
		newNav::framework::io::IRawDataConsumer*	consumer) = 0;

	/// Unregister a subscriber.
	///
	/// @param consumer Pointer to the component to unregister.
	virtual void	unsubscribe(
		newNav::framework::io::IRawDataConsumer*	consumer) = 0;
};

} // namespace io
} // namespace framework
} // namespace newNav
