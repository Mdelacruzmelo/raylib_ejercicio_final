#pragma once
#include "raylib.h"
#include "Environment.h"
#include "Character.h"
#include "AIController.h"

class EnvironmentHandler
{
public:
	EnvironmentHandler(Character* characterInput);

	int quantity = 0;
	Environment* environments;
	Character* character;
	AIController* aiController = nullptr;

	void Draw();
	void Append(Environment* newEnvironment);
	void SetAIController(AIController* aiControllerInput);
	void SetMap();

private:

};
