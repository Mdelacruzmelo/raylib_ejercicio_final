#include "Door.h"

Door::Door()
{
	// Por defecto la primera puerta a la izquierda si se construye sin parámetros
	// Cosa que posiblemente no ocurra, vamos a ver donde nos lleva el código

	doorSide = ENV_LEFT;
}

Door::Door(E_Side doorSideInput)
{
	doorSide = doorSideInput;
}

void Door::To(Door* doorTo) {

}
