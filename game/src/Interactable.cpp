#include "Interactable.h"

Interactable::Interactable()
{
}

Interactable::Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput)
{
	pos = posInput;
	type = typeInput;
	character = characterInput;
}

void Interactable::Draw()
{
	if (type == I_KEY) {

		DrawRectangleRec(longPart, color);
		DrawRectangleLinesEx(squarePart, 2.f, color);
		DrawRectangleRec(tooth1Part, color);
		DrawRectangleRec(tooth2Part, color);
		DrawRectangleRec(tooth3Part, color);
		DrawRectangleLinesEx(round, 2.f, color);

	}

	DetectGrab();

}


void Interactable::DetectGrab()
{
	if (character && !grabbed) {
		if (
			CheckCollisionRecs(character->GetRect(), round) &&
			character->GetIsInteracting()
			) {
			character->AddToInventory(type);
			grabbed = true;
		}
	}
}