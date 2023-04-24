#include "HUD.h"
#include "InventoryItemsUtils.h"
#include "AbilityUtils.h"

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

		// ----- DEBUG ABILITIES DRAW ------

		DrawText(
			TextFormat("Ataque: %f", character->GetAttack()),
			800,
			200,
			22,
			WHITE);

		DrawText(
			TextFormat("Defensa: %f", character->GetDefense()),
			800,
			240,
			22,
			WHITE);

		DrawText(
			TextFormat("Velocidad: %f", character->GetSpeed()),
			800,
			280,
			22,
			WHITE);

		DrawText(
			TextFormat("Energia: %f", character->GetEnergy()),
			800,
			320,
			22,
			WHITE);


		DrawText(
			TextFormat("Alcance: %f", character->GetAttackDistance()),
			800,
			360,
			22,
			WHITE);

	}
}

void HUD::DrawPauseWidget()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.9f));

	float padding = 20.f;
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

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.9f));

	float padding = 20.f;
	float h = 55.f;

	// Button 1 - Atrás

	float opacity1 = 0.8f;
	float yBack = 50.f;
	Rectangle rect1 = Rectangle{ 50.f, yBack, 100.f, h };

	if (CheckCollisionPointRec(GetMousePosition(), rect1)) {

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) habButtonPressed = 10;

	}

	DrawRectangleRec(rect1, Fade(WHITE, opacity1));
	DrawText("Atras", 50.f + padding, yBack + padding, 20, BLACK);

	// Botones de habilidades

	DrawAbButtons(ATTACK, 0);
	DrawAbButtons(DEFENSE, 1);
	DrawAbButtons(VELOCITY, 2);
	DrawAbButtons(ENERGY, 3);
	DrawAbButtons(ATTACK_DISTANCE, 4);

	// Personaje

	float chaWidth = 200.f;
	float chaHeight = 200.f;
	int chaMTop = 30;
	Vector2 chaPos = {
		GetScreenWidth() / 4 - 70.f,
		(GetScreenHeight() / 2) - (chaHeight / 2) + chaMTop
	};
	Rectangle rectCharacter = Rectangle{ chaPos.x, chaPos.y, chaWidth, chaHeight };
	DrawRectangleRec(rectCharacter, WHITE);

	// Puntos de habolidad

	int abFontSize = 30;
	int abPadding = 10;
	float abSize = abFontSize + (2 * abPadding);
	float abX = chaPos.x - 30;
	float abY = (GetScreenHeight() / 3);
	Rectangle rectAbPoints = Rectangle{ abX, abY, abSize, abSize };
	DrawRectangleRec(rectAbPoints, YELLOW);
	DrawText(
		TextFormat("%d", character->GetAbPoints()),
		abX + abPadding,
		abY + abPadding,
		30,
		BLACK
	);
	DrawText("Ability points", abX, abY - abSize, abFontSize, YELLOW);

	// Barra de experiencia

	int expMTop = 70;
	float expWidth = chaWidth + 60.f; // 30 a cada lado
	float expheight = 30.f;
	Vector2 expBarPos = { chaPos.x - (30), chaPos.y + chaHeight + expMTop };

	Rectangle rectTotalExp = Rectangle{
		expBarPos.x,
		expBarPos.y,
		expWidth,
		expheight
	};
	DrawRectangleRec(rectTotalExp, GRAY);

	Rectangle rectCurrentExp = Rectangle{
		expBarPos.x,
		expBarPos.y,
		expWidth * character->GetNormalizedExperience(),
		expheight
	};
	DrawRectangleRec(rectCurrentExp, YELLOW);
	DrawText("Level", expBarPos.x + 10, expBarPos.y + 5, 20, BLACK);

	int shortLevelNumY = expBarPos.y - expheight + 10;
	int shortLevelFSize = 12;
	DrawText(TextFormat("%d", character->GetLevel()), expBarPos.x, shortLevelNumY, shortLevelFSize, YELLOW);
	DrawText(TextFormat("%d", character->GetLevel() + 1), expBarPos.x + expWidth, shortLevelNumY, shortLevelFSize, YELLOW);

}

void HUD::DrawAbButtons(E_AbilityType abType, int order) {

	int marginLeft = 50;
	int startX = (GetScreenWidth() / 2) + marginLeft;
	int squareSize = 40;
	char* habilityName;

	if (abType == ATTACK) habilityName = "Ataque";
	else if (abType == DEFENSE) habilityName = "Defensa";
	else if (abType == VELOCITY) habilityName = "Velocidad";
	else if (abType == ENERGY) habilityName = "Energia";
	else habilityName = "Alcance";

	// de 300 hasta 900 --> total altura = 600

	int marginTop = 50;
	int hMax = 600;
	int centerY = GetScreenHeight() / 2;
	int y = (centerY - (hMax / 2)) + (120 * order) + marginTop;

	DrawText(
		habilityName,
		startX,
		y - squareSize,
		20,
		WHITE
	);

	for (int i = 0; i < 10; i++) {

		int addedWidth = squareSize * i;
		Rectangle rect = Rectangle{
			(float)(startX + addedWidth),
			(float)y,
			(float)squareSize,
			(float)squareSize
		};

		int abLevel = 0;

		if (abType == ATTACK) abLevel = character->GetAttack();
		if (abType == DEFENSE) abLevel = character->GetDefense();
		if (abType == VELOCITY) abLevel = character->GetSpeed();
		if (abType == ENERGY) abLevel = character->GetEnergy();
		if (abType == ATTACK_DISTANCE) abLevel = character->GetAttackDistance();

		if (abLevel > i) DrawRectangleRec(rect, GREEN);
		else DrawRectangleLinesEx(rect, 1.f, GRAY);

		if (CheckCollisionPointRec(GetMousePosition(), rect)) {

			SetMouseCursor(4);

			if (abLevel > i) {
				DrawRectangleRec(rect, Fade(RED, 1.f));
				if (IsMouseButtonPressed(0)) habButtonPressed = abType * -1;
			}
			else {
				DrawRectangleRec(rect, Fade(WHITE, 0.5f));
				if (IsMouseButtonPressed(0)) habButtonPressed = abType;
			}

		}

		DrawRectangleLines(startX + addedWidth, y, squareSize, squareSize, GRAY);

	}

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

int HUD::GetHabilityButtonPressed()
{
	return habButtonPressed;
}

void HUD::RestartHabilityButtons()
{
	habButtonPressed = 0;
}