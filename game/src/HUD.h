#pragma once
#include "Character.h"
#include "raylib.h"

enum E_TypeHUD {
	H_GAME,
	H_PAUSE,
	H_HABILITIES,
	H_INIT_HABILITIES,
	H_LOAD_DATA,
	H_MAIN_MENU,
	H_LOOSE_GAME,
	H_WIN_GAME,
};


class HUD
{
public:
	HUD(Character* characterInput);
	void Draw(E_TypeHUD typeHUDInput);
	void DrawPauseWidget();
	void DrawAbilitiesWidget(E_TypeHUD typeHUDInput);
	void DrawLoadDataWidget();
	void DrawMainMenuWidget();
	void DrawGameWidget();
	void ItemNumberPress(int num);
	void DrawAbButtons(E_AbilityType abType, int order);

	int GetPauseButtonPressed();
	void RestartPauseButtons();

	int GetMainMenuButtonPressed();
	void RestartMainMenuButtons();

	int GetHabilityButtonPressed();
	void RestartHabilityButtons();


private:

	Character* character;

	int padding = 20;

	int expBarHeight = 10;
	int expNumbersSize = 30;

	int healthBarWidth = 200;
	int healthBarHeight = 20;

	int itemSize = 30.f;
	int pauseButtonPressed = 0;
	int habButtonPressed = 0;
	int mainMenuButtonPressed = 0;

};