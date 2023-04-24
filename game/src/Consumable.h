#pragma once
#include "raylib.h"
#include "InventoryItemsUtils.h"
#include "Character.h"

class Consumable
{
public:
	Consumable();
	Consumable(E_ItemType typeInput, Character* characterInput, Vector2 loc);
	void DetectGrab();
	bool GetGrabbed();
	void Draw();
	E_ItemType GetType();
	Rectangle GetRect();

private:

	E_ItemType type = I_POTION_HEALTH;
	Character* character;
	Vector2 location = { -100.f, -100.f };

	bool grabbed = false;
	float size = 30.f;
	Rectangle rec = { location.x, location.y, size, size };
	Color color = GREEN;

};
