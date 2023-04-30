#include "Consumable.h"

Consumable::Consumable()
{
}

Consumable::Consumable(E_ItemType typeInput, Character* characterInput, Vector2 loc)
{
	type = typeInput;
	character = characterInput;
	location = loc;

	// TODO: Dibujar imagen de item

	if (typeInput == I_POTION_HEALTH) color = GREEN;
	else if (typeInput == I_POTION_STRENGTH) color = ORANGE;
	else if (typeInput == I_POTION_SPEED) color = BLUE;
	else color = YELLOW;

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
		DrawRectangleRec(rec, color);
		DetectGrab();
	}
}
