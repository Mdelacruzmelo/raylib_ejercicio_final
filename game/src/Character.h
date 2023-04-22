#pragma once
#include "raylib.h"

class Character
{
public:
	Character();

	float velocity = 1.f;
	float acceleration = 4.f;
	float size = 40.f;
	float radius = size / 2;
	float attackDistance = 70.f;
	Vector2 pos = { 600.f, 540.f };

	void Draw();
	void Move(Vector2 movement);
	void Attack(Vector2 endVector);
	Rectangle GetRect();
	void SetIsInteracting(bool isInteractingInput);
	bool GetIsInteracting();
	void TransportToDoor(char* doorTargetIdInput);
	bool GetIsTransporting();
	void SetIsTransporting(bool isTransportingInput);

private:

	bool isInteracting = false;
	bool isTransporting = false;
	char* doorTargetId;

};
