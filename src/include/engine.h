//
// Created by DigitalCyan on 7/21/23.
//

#ifndef GAME_OF_LIFE_ENGINE_H
#define GAME_OF_LIFE_ENGINE_H

#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#include <config.h>
#include <logger.h>
#include <world.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    bool quit;
    bool paused;
    bool step;
    bool help_controls;
} game_state_t;

extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;
extern world_t *g_world;
extern world_t *g_world_save;
extern game_state_t g_state;

extern TTF_Font *g_font;

int init();

void mainloop();

void tick();

void handle_events();

void update_world();

void draw();

void cleanup();

void draw_text(char *text, int x, int y);

void draw_debug_ui();

#endif //GAME_OF_LIFE_ENGINE_H
