#pragma once
#include "raylib.h"

class Character
{
public:
	Character();

	float velocity = 1.f;
	float acceleration = 4.f;
	float characterSize = 40.f;
	float characterRadius = characterSize / 2;
	float attackDistance = 70.f;
	Vector2 pos = { 600, 540 };

	void Draw();
	void Move(Vector2 movement);
	void Attack(Vector2 endVector);

private:

};
