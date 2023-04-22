#pragma once
#include "raylib.h"
#include "Character.h"

class PlayerController
{
public:
	PlayerController(Character* characterInput);

	Vector2 mousePosition = { 0.f, 0.f };
	float cursorSize = 50.f;
	float cursorRadius = cursorSize / 2;
	float cursorDepth = 2.5f;
	Vector2 movement = { 0.f, 0.f };

	void Play();

private:

	Character* character = nullptr;

};