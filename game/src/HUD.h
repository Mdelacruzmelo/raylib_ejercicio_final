#pragma once
#include "Character.h"
#include "raylib.h"

enum E_TypeHUD {
	H_GAME,
	H_PAUSE,
	H_HABILITIES,
	H_INIT_HABILITIES,
	H_LOAD_DATA,
	H_INIT_LOAD_DATA,
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
	void DrawLoadDataWidget(E_TypeHUD typeHUDInput);
	void DrawMainMenuWidget();
	void DrawGameWidget();

	void ItemNumberPress(int num);
	void DrawAbButtons(E_AbilityType abType, int order);
	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, Color cButton, Color cText, bool outline);
	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText);
	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, bool outline);

	void DrawRemoveButton(Rectangle rec, int slotNumber, Color color);
	Rectangle GetRectButtonRemove(Rectangle rec);

	int ButtonPressed();
	void RestartMainMenuButtons();
	bool GetInConfirmingModal();
	void OpenConfirmModal(int buttonPressed);
	void CloseConfirmModal();

	bool IsSelectingSlot();
	bool IsDeletingSlot();

	void Notify(char* message);
	void ShowNotification();
	void HideNotification();

private:

	E_TypeHUD type;
	Character* character;

	int padding = 20;

	int expBarHeight = 10;
	int expNumbersSize = 30;

	int healthBarWidth = 200;
	int healthBarHeight = 20;

	int itemSize = 30.f;
	int buttonPressed = 0;

	int slotQuantity = 4;
	bool isConfirming = false;
	int yesConfirmButton = 0;

	bool showingNotification = false;
	bool notiAnimStart = false;
	bool notiAnimEnd = false;
	float notificationCounter = 0;
	float notificationCounterMax = 2.f;
	char* notificationMessage;

};