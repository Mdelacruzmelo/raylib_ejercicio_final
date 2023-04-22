#include "Character.h"

Character::Character()
{
}

void Character::Draw() {
	DrawRectangle(
		pos.x - radius,
		pos.y - radius,
		size,
		size,
		WHITE
	);
}

void Character::Move(Vector2 movement)
{
	pos = Vector2{
		pos.x + (velocity * acceleration * movement.x),
		pos.y + (velocity * acceleration * movement.y)
	};
}

void Character::Attack(Vector2 endVector) {

	Vector2 circle1Center = { (endVector.x + pos.x) / 2,(endVector.y + pos.y) / 2 };
	DrawCircle(circle1Center.x, circle1Center.y, 30.f, RED);

	Vector2 circle2Center = { endVector.x, endVector.y };
	DrawCircle(circle2Center.x, circle2Center.y, 20.f, RED);

	// Todo, mirar cuando se ataca, con qué intersectan los circulos para afectar al objetivo del ataque

}

Rectangle Character::GetRect()
{
	return Rectangle{ pos.x, pos.y, size, size };
}

void Character::SetIsInteracting(bool isInteractingInput)
{
	isInteracting = isInteractingInput;
}

bool Character::GetIsInteracting()
{
	return isInteracting;
}

void Character::TransportToDoor(char* doorTargetIdInput)
{
	isTransporting = true;
	doorTargetId = doorTargetIdInput;
}

bool Character::GetIsTransporting()
{
	return isTransporting;
}

void Character::SetIsTransporting(bool isTransportingInput)
{
	isTransporting = isTransportingInput;
}
