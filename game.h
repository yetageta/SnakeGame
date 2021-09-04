#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <time.h>

#include "entity.h"
#include "Camera.h"
#include "input.h"

class game
{	
public:
	
	game(SDL_Renderer* rendr) {
		camera = new Camera(0,0);
		inputManager = new input();

		renderer = rendr;
	};

	entity* add_entity(entity * ent);
	entity* add_entity(entity * ent, std::string tag);

	void render();
	
	Camera* camera;
	input* inputManager;

	std::map<int, entity *> objects;
	std::vector<entity> objects2;

private:
	SDL_Renderer* renderer;
};

