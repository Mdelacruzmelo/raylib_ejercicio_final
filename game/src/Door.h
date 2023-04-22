#pragma once
#include "raylib.h"
// #include "Environment.h"
#include "EnvironmentUtils.h"

class Door
{
public:
	Door();
	Door(E_Side doorSideInput/*, Environment* environmentOwnerInput*/);

	// void To(Door* doorTo, Environment* environmentTargetInput);
	void Transport();
	void Draw(Vector2 posInput);
	E_Side GetDoorSide();
	float GetHeight();
	float GetWidth();

private:

	float width = 40.f;
	float height = 70.f;
	E_Side doorSide;
	// Environment* environmentOwner;
	// Environment* environmentTarget;
};