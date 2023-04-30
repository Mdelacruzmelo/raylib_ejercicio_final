#pragma once
#include "raylib.h"
#include "Character.h"
#include "InventoryItemsUtils.h"

class Interactable
{
public:
	Interactable();
	Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput, Texture2D textureInput);

	void Restart();
	void Draw();
	void DetectGrab();
	bool GetIsGrabbed();

private:

	Vector2 initialPos = Vector2{ -100.f, -100.f };
	Vector2 pos;
	Vector2 textureSize = Vector2{ 80.f, 80.f };
	Vector2 center;

	E_ItemType type = I_KEY;
	Rectangle rec;

	Character* character;
	Texture2D texture;
	bool grabbed = false;
};