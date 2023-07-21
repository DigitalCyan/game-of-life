//
// Created by DigitalCyan on 7/21/23.
//

#ifndef GAME_OF_LIFE_ENGINE_H
#define GAME_OF_LIFE_ENGINE_H

#include <config.h>
#include <logger.h>
#include <world.h>
#include <SDL2/SDL.h>

extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;
extern world_t *g_world;
extern bool g_quit;
extern bool g_paused;

int init();

void mainloop();

void tick();

void handle_events();

void update_world();

void draw();

void cleanup();

#endif //GAME_OF_LIFE_ENGINE_H
