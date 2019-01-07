#pragma once

class App
{
public:

	App();
	virtual ~App();

	int execute(
		int		argc,
		char*	argv[]);
};