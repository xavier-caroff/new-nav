#include <iostream>

#include "App.h"

App::App()
{
}

App::~App()
{
}

int App::execute(
	int		argc,
	char*	argv[])
{
    std::cout << "Hello, world!\n";

	return 0;
}
