#pragma once

#include <string>
#include <map>

class entity
{
public:
	entity(int w, int h, int x, int y, int clr[3]);

	int width;
	int height;

	int xPos;
	int yPos;

	std::string tag;

	int colour[3] = { 0,0,0 };

	bool visible = true;

};

