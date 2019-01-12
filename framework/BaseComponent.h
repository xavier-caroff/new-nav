#pragma once

#include <string>

#include "IComponent.h"

namespace newNav {
namespace framework {

///
/// Base class for components.
///
class BaseComponent
{
// Construction, destruction
public:

	/// Constructor.
	BaseComponent(
		const std::string&  name);

	/// Destructor.
	virtual ~BaseComponent(
		);
};

} // namespace framework
} // namespace newNav
