#include "Door.h"
#include "Environment.h"

Door::Door()
{
	// Por defecto la primera puerta a la izquierda si se construye sin parámetros
	// Cosa que posiblemente no ocurra, vamos a ver donde nos lleva el código

	doorSide = SIDE_LEFT;
}

Door::Door(E_Side doorSideInput, Environment* environmentOwnerInput)
{
	doorSide = doorSideInput;
	environmentOwner = environmentOwnerInput;
}

void Door::To(Door* doorTo, Environment* environmentTargetInput)
{
	environmentTarget = environmentTargetInput;
}

void Door::Transport()
{
	environmentOwner->Deactivate();
	environmentTarget->Activate();
}

void Door::Draw(Vector2 posInput)
{
	DrawRectangle((int)posInput.x, (int)posInput.y, (int)width, (int)height, ORANGE);
}

E_Side Door::GetDoorSide()
{
	return doorSide;
}

float Door::GetHeight()
{
	return height;
}

float Door::GetWidth()
{
	return width;
}
