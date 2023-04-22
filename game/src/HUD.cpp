#include "HUD.h"

HUD::HUD(Character* characterInput)
{
	character = characterInput;
}

void HUD::Draw()
{
	if (character) {

		// Nivel actual 
		DrawRectangle(
			padding,
			GetScreenHeight() - padding - expNumbersSize,
			expNumbersSize - 2,
			expNumbersSize,
			YELLOW
		);

		int level = character->GetLevel();
		int nextLevel = level + 1;

		float left1Padding = expNumbersSize / 4;
		float left2Padding = expNumbersSize / 4;

		if (level == 1) left1Padding = expNumbersSize / 3;

		DrawText(
			TextFormat("%d", character->GetLevel()),
			padding + left1Padding,
			GetScreenHeight() - padding - expNumbersSize + (expNumbersSize / 4),
			22,
			BLACK);

		// Barra de experiencia fondo

		int experienceWidth = GetScreenWidth() - (padding * 2) - (expNumbersSize * 2);

		DrawRectangle(
			padding + expNumbersSize,
			GetScreenHeight() - padding - expBarHeight,
			experienceWidth,
			expBarHeight,
			GRAY
		);

		// Barra de experiencia

		DrawRectangle(
			padding + expNumbersSize,
			GetScreenHeight() - padding - expBarHeight,
			experienceWidth * character->GetNormalizedExperience(),
			expBarHeight,
			YELLOW
		);

		// Nivel siguiente

		DrawRectangle(
			GetScreenWidth() - padding - expNumbersSize + 2,
			GetScreenHeight() - padding - expNumbersSize,
			expNumbersSize - 2,
			expNumbersSize,
			YELLOW
		);

		DrawText(
			TextFormat("%d", nextLevel),
			GetScreenWidth() - padding - expNumbersSize + 2 + left2Padding,
			GetScreenHeight() - padding - expNumbersSize + left2Padding,
			22,
			BLACK);

		// Barra de vida fondo

		DrawRectangle(
			padding,
			padding,
			healthBarWidth,
			healthBarHeight,
			GRAY
		);

		// Barra de vida

		DrawRectangle(
			padding,
			padding,
			healthBarWidth * character->GetNormalizedHealth(),
			healthBarHeight,
			GREEN
		);

		// Barra de vida bordes

		DrawRectangleLines(
			padding,
			padding,
			healthBarWidth,
			healthBarHeight,
			GRAY
		);

		// Inventario

		for (int i = 0; i < inventorySize; i++) {

			int marginTop = 5;
			int startX = padding + (i * itemSize) + (i * 5);

			// Cuadrado inventario

			DrawRectangleLines(
				startX,
				padding + healthBarHeight + marginTop,
				itemSize,
				itemSize,
				GRAY
			);

			// Numero tecla para usar inventario

			DrawText(
				TextFormat("%d", (i + 1)),
				startX + (itemSize / 3),
				padding + healthBarHeight + marginTop + itemSize + 4,
				12,
				GRAY
			);

		}



	}
}

void HUD::ItemNumberPress(int num)
{
	for (int i = 0; i < inventorySize; i++) {

		if (num == i + 1) {

			int marginTop = 5;
			int startX = padding + (i * itemSize) + (i * 5);

			// Cuadrado interaccion inventario

			DrawRectangle(
				startX,
				padding + healthBarHeight + marginTop,
				itemSize,
				itemSize,
				WHITE
			);

		}
	}
}
