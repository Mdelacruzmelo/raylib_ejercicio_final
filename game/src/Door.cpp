#include "Door.h"

Door::Door()
{
	// Por defecto la primera puerta a la izquierda si se construye sin parámetros
	// Cosa que posiblemente no ocurra, vamos a ver donde nos lleva el código

	doorSide = SIDE_LEFT;
}

Door::Door(E_Side doorSideInput, char* doorIdInput)
{
	doorSide = doorSideInput;
	doorId = doorIdInput;
}

void Door::Draw(Character* character)
{
	DrawRectangle((int)pos.x, (int)pos.y, (int)width, (int)height, ORANGE);

	// Detectar por ubicación del jugador si se intersecta con la puerta

	if (
		CheckCollisionRecs(character->GetRect(), GetRect()) &&
		character->GetIsInteracting()
		) {
		character->SetDoorTargetId(GetTargetId());
		character->SetIsTransporting(true);
	}
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

Rectangle Door::GetRect()
{
	return Rectangle{ pos.x, pos.y, width, height };
}

Vector2 Door::GetSize()
{
	return Vector2{ width, height };
}

char* Door::GetId()
{
	return doorId;
}

void Door::Target(char* targetIdInput)
{
	doorTargetId = targetIdInput;
}

char* Door::GetTargetId()
{
	return doorTargetId;
}

Vector2 Door::GetPosition()
{
	return pos;
}

void Door::SetPosition(Vector2 newPos)
{
	pos = newPos;
}
