#include "EnvironmentHandler.h"
#include <string>

EnvironmentHandler::EnvironmentHandler(Character* characterInput)
{
	character = characterInput;
}

void EnvironmentHandler::Draw()
{
	Environment* envToDraw = nullptr;

	int envNumber = 0;

	if (character->GetIsLoadingEnvironment()) {

		ActivateEnvironment(character->GetLoadedEnvironment());
		character->SetIsLoadingEnvironment(false);

	}

	else {

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

		character->SetEnvironment(envNumber);

		if (envToDraw) envToDraw->Draw(character);
		else environments[0].Draw(character);

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

					DrawText(
						TextFormat("Vector Y: %f", doorFound->GetPosition().y),
						450,
						470,
						24,
						WHITE);
				}
				else {
					environments[i].Deactivate();
				}

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

void EnvironmentHandler::SetMap()
{
	if (isSettingEnvs || character->GetIsLoadingDoors()) {

		// Environment 1

		Environment* env1 = new Environment(DARKGRAY);
		// env1->Activate();
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

		if (character->GetIsLoadingDoors()) {

			const char* delimiter = ",";
			int* count = new int[0];
			const char** resultsPointers = TextSplit(character->GetLoadedDoorsData(), *delimiter, count);

			for (int i = 0; i < *count; i++) {

				// DrawText(resultsPointers[0], 100, 150, 30, WHITE);

				if (i == 0 || i % 2 == 0) { // Solo vamos de par en par

					int lock = std::stoi(std::string(resultsPointers[i + 1]));
					std::string doorA = "door_A";
					std::string doorB = "door_B";
					std::string doorC = "door_C";
					std::string doorD = "door_D";
					std::string doorData = resultsPointers[i];

					if (doorA.compare(doorData) == 0) {

						if (lock == 1) env1->GetDoor("door_A")->Lock();
						else env1->GetDoor("door_A")->Unlock();

					}

					if (doorB.compare(doorData) == 0) {

						if (lock == 1) env2->GetDoor("door_B")->Lock();
						else env2->GetDoor("door_B")->Unlock();

					}

					if (doorC.compare(doorData) == 0) {

						if (lock == 1) env2->GetDoor("door_C")->Lock();
						else env2->GetDoor("door_C")->Unlock();

					}

					if (doorD.compare(doorData) == 0) {

						if (lock == 1) env3->GetDoor("door_D")->Lock();
						else env3->GetDoor("door_D")->Unlock();

					}
				}

			}

			character->SetIsLoadingDoors(false);
			isSettingEnvs = false;

		}
		else {

			env1->GetDoor("door_A")->Lock();
			isSettingEnvs = false;

		}



	}
}

void EnvironmentHandler::ActivateEnvironment(int envIndex)
{

	if (
		envIndex > 0 &&
		envIndex < quantity &&
		envIndex != 0
		) {

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

	// DrawText(TextFormat("COUNT %d", *count), 100, 100, 30, WHITE);

	if (*count > 0) {

		for (int i = 0; i < *count; i++) {

			if (i == 0 || i % 2 == 0) { // Solo vamos de par en par

				// Me di una fumada con strcpy para convertir: const char*  --->  char *
				std::string doorIdStr = resultsPointers[i];
				char* doorId = new char[doorIdStr.length()]; // 6 --> "door_A"
				strcpy(doorId, doorIdStr.c_str());

				bool lock = std::stoi(std::string(resultsPointers[i + 1])) == 1;

				ToggleLockDoorById(doorId, lock);

			}

		}

	}

}

void EnvironmentHandler::ToggleLockDoorById(char* doorId, bool lock) {

	if (quantity > 0) {

		DrawText(doorId, 400, 400, 50, WHITE);

		for (int i = 0; i < quantity; i++) {

			if (environments[i].HasDoor(doorId)) {

				if (lock) environments[i].GetDoor(doorId)->Lock();
				else environments[i].GetDoor(doorId)->Unlock();

			}

		}
	}

}