#include "Door.h"

Door::Door()
{
	doorSide = SIDE_LEFT;
	doorId = "door_A";
}

Door::Door(E_Side doorSideInput, char* doorIdInput)
{
	doorSide = doorSideInput;
	doorId = doorIdInput;
}

void Door::Draw(Character* characterInput)
{
	character = characterInput;

	static Texture2D door = LoadTexture("resources/textures/door.png");
	static Texture2D doorLocked = LoadTexture("resources/textures/door_locked.png");

	Rectangle source = { 0.f, 0.f, width, height };
	Rectangle dest = { pos.x + width / 2.f, pos.y + height / 2.f, width, height };

	if (locked) DrawTexturePro(doorLocked, source, dest, Vector2{ width / 2.f,height / 2.f }, rotation, WHITE);
	else DrawTexturePro(door, source, dest, Vector2{ width / 2.f, height / 2.f }, rotation, WHITE);

	if (showMessageLocked && locked) {

		counterMessageLocked += 1;

		Vector2 messagePos;
		if (doorSide == SIDE_TOP) messagePos = Vector2{ pos.x + width + 10.f, pos.y + height / 2 };
		else if (doorSide == SIDE_BOTTOM) messagePos = Vector2{ pos.x + width + 10.f, pos.y - 20.f };
		else if (doorSide == SIDE_RIGHT) messagePos = Vector2{ pos.x - 100.f, pos.y };
		else messagePos = Vector2{ pos.x + width + 10.f, pos.y - height / 2 };

		DrawText("Cerrado", messagePos.x, messagePos.y, 20, RED);

		if (counterMessageLocked >= 60) {

			showMessageLocked = false;
			counterMessageLocked = 0;

		}

	}

	// Detectar por ubicación del jugador si se intersecta con la puerta
	// Y detectar si el jugador está interactuando con la puerta

	if (
		CheckCollisionRecs(character->GetCollisionRect(), GetRect()) &&
		character->GetIsInteracting()
		) {

		if (locked) {

			if (character->HasKey() || character->GetIsUsingKey()) {
				character->UseKeyInventory();
				Unlock();

				static Sound openedSound = LoadSound("resources/sounds/door_opened.wav");
				PlaySound(openedSound);

				character->SetIsUsingKey(false);

			}
			else {

				showMessageLocked = true;
				static Sound lockedSound = LoadSound("resources/sounds/door_locked.wav");
				PlaySound(lockedSound);
			}

		}
		else {
			character->SetDoorTargetId(GetTargetId());
			character->SetIsTransporting(true);

			showMessageLocked = true;
			static Sound passSound = LoadSound("resources/sounds/door_passed.wav");
			PlaySound(passSound);
		}
	}
}

void Door::Draw(Character* characterInput, Vector2 posInput)
{
	pos = posInput;

	Draw(characterInput);
}

E_Side Door::GetDoorSide()
{
	return doorSide;
}

float Door::GetHeight()
{
	return height;
}

float Door::GetWidth()
{
	return width;
}

Rectangle Door::GetRect()
{
	return Rectangle{ pos.x, pos.y, width, height };
}

Vector2 Door::GetSize()
{
	return Vector2{ width, height };
}

char* Door::GetId()
{
	return doorId;
}

void Door::Lock()
{
	locked = true;
}

void Door::Unlock()
{
	locked = false;

	DrawText("UNLOCKING", 100, 150, 30, WHITE);

	/*if (character) {

		if (CheckCollisionRecs(character->GetRect(), GetRect())) {

			character->SetDoorTargetId(GetTargetId());
			character->SetIsTransporting(true);

		}

	}*/
}

bool Door::GetIsLocked()
{
	return locked;
}

void Door::Target(char* targetIdInput)
{
	doorTargetId = targetIdInput;
}

char* Door::GetTargetId()
{
	return doorTargetId;
}

Vector2 Door::GetPosition()
{
	return pos;
}

void Door::SetPosition(Vector2 newPos)
{
	pos = newPos;
}

void Door::SetRotation(float newRot)
{
	rotation = newRot;
}
