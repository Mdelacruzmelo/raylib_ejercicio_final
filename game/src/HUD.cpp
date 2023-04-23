#include "HUD.h"
#include "InventoryItemsUtils.h"

HUD::HUD(Character* characterInput)
{
	character = characterInput;
}

void HUD::Draw(E_TypeHUD typeHUDInput) {
	if (typeHUDInput == H_PAUSE) DrawPauseWidget();
	else if (typeHUDInput == H_HABILITIES) DrawHabilitiesWidget();
	else if (typeHUDInput == H_LOAD_DATA) DrawLoadDataWidget();
	else if (typeHUDInput == H_MAIN_MENU) DrawLoadDataWidget();
	else DrawGameWidget();
}

void HUD::DrawGameWidget()
{
	if (character) {

		// Nivel actual 
		DrawRectangle(
			padding,
			GetScreenHeight() - padding - expNumbersSize,
			expNumbersSize - 2,
			expNumbersSize,
			YELLOW
		);

		int level = character->GetLevel();
		int nextLevel = level + 1;

		float left1Padding = expNumbersSize / 4;
		float left2Padding = expNumbersSize / 4;

		if (level == 1) left1Padding = expNumbersSize / 3;

		DrawText(
			TextFormat("%d", character->GetLevel()),
			padding + left1Padding,
			GetScreenHeight() - padding - expNumbersSize + (expNumbersSize / 4),
			22,
			BLACK);

		// Barra de experiencia fondo

		int experienceWidth = GetScreenWidth() - (padding * 2) - (expNumbersSize * 2);

		DrawRectangle(
			padding + expNumbersSize,
			GetScreenHeight() - padding - expBarHeight,
			experienceWidth,
			expBarHeight,
			GRAY
		);

		// Barra de experiencia

		DrawRectangle(
			padding + expNumbersSize,
			GetScreenHeight() - padding - expBarHeight,
			experienceWidth * character->GetNormalizedExperience(),
			expBarHeight,
			YELLOW
		);

		// Nivel siguiente

		DrawRectangle(
			GetScreenWidth() - padding - expNumbersSize + 2,
			GetScreenHeight() - padding - expNumbersSize,
			expNumbersSize - 2,
			expNumbersSize,
			YELLOW
		);

		DrawText(
			TextFormat("%d", nextLevel),
			GetScreenWidth() - padding - expNumbersSize + 2 + left2Padding,
			GetScreenHeight() - padding - expNumbersSize + left2Padding,
			22,
			BLACK);

		// Barra de vida fondo

		DrawRectangle(
			padding,
			padding,
			healthBarWidth,
			healthBarHeight,
			GRAY
		);

		// Barra de vida

		DrawRectangle(
			padding,
			padding,
			healthBarWidth * character->GetNormalizedHealth(),
			healthBarHeight,
			GREEN
		);

		// Barra de vida bordes

		DrawRectangleLines(
			padding,
			padding,
			healthBarWidth,
			healthBarHeight,
			GRAY
		);

		// Inventario

		for (int i = 0; i < character->GetInventorySize(); i++) {

			int marginTop = 5;
			int startX = padding + (i * itemSize) + (i * 5);

			// Cuadrado inventario

			DrawText(TextFormat("doors quantity %d", character->GetInventory()[i]), 100, 330, 16, WHITE);

			if (character->GetInventory()[i] > 0) {

				// TODO: Dibujar imagen de item
				Color color;
				if (character->GetInventory()[i] == I_POTION_HEALTH) {
					color = GREEN;
				}
				else if (character->GetInventory()[i] == I_POTION_STRENGTH) {
					color = ORANGE;
				}
				else if (character->GetInventory()[i] == I_POTION_SPEED) {
					color = BLUE;
				}
				else {
					color = YELLOW;
				}

				DrawRectangle(
					startX,
					padding + healthBarHeight + marginTop,
					itemSize,
					itemSize,
					color
				);

			}
			else {

				DrawRectangleLines(
					startX,
					padding + healthBarHeight + marginTop,
					itemSize,
					itemSize,
					GRAY
				);
			}

			// Numero tecla para usar inventario

			DrawText(
				TextFormat("%d", (i + 1)),
				startX + (itemSize / 3),
				padding + healthBarHeight + marginTop + itemSize + 4,
				12,
				GRAY
			);

		}

	}
}

void HUD::DrawPauseWidget()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.9f));

	int padding = 20;
	float h = 55.f;
	float y = 400.f;

	// TODO: Primero rojo,	luego verde,			luego azul
	// TODO: Primero mal,	luego que funcione,		luego refactor

	// Button 1 - Reanudar partida

	float y1 = y + (80 * 0);
	float opacity1 = 0.8f;
	Rectangle rect1 = Rectangle{ 200.f, y1, 220.f, h };
	if (CheckCollisionPointRec(GetMousePosition(), rect1)) {

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) pauseButtonPressed = 1;

	}

	DrawRectangleRec(rect1, Fade(WHITE, opacity1));
	DrawText("Reanudar partida", 200 + padding, y1 + padding, 20, BLACK);

	// Button 2 - Cargar Partida

	float y2 = y + (80 * 1);
	float opacity2 = 0.8f;
	Rectangle rect2 = Rectangle{ 200.f, y2, 200.f, h };
	if (CheckCollisionPointRec(GetMousePosition(), rect2)) {

		opacity2 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) pauseButtonPressed = 2;

	}

	DrawRectangleRec(rect2, Fade(WHITE, opacity2));
	DrawText("Cargar Partida", 200 + padding, y2 + padding, 20, BLACK);

	// Button 3 - Habilidades

	float y3 = y + (80 * 2);
	float opacity3 = 0.8f;
	Rectangle rect3 = Rectangle{ 200.f, y3, 150.f, h };
	if (CheckCollisionPointRec(GetMousePosition(), rect3)) {

		opacity3 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) pauseButtonPressed = 3;

	}

	DrawRectangleRec(rect3, Fade(WHITE, opacity3));
	DrawText("Habilidades", 200 + padding, y3 + padding, 20, BLACK);

	// Button 4 - Salir

	float y4 = y + (80 * 3);
	float opacity4 = 0.8f;
	Rectangle rect4 = Rectangle{ 200.f, y4, 90.f, h };
	if (CheckCollisionPointRec(GetMousePosition(), rect4)) {

		opacity4 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) pauseButtonPressed = 4;

	}

	DrawRectangleRec(rect4, Fade(WHITE, opacity4));
	DrawText("Salir", 200 + padding, y4 + padding, 20, BLACK);

}

void HUD::DrawHabilitiesWidget()
{
}

void HUD::DrawLoadDataWidget()
{
}

void HUD::DrawMainMenuWidget()
{
}

void HUD::ItemNumberPress(int num)
{
	for (int i = 0; i < character->GetInventorySize(); i++) {

		if (num == i + 1) {

			int marginTop = 5;
			int startX = padding + (i * itemSize) + (i * 5);

			// Cuadrado interaccion inventario

			DrawRectangle(
				startX,
				padding + healthBarHeight + marginTop,
				itemSize,
				itemSize,
				WHITE
			);

		}
	}
}

int HUD::GetPauseButtonPressed()
{
	return pauseButtonPressed;
}

void HUD::RestartPauseButtons()
{
	pauseButtonPressed = 0;
}
