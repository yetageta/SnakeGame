#include <cstdlib>
#include <iostream>

#include <SDL.h>
#undef main

#include "game.h"

// Positions
int foodPos[2] = { 0, 0 };
int headPos[2] = { 270, 270 };

// Colours
int red[3] = { 255, 0, 0 };
int blue[3] = { 6, 85, 209 };
int modified_blue[3] = { 6, 50, 209 };

int greenOne[3] = { 50, 168, 82 };
int greenTwo[3] = { 64, 189, 97 };

game* gameObj;

entity* foodObject;
entity* snakeHead;

direction dir = direction::NONE;

std::vector<entity*> snakeSegments;

bool gameRunning = true;

void generate_snake();
void restart();

void generate_food();

int main()
{
    SDL_Window* window = SDL_CreateWindow("A cool snake game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return -1;
    }


    SDL_Event event;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    // Game Init

    gameObj = new game(renderer);

    for (int i = 0; i <= 600; i += 30) {
        for (int v = 0; v <= 600; v += 30) {
            gameObj->add_entity(
                new entity(30, 30, i, v, (i % 60 == v % 60) ? greenOne : greenTwo)
            );
        }
    }

    foodObject = gameObj->add_entity(new entity(30, 30, 0, 0, red));
    foodObject->visible = false;

    generate_snake();
    generate_food();

    // Window Loop

    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }

            if (event.type == SDL_KEYUP) {
                direction tempDir = gameObj->inputManager->get_direction(&event.key);
                if (tempDir != direction::NONE) {
                    dir = tempDir;
                }

                if (event.key.keysym.scancode == SDL_SCANCODE_P) {
                    gameRunning = !gameRunning;
                }

                if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    restart();
                    continue;
                }
            }
        }

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime += (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Render game objects

        gameObj->render();

        // Render snake

        if (dir != direction::NONE && deltaTime >= 100 && gameRunning == true) {
            deltaTime = 0;

            if (dir == direction::UP) {
                snakeHead->yPos -= 30;
            }
            if (dir == direction::DOWN) {
                snakeHead->yPos += 30;
            }
            if (dir == direction::LEFT) {
                snakeHead->xPos -= 30;
            }
            if (dir == direction::RIGHT) {
                snakeHead->xPos += 30;
            }

            if (snakeHead->yPos < 0 || snakeHead->yPos >= 30 * 20) {
                restart();
                continue;
            }

            if (snakeHead->xPos < 0 || snakeHead->xPos >= 30 * 20) {
                restart();
                continue;
            }

            int lastPosition[2] = { 0, 0 };

            // Move each segment to the pos of the next segment before the psition change
            for (int i = snakeSegments.size() - 1; i >= 0; i--) {
                entity* &currentSegment = snakeSegments[i];

                if (i == 0) {
                    currentSegment->xPos = headPos[0];
                    currentSegment->yPos = headPos[1];
                }
                else {
                    entity* &previousSegment = snakeSegments[i - 1];

                    if (i == snakeSegments.size() - 1) {
                        lastPosition[0] = currentSegment->xPos;
                        lastPosition[1] = currentSegment->yPos;
                    }

                    currentSegment->xPos = previousSegment->xPos;
                    currentSegment->yPos = previousSegment->yPos;
                }

            }

            // Check if eating food
            if (snakeHead->xPos == foodPos[0] && snakeHead->yPos == foodPos[1]) {
                generate_food();
                snakeSegments.push_back(
                    gameObj->add_entity(
                        new entity(
                            30, 30, lastPosition[0], lastPosition[1], blue
                        ), "snake"
                    )
                );
            }

            // Check if touching self   
            for (const auto& segment : snakeSegments)
            {
                // Non head segments
                for (const auto& segment2 : snakeSegments)
                {
                    if (segment != segment2) {
                        if (segment->xPos == segment2->xPos
                            && segment->yPos == segment2->yPos) {
                            restart();
                            continue;
                        }
                    }
                }

                // Check if colliding with head
                if (segment->xPos == snakeHead->xPos
                    && segment->yPos == snakeHead->yPos) {
                    restart();
                    continue;
                }
            }

            headPos[0] = snakeHead->xPos;
            headPos[1] = snakeHead->yPos;
        }

        // Display
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void generate_food() {
    int x = (rand() % 19) * 30;
    int y = (rand() % 19) * 30;

    foodPos[0] = x;
    foodPos[1] = y;

    foodObject->xPos = x;
    foodObject->yPos = y;

    foodObject->visible = true;
}

void generate_snake() {
    delete snakeHead;

    snakeHead =
        gameObj->add_entity(
            new entity(
                30, 30, 270, 270, modified_blue
            ), "snake"
        );
    
    headPos[0] = snakeHead->xPos;
    headPos[1] = snakeHead->yPos;

    snakeSegments.push_back(
        gameObj->add_entity(
            new entity(
                30, 30, 270, 240, blue
            ), "snake"
        )
    );

    snakeSegments.push_back(
        gameObj->add_entity(
            new entity(
                30, 30, 270, 210, blue
            ), "snake"
        )
    );
}

void remove_snake_segments() {
    for (const auto& pair : gameObj->objects)
    {
        if (&pair != nullptr) {

            auto ent = pair.second;


            if (ent->tag == "snake") {
                gameObj->objects.erase(pair.first);
                remove_snake_segments();
                break;
            }
        }
    }
}

void restart() {
    dir = direction::NONE;

    snakeSegments.clear();
    remove_snake_segments();
    generate_snake();
}