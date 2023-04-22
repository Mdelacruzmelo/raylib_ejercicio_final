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

	// DrawText(TextFormat("envs quantity %d", quantity), 100, 300, 16, WHITE);

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