#pragma once
#include "raylib.h"
#include "Character.h"
#include "HUD.h"
#include "raymath.h" // for vectors
#include <cmath> // for simple math
#include "InventoryItemsUtils.h"
#include "Utils.h"
#include "SaveData.h"

class PlayerController
{
public:
	PlayerController(Character* characterInput, HUD* hudInput);

	void Play();
	void SetTypeHUD(E_TypeHUD typeHUDInput);
	E_TypeHUD GetTypeHUD();
	void SaveGame(int slot);
	void LoadGame(int slot);
	void DeleteSlotGame(int slot);
	void CheckSlots();
	bool* GetSlotsAvailable();
	int GetSlotsQuantity();
	bool IsSlotAvailable(int slot);
	void RestartCheckSlots();

private:

	SaveData* data;
	Vector2 movement = { 0.f, 0.f };
	Vector2 mousePosition = { 0.f, 0.f };
	float cursorSize = 50.f;
	float cursorRadius = cursorSize / 2;
	float cursorDepth = 2.5f;

	Character* character = nullptr;
	HUD* hud = nullptr;
	E_TypeHUD typeHUD = H_MAIN_MENU;

	bool checkingSlots = true;
	int slotsQuantity = 4;
	bool* slots = new bool[slotsQuantity] {false, false, false, false};

};