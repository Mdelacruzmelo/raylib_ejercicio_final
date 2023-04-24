#pragma once
#include "raylib.h"
#include "Character.h"
#include "InventoryItemsUtils.h"

class Interactable
{
public:

	Interactable();
	Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput);

	void Interact();
	void Draw();
	void DetectGrab();

private:

	Vector2 pos;
	float squareSize = 10.f;
	Color color = RED;
	float padding = 5.f;
	float longitude = 30.f;

	E_ItemType type = I_KEY;

	Rectangle longPart = Rectangle{ pos.x, pos.y, longitude, 8.f };
	Rectangle squarePart = Rectangle{ pos.x - squareSize, pos.y - (squareSize / 2), squareSize, squareSize };
	Rectangle tooth1Part = Rectangle{ pos.x + 5.f, pos.y, 5.f, 12.f };
	Rectangle tooth2Part = Rectangle{ pos.x + 15.f, pos.y, 5.f, 12.f };
	Rectangle tooth3Part = Rectangle{ pos.x + 20.f, pos.y, 5.f, 12.f };
	Rectangle round = Rectangle{
		pos.x - squareSize - padding,
		pos.y - (squareSize / 2) - padding,
		squareSize + (2 * padding) + longitude,
		squareSize + (2 * padding) + longitude
	};

	Character* character;
	bool grabbed = false;
};