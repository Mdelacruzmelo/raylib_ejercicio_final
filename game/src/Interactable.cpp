#include "Interactable.h"

Interactable::Interactable() {}

Interactable::Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput, Texture2D textureInput)
{
	pos = posInput;
	type = typeInput;
	character = characterInput;
	texture = textureInput;
	rec = Rectangle{ pos.x,pos.y,textureSize.x, textureSize.y };
}

void Interactable::Restart()
{
	pos = initialPos;
	grabbed = false;
}

void Interactable::Draw()
{
	if (!grabbed) {
		DrawTextureEx(texture, pos, 0.f, 0.5f, WHITE);
		DetectGrab();
	}
}


void Interactable::DetectGrab()
{
	if (character && !grabbed) {
		if (
			CheckCollisionRecs(character->GetCollisionRect(), rec) &&
			character->GetIsInteracting()
			) {

			if (character->IsInventorySpaceAvailable()) {

				character->AddToInventory(type);
				grabbed = true;

				static Sound soundKeys = LoadSound("resources/sounds/keys.wav");
				SetSoundVolume(soundKeys, 2.f);
				PlaySound(soundKeys);

			}
			else {
				character->ShowNoInventorySpace();
			}
		}
	}
}

bool Interactable::GetIsGrabbed()
{
	return grabbed;
}