#include "Interactable.h"

Interactable::Interactable() {}

Interactable::Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput, Texture2D textureInput)
{
	pos = posInput;
	type = typeInput;
	character = characterInput;
	texture = textureInput;
	rec = Rectangle{ pos.x,pos.y,textureSize.x, textureSize.y };
	center = Vector2{ (float)textureSize.x / 2.f, (float)textureSize.y / 2.f };
}

void Interactable::Restart()
{
	pos = initialPos;
	grabbed = false;
}

void Interactable::Draw()
{
	if (type == I_KEY) {

		Rectangle source = { 0.f, 0.f, textureSize.x, textureSize.y };
		Rectangle dest = { pos.x, pos.y, textureSize.x, textureSize.y };
		DrawTexturePro(texture, source, dest, center, 0.f, WHITE);

	}

	DetectGrab();

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