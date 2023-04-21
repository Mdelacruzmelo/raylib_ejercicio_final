#pragma once
#include "raylib.h"
#include "Environment.h"

class EnvironmentHandler
{
public:
	EnvironmentHandler(Environment* environmentsInput, int size);

	int quantity = 0;
	Environment* environments;

	void Draw();

private:

};
