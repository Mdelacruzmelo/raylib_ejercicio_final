#pragma once
#include "raylib.h"
#include "EnvironmentUtils.h"
#include "Character.h"

class Door
{
public:
	Door();
	Door(E_Side doorSideInput, char* doorIdInput);

	void Draw(Character* character);
	void Draw(Character* character, Vector2 posInput);
	E_Side GetDoorSide();
	float GetHeight();
	float GetWidth();
	Rectangle GetRect();
	Vector2 GetSize();
	char* GetId();
	void Target(char* targetIdInput);
	char* GetTargetId();
	Vector2 GetPosition();
	void SetPosition(Vector2 newPos);

private:

	Vector2 pos;
	float width = 40.f;
	float height = 70.f;
	E_Side doorSide;
	char* doorId;
	char* doorTargetId;
};