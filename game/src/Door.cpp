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

void Door::Draw(Vector2 posInput, Character* character)
{
	pos = posInput;
	DrawRectangle((int)posInput.x, (int)posInput.y, (int)width, (int)height, ORANGE);

	// Detectar por ubicación del jugador si se intersecta con la puerta

	if (
		CheckCollisionRecs(character->GetRect(), GetRect()) &&
		character->GetIsInteracting()
		) {
		DrawText(
			TextFormat("INTERACTING"),
			100,
			440,
			24,
			WHITE);
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
