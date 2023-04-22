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

			bool correctEnvironment = false;

			// Recorro todas las puertas
			for (int j = 0; j < environments[i].GetDoorQuantity(); j++) {

				Door doorRef = environments[i].GetDoors()[j];

				// Si coincide el nombre unico de puerta, entonces vamos
				if (doorRef.GetId() == character->GetDoorTargetId()) {

					environments[i].Activate();
					character->SetPosition(doorRef.GetPosition());

					DrawText(
						TextFormat("Vector X: %f", doorRef.GetPosition().x),
						450,
						440,
						24,
						WHITE);

					DrawText(
						TextFormat("Vector Y: %f", doorRef.GetPosition().y),
						450,
						470,
						24,
						WHITE);
					// character->SetIsTransporting(false);
					// character->SetDoorTargetId(nullptr);

					correctEnvironment = true;

				}
			}

			// desactiva los entornos que no coincidan
			if (!correctEnvironment) environments[i].Deactivate();
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
