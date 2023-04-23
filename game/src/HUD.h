#pragma once
#include "Character.h"
#include "raylib.h"

class HUD
{
public:
	HUD(Character* characterInput);
	void UpdateData();
	void Draw();
	void ItemNumberPress(int num);

private:

	Character* character;

	int padding = 20;

	int expBarHeight = 10;
	int expNumbersSize = 30;

	int healthBarWidth = 200;
	int healthBarHeight = 20;

	int itemSize = 30.f;

};