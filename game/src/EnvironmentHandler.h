#pragma once
#include "raylib.h"
#include "Environment.h"

class EnvironmentHandler
{
public:
	EnvironmentHandler();

	int quantity = 0;
	Environment* environments;

	void Draw();
	void Append(Environment* newEnvironment);

private:

};
