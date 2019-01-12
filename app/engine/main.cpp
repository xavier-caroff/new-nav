#include "App.h"


int main(
	int		argc,
	char*	argv[])
{
	newNav::app::engine::App		app;

	return app.execute(argc, argv);
}
