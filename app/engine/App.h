#pragma once

namespace newNav {
namespace app {
namespace engine {

///
/// Application class for engine.
///
class App
{
// Construction, destruction
public:

	/// Constructor.
	App(
		);

	/// Destructor.
	virtual ~App(
		);

// Operation
public:

	/// Launch the application.
	int execute(
		int		argc,
		char*	argv[]);
};

} // namespace engine
} // namespace app
} // namespace newNav
