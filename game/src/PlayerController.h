#pragma once
#include "raylib.h"
#include "Character.h"
#include "HUD.h"

class PlayerController
{
public:
	PlayerController(Character* characterInput, HUD* hudInput);

	void Play();
	void SetTypeHUD(E_TypeHUD typeHUDInput);
	E_TypeHUD GetTypeHUD();

private:

	Vector2 movement = { 0.f, 0.f };
	Vector2 mousePosition = { 0.f, 0.f };
	float cursorSize = 50.f;
	float cursorRadius = cursorSize / 2;
	float cursorDepth = 2.5f;

	Character* character = nullptr;
	HUD* hud = nullptr;
	E_TypeHUD typeHUD = H_MAIN_MENU;

};