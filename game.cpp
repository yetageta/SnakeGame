#include "game.h"

void game::render() {
	// Set background colour
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Render all registered entities

	for (const auto& pair : objects)
	{
		auto ent = pair.second;

		if (!ent->visible)
			continue;

		SDL_Rect r{ ent->xPos, ent->yPos, ent->width, ent->height };

		SDL_SetRenderDrawColor(renderer, ent->colour[0], ent->colour[1], ent->colour[2], 255);

		SDL_RenderFillRect(renderer, &r);
	}
}

entity* game::add_entity(entity * ent) {
	auto it = objects.emplace(std::map<int, entity*>::value_type(objects.size() + 1, ent));
	auto x = it.first;

	return x->second;
}

entity* game::add_entity(entity * ent, std::string tag) {
	auto it = objects.emplace(std::map<int, entity*>::value_type(objects.size() + 1, ent));
	auto x = it.first;

	x->second->tag = tag;

	return x->second;
}