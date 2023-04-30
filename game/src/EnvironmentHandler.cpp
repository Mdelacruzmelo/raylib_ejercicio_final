#include "EnvironmentHandler.h"
#include <string>

EnvironmentHandler::EnvironmentHandler(Character* characterInput, AIController* aiControllerInput)
{
	character = characterInput;
	aiController = aiControllerInput;
}

void EnvironmentHandler::LoadDataFromCharacter() {

	ActivateEnvironment(character->GetLoadedEnvironment());
	UpdateDoors(character->GetLoadedDoorsData());

	aiController->ClearAll();

	character->SetIsLoadingData(false);

}

void EnvironmentHandler::Draw()
{
	Environment* envToDraw = nullptr;

	int envNumber = 0;

	for (int i = 0; i < quantity; i++) {

		if (envActivated != 0) {

			if (envActivated == i) {
				environments[i].Activate();
				envToDraw = &environments[i];
				envNumber = i;
			}
			else environments[i].Deactivate();

		}
		else if (environments[i].GetIsActivated()) {

			envToDraw = &environments[i];
			envNumber = i;

		}

	}

	if (envActivated != 0) envActivated = 0;

	// Set data for save

	character->SetEnvironment(envNumber);
	character->SetLoadedDoorsData(GetDoorsData());

	// Dibujar entorno

	if (envToDraw) envToDraw->Draw(character);
	else environments[0].Draw(character);

	// Dibujar puertas

	if (character->GetIsTransporting()) {

		// Recorro todos los environments
		for (int i = 0; i < quantity; i++) {

			Door* doorFound = nullptr;
			Vector2 endLocation = { 0.f, 0.f };

			// Recorro todas las puertas Top

			if (!doorFound) {
				for (int j = 0; j < environments[i].GetTopDoorQuantity(); j++) {

					Door* topDoorRef = &environments[i].GetTopDoors()[j];

					if (topDoorRef->GetId() == character->GetDoorTargetId()) {
						doorFound = topDoorRef;
						endLocation = Vector2{
							doorFound->GetPosition().x + (doorFound->GetSize().x / 2), // mitad H de la puerta
							doorFound->GetPosition().y + doorFound->GetSize().y + character->GetSize().y
						};
					}
				}
			}

			// Recorro todas las puertas Bottom

			if (!doorFound) {

				for (int j = 0; j < environments[i].GetBottomDoorQuantity(); j++) {

					Door* bottomDoorRef = &environments[i].GetBottomDoors()[j];

					if (bottomDoorRef->GetId() == character->GetDoorTargetId()) {
						doorFound = bottomDoorRef;
						endLocation = Vector2{
							doorFound->GetPosition().x + (doorFound->GetSize().x / 2), // mitad H de la puerta
							doorFound->GetPosition().y - character->GetSize().y - 5
						};
					}
				}
			}

			// Recorro todas las puertas Right

			if (!doorFound) {

				for (int j = 0; j < environments[i].GetRightDoorQuantity(); j++) {

					Door* rightDoorRef = &environments[i].GetRightDoors()[j];

					if (rightDoorRef->GetId() == character->GetDoorTargetId()) {
						doorFound = rightDoorRef;
						endLocation = Vector2{
							doorFound->GetPosition().x - character->GetSize().x - 5,
							doorFound->GetPosition().y + (doorFound->GetSize().y / 2) // mitad V de la puerta,
						};
					}
				}
			}

			// Recorro todas las puertas Left

			if (!doorFound) {

				for (int j = 0; j < environments[i].GetLeftDoorQuantity(); j++) {

					Door* leftDoorRef = &environments[i].GetLeftDoors()[j];

					if (leftDoorRef->GetId() == character->GetDoorTargetId()) {
						doorFound = leftDoorRef;
						endLocation = Vector2{
							doorFound->GetPosition().x + doorFound->GetSize().x + character->GetSize().x,
							doorFound->GetPosition().y + (doorFound->GetSize().y / 2) // mitad V de la puerta,
						};
					}
				}
			}

			if (doorFound) {

				if (aiController != nullptr) aiController->DeleteEnemies();

				environments[i].Activate();
				character->SetIsTransporting(false);
				character->SetIsInteracting(false);
				character->SetPosition(endLocation);
				character->SetDoorTargetId(nullptr);

			}
			else {
				environments[i].Deactivate();
			}

		}
	}

}

void EnvironmentHandler::Append(Environment* newEnvironment)
{
	int newQuantity = quantity + 1;

	Environment* newEnvs = new Environment[newQuantity];

	for (int i = 0; i < newQuantity; i++) {

		if (i < quantity) newEnvs[i] = environments[i];
		else newEnvs[i] = *newEnvironment;

	}

	quantity = newQuantity;
	environments = newEnvs;
}

void EnvironmentHandler::SetAIController(AIController* aiControllerInput)
{
	aiController = aiControllerInput;
}

void EnvironmentHandler::InitializeMap() // 1 Time executed, before BeginDrawing();
{
	// Environment 1

	Environment* env1 = new Environment(DARKGRAY);
	env1->Activate();
	env1->AddDoor(SIDE_RIGHT, "door_A");
	Append(env1);

	// Environment 2

	Environment* env2 = new Environment(DARKPURPLE);
	env2->AddDoor(SIDE_LEFT, "door_B");
	env2->AddDoor(SIDE_BOTTOM, "door_C");
	Append(env2);

	// Environment 3

	Environment* env3 = new Environment(BLACK);
	env3->AddDoor(SIDE_TOP, "door_D");
	Append(env3);

	// Connections

	env1->GetDoor("door_A")->Target("door_B");
	env2->GetDoor("door_B")->Target("door_A");
	env3->GetDoor("door_D")->Target("door_C");
	env2->GetDoor("door_C")->Target("door_D");

	// Doors locked

	// (float)env1->GetDoor("door_A")->Lock();

}

void EnvironmentHandler::ActivateEnvironment(int envIndex)
{

	if (envIndex < quantity) {

		for (int i = 0; i < quantity; i++) {

			if (i == envIndex) {
				environments[i].Activate();
				envActivated = envIndex;
			}
			else environments[i].Deactivate();

		}

	}

}

void EnvironmentHandler::UpdateDoors(char* doorsData) {

	const char* delimiter = ",";
	int* count = new int[0];
	const char** resultsPointers = TextSplit(doorsData, *delimiter, count);

	if (*count > 0) {

		for (int i = 0; i < *count; i++) {

			// Solo vamos de par en par, door_A,1,door_B,0,door_C,1... etc
			if (i == 0 || i % 2 == 0) {

				std::string doorIdStr = resultsPointers[i];
				char* doorId = new char[doorIdStr.length()];
				strcpy(doorId, doorIdStr.c_str());

				bool lock = std::stoi(std::string(resultsPointers[i + 1])) == 1;

				ToggleLockDoorById(doorId, lock);

			}

		}

	}

}

void EnvironmentHandler::Restart() {

	InitializeMap();
	character->SetIsInNewGame(false);

}

char* EnvironmentHandler::GetDoorsData()
{
	char* charDoorA = "door_A";
	std::string doorA = charDoorA;
	std::string lockedA = environments[0].GetDoor(charDoorA)->GetIsLocked() ? "1" : "0";
	char* charLockedA = new char[1];
	strcpy(charLockedA, lockedA.c_str());

	char* charDoorB = "door_B";
	std::string doorB = charDoorB;
	std::string lockedB = environments[1].GetDoor(charDoorB)->GetIsLocked() ? "1" : "0";
	char* charLockedB = new char[1];
	strcpy(charLockedB, lockedB.c_str());

	char* charDoorC = "door_C";
	std::string doorC = charDoorC;
	std::string lockedC = environments[1].GetDoor(charDoorC)->GetIsLocked() ? "1" : "0";
	char* charLockedC = new char[1];
	strcpy(charLockedC, lockedC.c_str());

	char* charDoorD = "door_D";
	std::string doorD = charDoorD;
	std::string lockedD = environments[2].GetDoor(charDoorD)->GetIsLocked() ? "1" : "0";
	char* charLockedD = new char[1];
	strcpy(charLockedD, lockedD.c_str());

	int totalDataLength =
		doorA.length() +
		doorB.length() +
		doorC.length() +
		doorD.length() +
		lockedA.length() +
		lockedB.length() +
		lockedC.length() +
		lockedD.length();

	int comasLength = totalDataLength - 1;
	char* dataToSave = new char[totalDataLength + comasLength];

	strcpy(dataToSave, charDoorA);
	strcat(dataToSave, ",");
	strcat(dataToSave, charLockedA);
	strcat(dataToSave, ",");
	strcat(dataToSave, charDoorB);
	strcat(dataToSave, ",");
	strcat(dataToSave, charLockedB);
	strcat(dataToSave, ",");
	strcat(dataToSave, charDoorC);
	strcat(dataToSave, ",");
	strcat(dataToSave, charLockedC);
	strcat(dataToSave, ",");
	strcat(dataToSave, charDoorD);
	strcat(dataToSave, ",");
	strcat(dataToSave, charLockedD);

	return dataToSave;

}

void EnvironmentHandler::ToggleLockDoorById(char* doorId, bool lock) {

	if (quantity > 0) {

		std::string doorA = "door_A";
		std::string doorB = "door_B";
		std::string doorC = "door_C";
		std::string doorD = "door_D";

		if (doorA.compare(doorId) == 0) {

			if (lock) environments[0].GetDoor("door_A")->Lock();
			else environments[0].GetDoor("door_A")->Unlock();

		}
		else if (doorB.compare(doorId) == 0) {

			if (lock) environments[1].GetDoor("door_B")->Lock();
			else environments[1].GetDoor("door_B")->Unlock();

		}
		else if (doorC.compare(doorId) == 0) {

			if (lock) environments[1].GetDoor("door_C")->Lock();
			else environments[1].GetDoor("door_C")->Unlock();

		}
		else if (doorD.compare(doorId) == 0) {

			if (lock) environments[2].GetDoor("door_D")->Lock();
			else environments[2].GetDoor("door_D")->Unlock();

		}

	}

}