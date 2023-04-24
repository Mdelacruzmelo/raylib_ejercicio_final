#include "Interactable.h"

Interactable::Interactable()
{
}

Interactable::Interactable(Vector2 posInput, E_ItemType typeInput, Character* characterInput)
{
	pos = posInput;
	type = typeInput;
	character = characterInput;

	longPart = Rectangle{ pos.x, pos.y, longitude, 8.f };
	squarePart = Rectangle{ pos.x - squareSize, pos.y - (squareSize / 2), squareSize, squareSize };
	tooth1Part = Rectangle{ pos.x + 5.f, pos.y, 5.f, 12.f };
	tooth2Part = Rectangle{ pos.x + 15.f, pos.y, 5.f, 12.f };
	tooth3Part = Rectangle{ pos.x + 20.f, pos.y, 5.f, 12.f };
	round = Rectangle{
	   pos.x - squareSize - padding,
	   pos.y - (squareSize) - padding,
	   squareSize + (2 * padding) + longitude,
	   squareSize + (2 * padding) + longitude
	};
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

bool Interactable::GetGrabbed()
{
	return grabbed;
}