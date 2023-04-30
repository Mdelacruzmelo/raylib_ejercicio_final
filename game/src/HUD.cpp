#include "HUD.h"

HUD::HUD(Character* characterInput)
{
	character = characterInput;

	pillHealthTexture = LoadTexture("resources/textures/pill_health.png");
	pillSpeedTexture = LoadTexture("resources/textures/pill_speed.png");
	keyTexture = LoadTexture("resources/textures/key.png");
	police = LoadTexture("resources/textures/police_front.png");
	policeWin = LoadTexture("resources/textures/police_front_win.png");

	buttonHoverSound = LoadSound("resources/sounds/button_hover.wav");
	buttonClickedSound = LoadSound("resources/sounds/button_clicked.wav");
	buttonRemoveSound = LoadSound("resources/sounds/button_remove.wav");
	buttonDisabledSound = LoadSound("resources/sounds/button_disabled.wav");

	SetSoundVolume(buttonHoverSound, 0.2f);
	SetSoundVolume(buttonClickedSound, 0.2f);
	SetSoundVolume(buttonRemoveSound, 0.2f);
	SetSoundVolume(buttonDisabledSound, 0.2f);

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

			SoundHover(order);

			SetMouseCursor(4);

			if (abLevel > i) {
				DrawRectangleRec(rect, Fade(RED, 1.f));
				if (IsMouseButtonPressed(0)) {
					buttonPressed = abType * -1;
					PlaySound(buttonRemoveSound);
				}
			}
			else {
				DrawRectangleRec(rect, Fade(WHITE, 0.5f));

				if (IsMouseButtonPressed(0)) {

					buttonPressed = abType;

					if (character->GetAbPoints() > 0) PlaySound(buttonClickedSound);
					else PlaySound(buttonDisabledSound);

				}
			}

		}

		DrawRectangleLines(startX + addedWidth, y, squareSize, squareSize, GRAY);

	}

}

void HUD::SoundHover(int buttonNumber) {

	if (buttonNumberHovered != buttonNumber) {
		SetSoundVolume(buttonHoverSound, 0.6f);
		PlaySound(buttonHoverSound);
		buttonNumberHovered = buttonNumber;
	}
}

void HUD::SetLoadingTimes(float time, float maxTime)
{
	loadingTime = time;
	loadingMaxTime = maxTime;
}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, Color cButton, Color cText, bool outline) {

	float padding = 20.f;
	float opacity1 = 0.8f;

	if (CheckCollisionPointRec(GetMousePosition(), buttonRec)) {

		SoundHover(buttonNumber);

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) {
			buttonPressed = buttonNumber;
			PlaySound(buttonClickedSound);
		}

	}

	if (outline) {
		DrawRectangleLinesEx(buttonRec, 2.f, Fade(cButton, opacity1));
		DrawText(buttonText, buttonRec.x + padding, buttonRec.y + padding, 20, cButton);
	}
	else {
		DrawRectangleRec(buttonRec, Fade(cButton, opacity1));
		DrawText(buttonText, buttonRec.x + padding, buttonRec.y + padding, 20, cText);
	}

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, const char* buttonText, Color cButton, Color cText, bool outline) {

	float padding = 20.f;
	float opacity1 = 0.8f;

	if (CheckCollisionPointRec(GetMousePosition(), buttonRec)) {

		SoundHover(buttonNumber);

		opacity1 = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) {
			buttonPressed = buttonNumber;
			PlaySound(buttonClickedSound);
		}

	}

	if (outline) {
		DrawRectangleLinesEx(buttonRec, 2.f, Fade(cButton, opacity1));
		DrawText(buttonText, buttonRec.x + padding, buttonRec.y + padding, 20, cButton);
	}
	else {
		DrawRectangleRec(buttonRec, Fade(cButton, opacity1));
		DrawText(buttonText, buttonRec.x + padding, buttonRec.y + padding, 20, cText);
	}

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText) {

	DrawMenuButton(buttonRec, buttonNumber, buttonText, WHITE, BLACK, false);

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, const char* buttonText) {

	DrawMenuButton(buttonRec, buttonNumber, buttonText, WHITE, BLACK, false);

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, char* buttonText, bool outline) {

	DrawMenuButton(buttonRec, buttonNumber, buttonText, WHITE, BLACK, outline);

}

void HUD::DrawMenuButton(Rectangle buttonRec, int buttonNumber, const char* buttonText, bool outline) {

	DrawMenuButton(buttonRec, buttonNumber, buttonText, WHITE, BLACK, outline);

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

int HUD::ButtonPressed()
{
	return buttonPressed;
}

void HUD::RestartMainMenuButtons()
{
	buttonPressed = 0;
}

void HUD::DrawRemoveButton(Rectangle rec, int slotNumber, Color color)
{
	DrawLine(rec.x, rec.y, rec.x + rec.width, rec.y + rec.height, color);
	DrawLine(rec.x + rec.width, rec.y, rec.x, rec.y + rec.height, color);

	float removeOpacity = 0.2f;

	if (CheckCollisionPointRec(GetMousePosition(), rec)) {

		removeOpacity = 1.f;
		SetMouseCursor(4);

		if (IsMouseButtonPressed(0)) buttonPressed = slotNumber;

	}

}

bool HUD::GetInConfirmingModal() {

	return isConfirming;

}

void HUD::OpenConfirmModal(int buttonPressed, char* confirmQuestionInput) {

	isConfirming = true;
	yesConfirmButton = buttonPressed;
	confirmQuestion = confirmQuestionInput;
}

void HUD::CloseConfirmModal() {

	isConfirming = false;
	yesConfirmButton = 0;

}

bool HUD::IsSelectingSlot() {

	return ButtonPressed() == SLOT_1 ||
		ButtonPressed() == SLOT_2 ||
		ButtonPressed() == SLOT_3 ||
		ButtonPressed() == SLOT_4;

}

bool HUD::IsDeletingSlot() {

	return ButtonPressed() == -SLOT_1 ||
		ButtonPressed() == -SLOT_2 ||
		ButtonPressed() == -SLOT_3 ||
		ButtonPressed() == -SLOT_4;

}

void HUD::Notify(char* message) {

	notiAnimStart = true;
	showingNotification = true;
	notificationMessage = message;

}

void HUD::ShowNotification() {

	float notiWidth = (float)GetScreenWidth() / 2.f;
	float notiHeight = 110.f;
	float notiStartY = -10.f;
	static float notiY = notiStartY - notiHeight;
	float notiX = (float)GetScreenWidth() / 2.f - (notiWidth / 2.f);
	static float notiOpacity = 0.f;

	notificationCounter += (float)GetFrameTime();

	if (notiAnimStart) {

		notiY += ((float)GetFrameTime() * 300.f);
		notiOpacity += ((float)GetFrameTime() * 3.f);

		if (notiY >= notiStartY) {

			notiAnimStart = false;
			notificationCounter = 0.f;
		}

	}
	else if (notiAnimEnd) {

		notiY -= ((float)GetFrameTime() * 300.f);
		notiOpacity -= ((float)GetFrameTime() * 3.f);

		if (notiY <= notiStartY - notiHeight) {

			notificationCounter = 0.f;
			notiY = -10.f - notiHeight;
			notiOpacity = 0.f;
			notiAnimEnd = false;
			showingNotification = false;
		}

	}
	else if (showingNotification) {

		if (notificationCounter >= notificationCounterMax) {

			notificationCounter = 0.f;
			notiAnimEnd = true;

		}

	}

	Rectangle notiRec = { notiX, notiY, notiWidth, notiHeight };
	DrawRectangleRec(notiRec, Fade(CLITERAL(Color) { 30, 30, 30, 255 }, notiOpacity)); // BLACK

	if (!notiAnimStart && showingNotification && !notiAnimEnd) {

		float notiProgress = notiRec.width * (notificationCounter / notificationCounterMax);
		Rectangle notiRecBar = { notiRec.x, notiRec.y + 10.f, notiProgress, 5.f };
		DrawRectangleRec(notiRecBar, Fade(GRAY, notiOpacity));

		DrawText(notificationMessage, (int)notiRec.x + notiWidth / 10, (int)notiRec.y + notiHeight / 2, 24, Fade(WHITE, notiOpacity));
	}

}

void HUD::HideNotification() {

	notiAnimEnd = true;
	showingNotification = true;

}

void HUD::SetSlots(bool* slotsInput) {

	slots = slotsInput;

}

void HUD::SetSlotsQuantity(int slotsQuantityInput) {

	slotsQuantity = slotsQuantityInput;

}

void HUD::ShowConfirmHUD(char* message, int yesNumber, int noNumber) {

	float bWidth = (float)GetScreenWidth() / 5;
	float bHeight = 50.f;

	Rectangle rectNoButton = Rectangle{
		(float)GetScreenWidth() / 2 - (bWidth),
		(float)GetScreenHeight() / 2 - (bHeight / 2),
		bWidth,
		bHeight
	};
	DrawMenuButton(rectNoButton, noNumber, "No", true);

	Rectangle rectYesButton = Rectangle{
		(float)GetScreenWidth() / 2 + 20.f,
		(float)GetScreenHeight() / 2 - (bHeight / 2),
		bWidth,
		bHeight
	};
	DrawMenuButton(rectYesButton, yesNumber, "Si");

	DrawText(
		(message),
		bWidth + 20.f,
		(float)GetScreenHeight() / 2 - bHeight - 40.f,
		30,
		WHITE);

}

void HUD::ShowConfirmHUD(const char* message, int yesNumber, int noNumber) {

	float bWidth = (float)GetScreenWidth() / 5;
	float bHeight = 50.f;

	Rectangle rectNoButton = Rectangle{
		(float)GetScreenWidth() / 2 - (bWidth),
		(float)GetScreenHeight() / 2 - (bHeight / 2),
		bWidth,
		bHeight
	};
	DrawMenuButton(rectNoButton, noNumber, "No", true);

	Rectangle rectYesButton = Rectangle{
		(float)GetScreenWidth() / 2 + 20.f,
		(float)GetScreenHeight() / 2 - (bHeight / 2),
		bWidth,
		bHeight
	};
	DrawMenuButton(rectYesButton, yesNumber, "Si");

	DrawText(
		(message),
		bWidth + 20.f,
		(float)GetScreenHeight() / 2 - bHeight - 40.f,
		30,
		WHITE);

}

bool HUD::SlotAvailable() {

	for (int i = 0; i < slotsQuantity; i++) {

		if (slots[i]) return true;

	}

	return false;
}

// Widgets 

void HUD::Draw(E_TypeHUD typeHUDInput) {

	type = typeHUDInput;

	if (typeHUDInput == H_PAUSE) DrawPauseWidget();
	else if (typeHUDInput == H_ABILITIES || typeHUDInput == H_INIT_HABILITIES) DrawAbilitiesWidget(typeHUDInput);
	else if (typeHUDInput == H_MAIN_MENU) DrawMainMenuWidget();
	else if (typeHUDInput == H_SAVE_DATA) DrawSaveDataWidget();
	else if (typeHUDInput == H_LOAD_DATA || typeHUDInput == H_INIT_LOAD_DATA) DrawLoadDataWidget(typeHUDInput);
	else if (typeHUDInput == H_LOOSE_GAME) DrawLooseGameWidget();
	else if (typeHUDInput == H_WIN_GAME) DrawWinGameWidget();
	else if (typeHUDInput == H_LOADING_GAME) DrawLoadingGameWidget();
	else DrawGameWidget();

	if (showingNotification) ShowNotification();
}

void HUD::DrawMainMenuWidget()
{
	DrawbackgroundGradient();

	DrawText("The legend of Brenda", 100, GetScreenHeight() / 4, 50, RED);
	DrawText("- in the Maniac House -", 100, GetScreenHeight() / 4 + 70, 20, RED);

	Rectangle buttonRect1 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 80.f, 220.f, 55.f };
	DrawMenuButton(buttonRect1, NEW, "Nueva partida");

	Rectangle buttonRect2 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 160.f, 220.f, 55.f };
	DrawMenuButton(buttonRect2, SlotAvailable() ? LOAD : 0, "Cargar partida", SlotAvailable() ? false : true);

	Rectangle buttonRect3 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 240.f, 220.f, 55.f };
	DrawMenuButton(buttonRect3, QUIT, "Salir");

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

void HUD::DrawLooseGameWidget()
{
	DrawbackgroundGradient();

	DrawText("---- You loose ----", 100, GetScreenHeight() / 4, 50, RED);

	Rectangle buttonRect1 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 80.f, 220.f, 55.f };
	DrawMenuButton(buttonRect1, NEW, "Nueva partida");

	Rectangle buttonRect2 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 160.f, 220.f, 55.f };
	DrawMenuButton(buttonRect2, SlotAvailable() ? LOAD : 0, "Cargar partida", SlotAvailable() ? false : true);

	Rectangle buttonRect3 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 240.f, 220.f, 55.f };
	DrawMenuButton(buttonRect3, QUIT, "Salir");

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

void HUD::DrawSaveDataWidget() {

	DrawbackgroundGradient();

	if (isConfirming) ShowConfirmHUD(confirmQuestion, yesConfirmButton, GO_BACK);
	else {

		Rectangle rectBackButton = Rectangle{ 50.f, 50.f, 100.f, 55.f };
		DrawMenuButton(rectBackButton, GO_BACK, "Atras");

		float buttonWidth = (float)GetScreenWidth() / 3.f;
		float startX1 = (float)GetScreenWidth() / 3.f - buttonWidth / 1.8;

		float marginLeft = 40.f;
		float startX2 = (float)startX1 + buttonWidth + marginLeft;

		int row = 0;

		for (int nSlot = 1; nSlot <= slotsQuantity; nSlot++) {

			const char* textSlot = TextFormat("Slot %d", nSlot);

			if (nSlot % 2 != 0) {

				// Slots 1, 3

				Rectangle buttonRect1 = Rectangle{ startX1, (float)GetScreenHeight() / 4.f + (80.f + 100 * row), buttonWidth, 55.f };

				if (slots[nSlot - 1]) { // Slot exists

					DrawMenuButton(buttonRect1, (E_GameSlot)nSlot, textSlot);
					DrawRemoveButton(GetRectButtonRemove(buttonRect1), -(E_GameSlot)nSlot, BLACK);

				}
				else { // Slot NOT exists

					DrawMenuButton(buttonRect1, (E_GameSlot)nSlot, textSlot, true);

				}
			}
			else {

				// Slots 2, 4

				Rectangle buttonRect2 = Rectangle{ startX2, (float)GetScreenHeight() / 4.f + (80.f + 100 * row), buttonWidth, 55.f };

				if (slots[nSlot - 1]) { // Slot exists

					DrawMenuButton(buttonRect2, (E_GameSlot)nSlot, textSlot);
					DrawRemoveButton(GetRectButtonRemove(buttonRect2), -(E_GameSlot)nSlot, BLACK);

				}
				else { // Slot NOT exists

					DrawMenuButton(buttonRect2, (E_GameSlot)nSlot, textSlot, true);

				}

				row++;

			}

		}

	}

}

void HUD::DrawLoadDataWidget(E_TypeHUD typeHUDInput)
{
	DrawbackgroundGradient();

	if (showingNotification) ShowNotification();
	if (isConfirming) ShowConfirmHUD(confirmQuestion, yesConfirmButton, GO_BACK);
	else {

		Rectangle rectBackButton = Rectangle{ 50.f, 50.f, 100.f, 55.f };
		DrawMenuButton(rectBackButton, GO_BACK, "Atras");

		float buttonWidth = (float)GetScreenWidth() / 3.f;
		float startX1 = (float)GetScreenWidth() / 3.f - buttonWidth / 1.8;

		float marginLeft = 40.f;
		float startX2 = (float)startX1 + buttonWidth + marginLeft;

		int row = 0;

		for (int nSlot = 1; nSlot <= slotsQuantity; nSlot++) {

			const char* textSlot = TextFormat("Slot %d", nSlot);

			if (nSlot % 2 != 0) {

				// Slots 1, 3

				Rectangle buttonRect1 = Rectangle{ startX1, (float)GetScreenHeight() / 4.f + (80.f + 100 * row), buttonWidth, 55.f };

				if (slots[nSlot - 1]) { // Slot exists

					DrawMenuButton(buttonRect1, (E_GameSlot)nSlot, textSlot);
					DrawRemoveButton(GetRectButtonRemove(buttonRect1), -(E_GameSlot)nSlot, BLACK);

				}
				else { // Slot NOT exists

					DrawMenuButton(buttonRect1, 0, textSlot, true);

				}
			}
			else {

				// Slots 2, 4

				Rectangle buttonRect2 = Rectangle{ startX2, (float)GetScreenHeight() / 4.f + (80.f + 100 * row), buttonWidth, 55.f };

				if (slots[nSlot - 1]) { // Slot exists

					DrawMenuButton(buttonRect2, (E_GameSlot)nSlot, textSlot);
					DrawRemoveButton(GetRectButtonRemove(buttonRect2), -(E_GameSlot)nSlot, BLACK);

				}
				else { // Slot NOT exists

					DrawMenuButton(buttonRect2, 0, textSlot, true);

				}

				row++;

			}

		}

	}
}

void HUD::DrawLoadingGameWidget()
{
	DrawbackgroundGradient();

	loadingTime += GetFrameTime();
	float GrowAlpha = (float)(loadingTime / loadingMaxTime);
	float BarWidth = GetScreenWidth() * GrowAlpha;

	DrawRectangle(0, 0, (int)BarWidth, 30, WHITE);
	DrawText("Muevete con AWSD", 150, 110, 24, WHITE);
	DrawText("Dispara con click - tienes balas infinitas :)", 150, 150, 24, WHITE);
	DrawText("Tecla espacio para interactuar", 150, 190, 24, WHITE);
	DrawText("Coge pildoras y usalas con los numeros del 1 - 5 del inventario", 150, 230, 24, WHITE);
	DrawText("No mueras hasta llegar al nivel 5", 150, 490, 24, GREEN);
	DrawText("(Menu de pausa con la telca E)", 150, 530, 16, WHITE);

	Rectangle rectStart = Rectangle{
		(float)GetScreenWidth() - 200.f,
		(float)GetScreenHeight() - 100.f,
		125.f,
		50.f
	};
	DrawMenuButton(rectStart, GO_SKIP, "Empezar", YELLOW, BLACK, false);

}

void HUD::DrawWinGameWidget() {

	DrawbackgroundGradient();

	DrawText("---- You win ----", 100, GetScreenHeight() / 4, 50, GREEN);

	Rectangle buttonRect1 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 80.f, 220.f, 55.f };
	DrawMenuButton(buttonRect1, NEW, "Nueva partida");

	Rectangle buttonRect2 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 160.f, 220.f, 55.f };
	DrawMenuButton(buttonRect2, SlotAvailable() ? LOAD : 0, "Cargar partida", SlotAvailable() ? false : true);

	Rectangle buttonRect3 = Rectangle{ 200.f, (float)GetScreenHeight() / 3.f + 240.f, 220.f, 55.f };
	DrawMenuButton(buttonRect3, QUIT, "Salir");

	// Personaje

	float chaWidth = 200.f;
	float chaHeight = 200.f;
	int chaMTop = 30;
	Vector2 chaPos = {
		GetScreenWidth() * 2 / 4 - 70.f,
		(GetScreenHeight() / 2) - (chaHeight / 2) + chaMTop
	};
	DrawTextureEx(
		policeWin,
		Vector2{ chaPos.x - chaWidth / 2 + 20.f, chaPos.y - chaHeight / 2 + 20.f },
		0.f,
		1.5f,
		Fade(WHITE, 0.5f)
	);

}

void HUD::DrawBloodDamage() {

	hurtTimer += 1;

	if (hurtTimer > 0 && hurtTimer < 10) {
		hurtOpacity += 0.02f;
	}
	else if (hurtTimer >= 10 && hurtTimer < 30) {
		hurtOpacity -= 0.02f;
	}
	else {
		hurtTimer = 0;
		hurtOpacity = 0.f;
		character->SetIsJustHurt(false);
	}

	static int gradientWidth1 = 350;
	static int gradientWidth2 = 150;

	DrawRectangleGradientH(0, 0, gradientWidth1, GetScreenHeight(), Fade(RED, hurtOpacity), BLANK);
	DrawRectangleGradientH(GetScreenWidth() - gradientWidth1, 0, gradientWidth1, GetScreenHeight(), BLANK, Fade(RED, hurtOpacity));
	DrawRectangleGradientV(0, 0, GetScreenWidth(), gradientWidth1, Fade(RED, hurtOpacity), BLANK);
	DrawRectangleGradientV(0, GetScreenHeight() - gradientWidth1, GetScreenWidth(), gradientWidth1, BLANK, Fade(RED, hurtOpacity));

	DrawRectangleGradientH(0, 0, gradientWidth2, GetScreenHeight(), Fade(RED, hurtOpacity), BLANK);
	DrawRectangleGradientH(GetScreenWidth() - gradientWidth2, 0, gradientWidth2, GetScreenHeight(), BLANK, Fade(RED, hurtOpacity));
	DrawRectangleGradientV(0, 0, GetScreenWidth(), gradientWidth2, Fade(RED, hurtOpacity), BLANK);
	DrawRectangleGradientV(0, GetScreenHeight() - gradientWidth2, GetScreenWidth(), gradientWidth2, BLANK, Fade(RED, hurtOpacity));

}

void HUD::DrawGameWidget()
{
	if (character && character->GetIsAlive()) {

		if (character->GetIsJustHurt()) DrawBloodDamage();

		// Barra de experiencia Fondo negro

		DrawRectangle(
			0,
			GetScreenHeight() - 60,
			GetScreenWidth(),
			60,
			BLACK
		);

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

		// Barra de experiencia

		int experienceWidth = GetScreenWidth() - (padding * 2) - (expNumbersSize * 2);

		DrawRectangle(
			padding + expNumbersSize,
			GetScreenHeight() - padding - expBarHeight,
			experienceWidth,
			expBarHeight,
			Fade(YELLOW, 0.5f)
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

		DrawRectangleGradientH(
			padding,
			padding,
			healthBarWidth * character->GetNormalizedHealth(),
			healthBarHeight,
			CLITERAL(Color) {29, 116, 0, 255},
			CLITERAL(Color) {
			0, 255, 79, 255
		}
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

		DrawRectangleGradientH(
			padding,
			padding + healthBarHeight + 2,
			healthBarWidth * character->GetNormalizedShield(),
			healthBarHeight / 3,
			CLITERAL(Color) {0, 63, 100, 255},
			CLITERAL(Color) {
			0, 245, 255, 255
		}
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

				Texture2D textureToDraw;

				if (character->GetInventory()[i] == I_POTION_HEALTH)  textureToDraw = pillHealthTexture;
				else if (character->GetInventory()[i] == I_POTION_STRENGTH) textureToDraw = pillSpeedTexture;
				else if (character->GetInventory()[i] == I_POTION_SPEED) textureToDraw = pillSpeedTexture;
				else if (character->GetInventory()[i] == I_KEY) textureToDraw = keyTexture;
				else textureToDraw = pillHealthTexture;


				DrawTextureEx(textureToDraw, Vector2{ (float)startX, (float)padding + healthBarHeight + marginTop }, 0.f, 0.25f, WHITE);

				DrawRectangleLines(
					startX,
					padding + healthBarHeight + marginTop,
					itemSize,
					itemSize,
					GRAY
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

void HUD::DrawbackgroundGradient()
{
	static int rTimer = 0;

	if (rTimer >= 0 && rTimer < 30) rTimer += 1;
	else if (rTimer >= 30 && rTimer < 70) rTimer -= 1;
	else if (rTimer >= 70 && rTimer < 130) rTimer += 1;
	else rTimer = 0;

	unsigned char rTimerChar = static_cast<unsigned char>(rTimer);

	DrawRectangleGradientEx(
		Rectangle{ 0.f,0.f,(float)GetScreenWidth(),(float)GetScreenHeight() },
		CLITERAL(Color) {
		0, 7, 1, 255
	},
		CLITERAL(Color) {
		1, 38, 51, 255
	}, CLITERAL(Color) {
			0, 0, 12, 255
		}, CLITERAL(Color) {
			50, 1, 38, 255
		});
}

void HUD::DrawPauseWidget()
{
	DrawbackgroundGradient();

	for (int i = 1; i <= 5; i++) {

		Rectangle rect1 = Rectangle{ 200.f, 400.f + (80 * i), 220.f, 55.f };

		if (i == RESUME) DrawMenuButton(rect1, RESUME, "Reanudar partida");
		if (i == HABILITIES) DrawMenuButton(rect1, HABILITIES, "Habilidades");
		if (i == SAVE) DrawMenuButton(rect1, SAVE, "Guardar partida");
		if (i == LOAD) DrawMenuButton(rect1, LOAD, "Cargar partida");
		if (i == QUIT) DrawMenuButton(rect1, QUIT, "Salir");

	}

}

void HUD::DrawAbilitiesWidget(E_TypeHUD typeHUDInput)
{
	DrawbackgroundGradient();

	// Button 1 - Atrás

	Rectangle rectBackButton = Rectangle{ 50.f, 50.f, 100.f, 55.f };
	DrawMenuButton(rectBackButton, GO_BACK, "Atras");

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
	DrawTextureEx(
		police,
		Vector2{ chaPos.x - chaWidth / 2 + 20.f, chaPos.y - chaHeight / 2 + 20.f },
		0.f,
		1.f,
		WHITE
	);

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
	DrawText("Puntos de habilidad", abX, abY - abSize, abFontSize, YELLOW);

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
	DrawText("Nivel", expBarPos.x + 10, expBarPos.y + 5, 20, BLACK);

	int shortLevelNumY = expBarPos.y - expheight + 10;
	int shortLevelFSize = 12;
	DrawText(TextFormat("%d", character->GetLevel()), expBarPos.x, shortLevelNumY, shortLevelFSize, YELLOW);
	DrawText(TextFormat("%d", character->GetLevel() + 1), expBarPos.x + expWidth, shortLevelNumY, shortLevelFSize, YELLOW);


	if (typeHUDInput == H_INIT_HABILITIES) {

		// Boton empezar partida

		Rectangle rectStart = Rectangle{ (float)GetScreenWidth() - 200.f, (float)GetScreenHeight() - 100.f, 125.f, 50.f };
		DrawMenuButton(rectStart, GO_FORWARD, "Empezar", YELLOW, BLACK, false);

	}

}