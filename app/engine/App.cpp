#include <iostream>

#include "App.h"

namespace newNav {
namespace app {
namespace engine {

// Constructor.
App::App(
	)
{
}

// Destructor.
App::~App(
	)
{
}

// Launch the application
int App::execute(
	int		argc,
	char*	argv[])
{
    std::cout << "Hello, world!\n";

	return 0;
}

} // namespace engine
} // namespace app
} // namespace newNav
