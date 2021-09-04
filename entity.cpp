#include "entity.h"

entity::entity(int w, int h, int x, int y, int clr[3]) {
	width = w;
	height = h;

	xPos = x;
	yPos = y;

	colour[0] = clr[0];
	colour[1] = clr[1];
	colour[2] = clr[2];
}