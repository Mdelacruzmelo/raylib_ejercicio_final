#include "Consumable.h"

Consumable::Consumable()
{
}

Consumable::Consumable(E_ItemType typeInput, Character* characterInput, Vector2 loc, Texture2D textureInput)
{
	type = typeInput;
	character = characterInput;
	location = loc;

	if (typeInput == I_POTION_HEALTH) color = GREEN;
	else if (typeInput == I_POTION_STRENGTH) color = ORANGE;
	else if (typeInput == I_POTION_SPEED) color = BLUE;
	else color = YELLOW;

	texture = textureInput;

	rec = { location.x, location.y, size, size };
}

void Consumable::DetectGrab()
{
	if (character) {

		if (
			CheckCollisionRecs(character->GetCollisionRect(), rec) &&
			character->GetIsInteracting()
			) {

			if (character->IsInventorySpaceAvailable()) {

				character->AddToInventory(type);
				grabbed = true;

				static Sound soundKeys = LoadSound("resources/sounds/pill1.wav");
				SetSoundVolume(soundKeys, 0.5f);
				PlaySound(soundKeys);

			}
			else {
				character->ShowNoInventorySpace();
			}
		}
	}
}

bool Consumable::GetGrabbed()
{
	return grabbed;
}

void Consumable::SetGrabbed(bool grabbedInput)
{
	grabbed = grabbedInput;
}

void Consumable::SetCharacter(Character* characterInput)
{
	character = characterInput;
}

E_ItemType Consumable::GetType()
{
	return type;
}

Rectangle Consumable::GetRect()
{
	return rec;
}

void Consumable::Draw()
{
	if (!grabbed) {

		DrawTextureEx(texture, location, 0.f, 0.5f, WHITE);
		DetectGrab();

	}
}
