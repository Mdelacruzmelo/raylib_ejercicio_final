#pragma once
#include "raylib.h"
#include "EnvironmentUtils.h"
#include "Character.h"

class Door
{
public:
	Door();
	Door(E_Side doorSideInput, char* doorIdInput);

	void Draw(Vector2 posInput, Character* character);
	E_Side GetDoorSide();
	float GetHeight();
	float GetWidth();
	Rectangle GetRect();
	char* GetId();
	void Target(char* targetIdInput);
	char* GetTargetId();
	Vector2 GetPosition();

private:

	Vector2 pos;
	float width = 40.f;
	float height = 70.f;
	E_Side doorSide;
	char* doorId;
	char* doorTargetId;
};