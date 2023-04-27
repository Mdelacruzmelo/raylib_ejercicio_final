#pragma once

enum E_AbilityType {
	ATTACK = 1,
	DEFENSE = 2,
	VELOCITY = 3,
	ENERGY = 4,
	ATTACK_DISTANCE = 5,
};

enum E_GameSlot {
	SLOT_1 = 1,
	SLOT_2 = 2,
	SLOT_3 = 3,
	SLOT_4 = 4,
};

enum E_Button {
	GO_BACK = 10,
	GO_FORWARD = 11,
};

struct SlotData {

	const char** slotPointers;
	int count;

};

struct SavedData {
	float attack;
	float defense;
	float speed;
	float energy;
	float attackdistance;
	float health;
	float shield;
	float experience;
	int level;
	int inventory1;
	int inventory2;
	int inventory3;
	int inventory4;
	int inventory5;
	int environment;
	float locationx;
	float locationy;
	int abPoints;
};

enum E_SavedDataKey {
	SAVED_ATTACK,
	SAVED_DEFENSE,
	SAVED_SPEED,
	SAVED_ENERGY,
	SAVED_ATTACK_DISTANCE,
	SAVED_HEALTH,
	SAVED_SHIELD,
	SAVED_EXPERIENCE,
	SAVED_LEVEL,
	SAVED_INVENTORY_1,
	SAVED_INVENTORY_2,
	SAVED_INVENTORY_3,
	SAVED_INVENTORY_4,
	SAVED_INVENTORY_5,
	SAVED_ENVIRONMENT,
	SAVED_LOCATION_X,
	SAVED_LOCATION_Y,
	SAVED_AB_POINTS,
};