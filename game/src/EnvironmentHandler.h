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
	int envActivated = 0;

	void Draw();
	void LoadDataFromCharacter();
	void Append(Environment* newEnvironment);
	void SetAIController(AIController* aiControllerInput);
	void SetMap();
	void ActivateEnvironment(int envIndex);
	void UpdateDoors(char* doorsData);
	void ToggleLockDoorById(char* doorId, bool lock);

private:

};
