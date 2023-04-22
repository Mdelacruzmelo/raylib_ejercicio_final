#pragma once
#include "raylib.h"

class Character
{
public:
	Character();

	void Draw();
	void Move(Vector2 movement);
	void Attack(Vector2 endVector);
	Rectangle GetRect();
	Vector2 GetSize();
	float GetAttackDistance();
	void SetIsInteracting(bool isInteractingInput);
	bool GetIsInteracting();
	bool GetIsTransporting();
	void SetIsTransporting(bool isTransportingInput);
	char* GetDoorTargetId();
	void SetDoorTargetId(char* doorTargetIdInput);
	void SetPosition(Vector2 newPos);
	Vector2 GetPosition();

private:

	float velocity = 1.f;
	float acceleration = 4.f;
	float size = 40.f;
	float radius = size / 2;
	float attackDistance = 70.f;
	Vector2 pos = { 600.f, 540.f };

	bool isInteracting = false;
	bool isTransporting = false;
	char* doorTargetId;

};
