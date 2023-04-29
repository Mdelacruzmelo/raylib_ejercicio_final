#pragma once
#include <string>

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

enum E_PauseButton {
	RESUME = 1,
	HABILITIES = 2,
	SAVE = 3,
	LOAD = 4,
	QUIT = 5,
	NEW = 6,
};

enum E_TypeHUD {
	H_GAME,
	H_PAUSE,
	H_HABILITIES,
	H_INIT_HABILITIES,
	H_SAVE_DATA,
	H_LOAD_DATA,
	H_INIT_LOAD_DATA,
	H_MAIN_MENU,
	H_LOOSE_GAME,
	H_WIN_GAME,
};

enum E_ItemType {
	I_POTION_HEALTH = 1,
	I_POTION_STRENGTH = 2,
	I_POTION_SPEED = 3,
	I_EXPERIENCE = 4,
	I_KEY = 5,
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
	char* doorsData;
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
	SAVED_DOORS_DATA,
	SAVED_LOCATION_X,
	SAVED_LOCATION_Y,
	SAVED_AB_POINTS,
};

struct Converter {

	static char* FloatToChar(float dataValue) {

		std::string dataStr = std::to_string(dataValue);
		const char* constChar = dataStr.c_str();

		char* simpleChar = new char[strlen(constChar) + 1];
		strcpy(simpleChar, constChar);

		return simpleChar;

	}

	static char* IntToChar(int dataValue) {

		std::string dataStr = std::to_string(dataValue);
		const char* constChar = dataStr.c_str();

		char* simpleChar = new char[strlen(constChar) + 1];
		strcpy(simpleChar, constChar);

		return simpleChar;

	}


};