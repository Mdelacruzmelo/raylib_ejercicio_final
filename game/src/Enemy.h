#pragma once
#include "raylib.h"
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();

	void Play();
	void SetTarget(Character* characterInput);
	void SetPosition(Vector2 posInput);

private:

	float width = 40.f;
	float height = 50.f;
	bool arrivedToLoc = false;
	Character* character = nullptr;
	Vector2 targetLoc = Vector2{ 0.f, 0.f };

};
