#pragma once
#include "raylib.h"
#include "Character.h"
#include "InventoryItemsUtils.h"

class Interactable
{
public:

	Interactable();
	Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput);

	void Restart();
	void Draw();
	void DetectGrab();
	bool GetGrabbed();

private:

	Vector2 initialPos = Vector2{ -100.f, -100.f };
	Vector2 pos;
	float squareSize = 20.f;
	Color color = YELLOW;
	float padding = 5.f;
	float longitude = 30.f;

	E_ItemType type = I_KEY;

	Rectangle longPart;
	Rectangle squarePart;
	Rectangle tooth1Part;
	Rectangle tooth2Part;
	Rectangle tooth3Part;
	Rectangle round;

	Character* character;
	bool grabbed = false;
};