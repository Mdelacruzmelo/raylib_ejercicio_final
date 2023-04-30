#pragma once
#include "raylib.h"
#include "EnvironmentUtils.h"
#include "Character.h"

class Door
{
public:
	Door();
	Door(E_Side doorSideInput, char* doorIdInput);

	void Draw(Character* characterInput);
	void Draw(Character* characterInput, Vector2 posInput);
	E_Side GetDoorSide();
	float GetHeight();
	float GetWidth();
	Rectangle GetRect();
	Vector2 GetSize();
	char* GetId();
	void Lock();
	void Unlock();
	bool GetIsLocked();
	void Target(char* targetIdInput);
	char* GetTargetId();
	Vector2 GetPosition();
	void SetPosition(Vector2 newPos);
	void SetRotation(float newRot);

private:

	Vector2 pos;
	float width = 80.f;
	float height = 80.f;
	float doorSize = 80.f;
	float rotation = 0.f;
	E_Side doorSide;
	char* doorId;
	char* doorTargetId;
	bool locked = false;
	bool showMessageLocked = false;
	int counterMessageLocked = 0;
	Character* character;

	Texture2D door;
	Texture2D doorLocked;

};