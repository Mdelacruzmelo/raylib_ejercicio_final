#pragma once
#include "raylib.h"
#include "Environment.h"
#include "EnvironmentUtils.h"

class Door
{
public:
	Door();
	Door(E_Side doorSideInput);

	void To(Door* doorTo);

private:

	E_Side doorSide;

};