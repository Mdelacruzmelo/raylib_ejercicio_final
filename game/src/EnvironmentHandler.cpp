#include "EnvironmentHandler.h"

EnvironmentHandler::EnvironmentHandler(Environment* environmentsInput, int size)
{
	quantity = size;
	Environment* envResult = new Environment[size];

	for (int i = 0; i < size; i++) {
		envResult[i] = environmentsInput[i];
	}

	environments = envResult;
}

void EnvironmentHandler::Draw()
{
	Environment* envToDraw = nullptr;

	for (int i = 0; i < quantity; i++) {
		if (environments[i].GetIsActivated()) {
			envToDraw = &environments[i];
		}
	}

	if (envToDraw) envToDraw->Draw();
	else environments[0].Draw();

}
