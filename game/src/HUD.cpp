#include "HUD.h"
#include "InventoryItemsUtils.h"
#include "AbilityUtils.h"

HUD::HUD(Character* characterInput)
{
	character = characterInput;
}

void HUD::Draw(E_TypeHUD typeHUDInput) {

	type = typeHUDInput;

	if (typeHUDInput == H_PAUSE)
		DrawPauseWidget();

	else if (typeHUDInput == H_HABILITIES || typeHUDInput == H_INIT_HABILITIES)
		DrawAbilitiesWidget(typeHUDInput);

	else if (typeHUDInput == H_MAIN_MENU)
		DrawMainMenuWidget();

	else if (typeHUDInput == H_LOAD_DATA || typeHUDInput == H_INIT_LOAD_DATA)
		DrawLoadDataWidget(typeHUDInput);

	else DrawGameWidget();

}

void HUD::DrawGameWidget()
{
	if (character && character->GetIsAlive()) {

		// Nivel actual 
		DrawRectangle(
			padding,
			GetScreenHeight() - padding - expNumbersSize,
			expNumbersSize - 2,
			expNumbersSize,
			YELLOW
		);

		float left1Padding = expNumbersSize / 4;
		if (character->GetLevel() == 1) left1Padding = expNumbersSize / 3;

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

		float left2Padding = expNumbersSize / 4;

		DrawText(
			TextFormat("%d", character->GetLevel() + 1),
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

		// Barra de escudo fondo

		DrawRectangle(
			padding,
			padding + healthBarHeight + 2,
			healthBarWidth,
			healthBarHeight / 3,
			GRAY
		);

		// Barra de escudo

		DrawRectangle(
			padding,
			padding + healthBarHeight + 2,
			healthBarWidth * character->GetNormalizedShield(),
			healthBarHeight / 3,
			BLUE
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

			int marginTop = 20;
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
				else if (character->GetInventory()[i] == I_KEY) {
					color = YELLOW;
				}
				else {
					color = PURPLE;
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

		/*DrawText(
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
			WHITE);*/

	}
}

void HUD::DrawPauseWidget()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.9f));

	float padding = 20.f;
	float h = 55.f;
	float y = 400.f;

	// Button 1 - Reanudar partida

	float y1 = y + (80 * 0);
	float opacity1 = 0.8f;
	Rectangle rect1 = Rectangle{ 200.f, y1, 220.f, h };
	if (CheckCollisionPointRec(GetMousePosition(), rect1)) {

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = 1;

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

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = 2;

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

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = 3;

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

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = 4;

	}

	DrawRectangleRec(rect4, Fade(WHITE, opacity4));
	DrawText("Salir", 200 + padding, y4 + padding, 20, BLACK);

}

void HUD::DrawBackButton(int buttonNumber) {

	float padding = 20.f;
	float opacity1 = 0.8f;

	Rectangle rect1 = Rectangle{ 50.f, 50.f, 100.f, 55.f };

	if (CheckCollisionPointRec(GetMousePosition(), rect1)) {

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = buttonNumber;

	}

	DrawRectangleRec(rect1, Fade(WHITE, opacity1));
	DrawText("Atras", 50.f + padding, 50.f + padding, 20, BLACK);

}

void HUD::DrawAbilitiesWidget(E_TypeHUD typeHUDInput)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.9f));

	// Button 1 - Atrás

	DrawBackButton(10);

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


	if (typeHUDInput == H_INIT_HABILITIES) {

		// Boton empezar partida

		Rectangle rectStart = Rectangle{ (float)GetScreenWidth() - 200.f, (float)GetScreenHeight() - 100.f, 125.f, 50.f };
		DrawMenuButton(rectStart, 11, "Empezar");

	}

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
				if (IsMouseButtonPressed(0)) mainMenuButtonPressed = abType * -1;
			}
			else {
				DrawRectangleRec(rect, Fade(WHITE, 0.5f));
				if (IsMouseButtonPressed(0)) mainMenuButtonPressed = abType;
			}

		}

		DrawRectangleLines(startX + addedWidth, y, squareSize, squareSize, GRAY);

	}

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, Color cButton, Color cText) {

	float padding = 20.f;
	float opacity1 = 0.8f;

	if (CheckCollisionPointRec(GetMousePosition(), buttonRec)) {

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = buttonNumber;

	}

	DrawRectangleRec(buttonRec, Fade(WHITE, opacity1));
	DrawText(buttonText, buttonRec.x + padding, buttonRec.y + padding, 20, BLACK);

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText) {

	Color cText = BLACK;
	Color cButton = WHITE;

	DrawMenuButton(buttonRec, buttonNumber, buttonText, cButton, cText);

}

void HUD::DrawLoadDataWidget(E_TypeHUD typeHUDInput)
{
	// Botón atrás

	// DrawBackButton(10);

	Rectangle rectBackButton = Rectangle{ 50.f, 50.f, 100.f, 55.f };
	DrawMenuButton(rectBackButton, 10, "Atras");

	float buttonWidth = (float)GetScreenWidth() / 3.f;
	float startX1 = (float)GetScreenWidth() / 3.f - buttonWidth / 1.8;

	float marginLeft = 40.f;
	float startX2 = (float)startX1 + buttonWidth + marginLeft;

	// Slot 1

	Rectangle buttonRect1 = Rectangle{ startX1, (float)GetScreenHeight() / 4.f + 80.f, buttonWidth, 55.f };
	DrawMenuButton(buttonRect1, 20, "Slot 1");
	DrawRemoveButton(GetRectButtonRemove(buttonRect1), -20, BLACK);

	// Slot 2

	Rectangle buttonRect2 = Rectangle{ startX2, (float)GetScreenHeight() / 4.f + 80.f, buttonWidth, 55.f };
	DrawMenuButton(buttonRect2, 21, "Slot 2");
	DrawRemoveButton(GetRectButtonRemove(buttonRect2), -21, BLACK);

	// Slot 3

	Rectangle buttonRect3 = Rectangle{ startX1, (float)GetScreenHeight() / 4.f + 180.f, buttonWidth, 55.f };
	DrawMenuButton(buttonRect3, 22, "Slot 3");
	DrawRemoveButton(GetRectButtonRemove(buttonRect3), -22, BLACK);

	// Slot 3

	Rectangle buttonRect4 = Rectangle{ startX2, (float)GetScreenHeight() / 4.f + 180.f, buttonWidth, 55.f };
	DrawMenuButton(buttonRect4, 23, "Slot 4");
	DrawRemoveButton(GetRectButtonRemove(buttonRect4), -23, BLACK);

}

Rectangle HUD::GetRectButtonRemove(Rectangle rec) {

	float squareSize = rec.height - 20.f;

	return Rectangle{
			rec.x + rec.width - squareSize - 10.f,
			rec.y + 10.f,
			squareSize,
			squareSize
	};
}

void HUD::DrawMainMenuWidget()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	DrawText("The legend of Brenda", 100, GetScreenHeight() / 4, 50, RED);
	DrawText("- in the Maniac House -", 100, GetScreenHeight() / 4 + 70, 20, RED);

	Rectangle buttonRect1 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 80.f, 220.f, 55.f };
	DrawMenuButton(buttonRect1, 1, "Nueva partida");

	Rectangle buttonRect2 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 160.f, 220.f, 55.f };
	DrawMenuButton(buttonRect2, 2, "Cargar partida");

	Rectangle buttonRect3 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 240.f, 220.f, 55.f };
	DrawMenuButton(buttonRect3, 3, "Salir");

	// Sangre

	static float bloodLength1 = 1.f;
	bloodLength1 += 1.f;
	Rectangle bloodRec1 = Rectangle{ 120.f, ((float)GetScreenHeight() / 3.f - 10.f), 4.f, bloodLength1 };
	DrawRectangleRec(bloodRec1, RED);

	static float bloodLength2 = 1.f;
	bloodLength2 += 1.f;
	Rectangle bloodRec2 = Rectangle{ 375.f, ((float)GetScreenHeight() / 4.f + 20.f), 5.f, bloodLength2 };
	DrawRectangleRec(bloodRec2, RED);

	static float bloodLength3 = 0.f;
	bloodLength3 += 0.6f;
	Rectangle bloodRec3 = Rectangle{ 480.f, ((float)GetScreenHeight() / 4.f + 40.f), 10.f, bloodLength3 };
	DrawRectangleRec(bloodRec3, RED);

	static float bloodLength4 = 0.f;
	bloodLength4 += 0.3f;
	Rectangle bloodRec4 = Rectangle{ 160.f, ((float)GetScreenHeight() / 3.f - 10.f), 2.f, bloodLength4 };
	DrawRectangleRec(bloodRec4, RED);

	static float bloodLength5 = 0.f;
	bloodLength5 += 0.5f;
	Rectangle bloodRec5 = Rectangle{ 260.f, ((float)GetScreenHeight() / 3.f - 10.f), 2.f, bloodLength5 };
	DrawRectangleRec(bloodRec5, RED);

	static float bloodLength6 = 0.f;
	bloodLength6 += 0.2f;
	Rectangle bloodRec6 = Rectangle{ 560.f, ((float)GetScreenHeight() / 3.f - 10.f), 10.f, bloodLength6 };
	DrawRectangleRec(bloodRec6, RED);

	// Sangre Colision 1 - gota gruesa por los 3 botones

	Rectangle colRect1 = GetCollisionRec(bloodRec2, buttonRect1);
	Rectangle colRect1Modified = Rectangle{ colRect1.x - 6.f, colRect1.y, colRect1.width + 4.f, colRect1.height };
	DrawRectangleRec(colRect1Modified, RED);

	Rectangle colRect2 = GetCollisionRec(bloodRec2, buttonRect2);
	Rectangle colRect2Modified = Rectangle{ colRect2.x - 5.f, colRect2.y, colRect2.width + 5.f, colRect2.height };
	DrawRectangleRec(colRect2Modified, RED);

	Rectangle colRect3 = GetCollisionRec(bloodRec2, buttonRect3);
	Rectangle colRect3Modified = Rectangle{ colRect3.x - 4.f, colRect3.y, colRect3.width + 6.f, colRect3.height };
	DrawRectangleRec(colRect3Modified, RED);

	// Sangre Colision 2 - gota delgada por los 3 botones

	Rectangle colRect4 = GetCollisionRec(bloodRec5, buttonRect1);
	Rectangle colRect4Modified = Rectangle{ colRect4.x - 6.f, colRect4.y, colRect4.width + 4.f, colRect4.height };
	DrawRectangleRec(colRect4Modified, RED);

	Rectangle colRect5 = GetCollisionRec(bloodRec5, buttonRect2);
	Rectangle colRect5Modified = Rectangle{ colRect5.x - 5.f, colRect5.y, colRect5.width + 5.f, colRect5.height };
	DrawRectangleRec(colRect5Modified, RED);

	Rectangle colRect6 = GetCollisionRec(bloodRec5, buttonRect3);
	Rectangle colRect6Modified = Rectangle{ colRect6.x - 4.f, colRect6.y, colRect6.width + 6.f, colRect6.height };
	DrawRectangleRec(colRect6Modified, RED);

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

int HUD::GetMainMenuButtonPressed()
{
	return mainMenuButtonPressed;
}

void HUD::RestartMainMenuButtons()
{
	mainMenuButtonPressed = 0;
}


void HUD::DrawRemoveButton(Rectangle rec, int slotNumber, Color color)
{
	DrawLine(rec.x, rec.y, rec.x + rec.width, rec.y + rec.height, color);
	DrawLine(rec.x + rec.width, rec.y, rec.x, rec.y + rec.height, color);

	float removeOpacity = 0.2f;

	if (CheckCollisionPointRec(GetMousePosition(), rec)) {

		removeOpacity = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) mainMenuButtonPressed = slotNumber;

	}

}
