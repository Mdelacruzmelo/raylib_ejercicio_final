#include "EnvironmentHandler.h"

EnvironmentHandler::EnvironmentHandler(Character* characterInput)
{
	character = characterInput;
}

void EnvironmentHandler::Draw()
{
	Environment* envToDraw = nullptr;

	for (int i = 0; i < quantity; i++) {
		if (environments[i].GetIsActivated()) {
			envToDraw = &environments[i];
		}
	}

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
	// TODO: Si me alcanza el tiempo, me encantaría hacer esto procedural

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
	env1->GetDoor("door_A")->Lock();
	env2->GetDoor("door_B")->Target("door_A");
	env3->GetDoor("door_D")->Target("door_C");
	env2->GetDoor("door_C")->Target("door_D");
}