#pragma once
#include "Character.h"
#include "raylib.h"
#include "Utils.h"

class HUD
{
public:
	HUD(Character* characterInput);
	void Draw(E_TypeHUD typeHUDInput);

	void DrawPauseWidget();
	void DrawAbilitiesWidget(E_TypeHUD typeHUDInput);
	void DrawSaveDataWidget();
	void DrawLoadDataWidget(E_TypeHUD typeHUDInput);
	void DrawLoadingGameWidget();
	void DrawLooseGameWidget();
	void DrawWinGameWidget();
	void DrawMainMenuWidget();
	void DrawGameWidget();
	void DrawbackgroundGradient();

	void ItemNumberPress(int num);
	void DrawAbButtons(E_AbilityType abType, int order);

	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, Color cButton, Color cText, bool outline);
	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, const char* buttonText, Color cButton, Color cText, bool outline);

	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText);
	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, const char* buttonText);

	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, bool outline);
	void DrawMenuButton(Rectangle buttonRec, int buttonNumber, const char* buttonText, bool outline);

	void DrawRemoveButton(Rectangle rec, int slotNumber, Color color);
	Rectangle GetRectButtonRemove(Rectangle rec);

	int ButtonPressed();
	void RestartMainMenuButtons();
	bool GetInConfirmingModal();
	void OpenConfirmModal(int buttonPressed, char* confirmQuestionInput);
	void CloseConfirmModal();

	bool IsSelectingSlot();
	bool IsDeletingSlot();

	void Notify(char* message);
	void ShowNotification();
	void HideNotification();

	void ShowConfirmHUD(char* message, int yesNumber, int noNumber);
	void ShowConfirmHUD(const char* message, int yesNumber, int noNumber);

	void SetSlots(bool* slotsInput);
	void SetSlotsQuantity(int slotsQuantityInput);
	bool SlotAvailable();
	void DrawBloodDamage();
	void SoundHover(int buttonNumber);

	void SetLoadingTimes(float time, float maxTime);

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
	char* confirmQuestion;
	char* notificationMessage;

	bool* slots;
	int slotsQuantity = 0;
	int hurtTimer = 0;
	float hurtOpacity = 0.f;

	Texture2D pillHealthTexture;
	Texture2D pillSpeedTexture;
	Texture2D keyTexture;
	Texture2D police;
	Texture2D policeWin;

	Sound buttonHoverSound;
	Sound buttonClickedSound;
	Sound buttonRemoveSound;
	Sound buttonDisabledSound;

	bool playedHoverSound = false;
	int buttonNumberHovered = 0;
	float loadingTime;
	float loadingMaxTime;
	float LOADING_MAX_SECONDS = 10.f;
	float loadingBarPercentage = 0.f;

};