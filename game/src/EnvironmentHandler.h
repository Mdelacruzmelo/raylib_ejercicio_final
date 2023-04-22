#pragma once
#include "raylib.h"
#include "Environment.h"
#include "Character.h"

class EnvironmentHandler
{
public:
	EnvironmentHandler(Character* characterInput);

	int quantity = 0;
	Environment* environments;
	Character* character;

	void Draw();
	void Append(Environment* newEnvironment);

private:

};
