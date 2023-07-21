#include <engine.h>

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
world_t *g_world = NULL;
bool g_quit = false;
bool g_paused = false;

int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        logger(ERROR, "Failed to initialize SDL!");
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(
            WINDOW_SIZE,
            WINDOW_SIZE,
            0,
            &g_window,
            &g_renderer
    )) {
        logger(ERROR, "Failed to init window or renderer!");
        return 1;
    }

    SDL_SetWindowTitle(g_window, GAME_NAME);

    g_world = world_create(WORLD_SIZE);


    logger(INFO, "Window and renderer initialized");

    mainloop();

    cleanup();

    return 0;
}

void mainloop() {
    while (!g_quit) {
        tick();
        draw();
        SDL_Delay(THINK_DELAY);
    }
}

void tick() {
    handle_events();
    update_world();
}

void draw() {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);

    for (int y = 0; y < WORLD_SIZE; y++) {
        for (int x = 0; x < WORLD_SIZE; x++) {

            bool cell = world_get_cell(g_world, x, y, false);
            if (cell) {
                SDL_Rect rect = {
                        .x = x * CELL_SIZE,
                        .y = y * CELL_SIZE,
                        .w = CELL_SIZE,
                        .h = CELL_SIZE
                };

                SDL_RenderFillRect(g_renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(g_renderer);
}

void cleanup() {
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_renderer);
    world_destroy(g_world);
}

void handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            g_quit = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x / CELL_SIZE;
            int y = event.button.y / CELL_SIZE;

            bool isAlive = world_get_cell(g_world, x, y, false);
            world_set_cell(g_world, x, y, !isAlive, false);
        }

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                g_paused = !g_paused;
                if (g_paused) {
                    logger(INFO, "Simulation paused");
                } else {
                    logger(INFO, "Simulation unpaused");
                }
            }
        }
    }
}

void update_world() {
    if (g_paused) {
        return;
    }

    for (int y = 0; y < WORLD_SIZE; y++) {
        for (int x = 0; x < WORLD_SIZE; x++) {
            size_t count = world_get_neighbours(g_world, x, y, false);
            bool is_alive = world_get_cell(g_world, x, y, false);

            if (count < 2) {
                world_set_cell(g_world, x, y, false, true);
                continue;
            }

            if (count == 2) {
                world_set_cell(g_world, x, y, is_alive, true);
                continue;
            }

            if (count == 3) {
                world_set_cell(g_world, x, y, true, true);
                continue;
            }

            world_set_cell(g_world, x, y, false, true);
        }
    }

    world_flip(g_world);
}
