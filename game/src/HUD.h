#pragma once
#include "Character.h"
#include "raylib.h"

enum E_TypeHUD {
	H_GAME,
	H_PAUSE,
	H_HABILITIES,
	H_LOAD_DATA,
	H_MAIN_MENU,
};


class HUD
{
public:
	HUD(Character* characterInput);
	void Draw(E_TypeHUD typeHUDInput);
	void DrawPauseWidget();
	void DrawHabilitiesWidget();
	void DrawLoadDataWidget();
	void DrawMainMenuWidget();
	void DrawGameWidget();
	void ItemNumberPress(int num);

	int GetPauseButtonPressed();
	void RestartPauseButtons();

private:

	Character* character;

	int padding = 20;

	int expBarHeight = 10;
	int expNumbersSize = 30;

	int healthBarWidth = 200;
	int healthBarHeight = 20;

	int itemSize = 30.f;
	int pauseButtonPressed = 0;

};