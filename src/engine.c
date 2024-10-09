#include <engine.h>

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
world_t *g_world = NULL;
world_t *g_world_save = NULL;
TTF_Font *g_font = NULL;
game_state_t g_state = {
        .paused = true,
        .quit = false,
        .step = false,
        .help_controls = false
};

extern char **environ;

int init() {
    char binary_path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", binary_path, sizeof(binary_path) - 1);
    char *working_dir = dirname(binary_path);
    char *font_path = strcat(working_dir, "/../assets/VT323-Regular.ttf");

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        logger(LOG_ERROR, "Failed to initialize SDL!");
        return 1;
    }

    g_window = SDL_CreateWindow(GAME_NAME, 0, 0, WINDOW_SIZE, WINDOW_SIZE, 0);
    if (g_window == NULL) {
        logger(LOG_ERROR, "Failed to create a window!");
        return 1;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_window == NULL) {
        logger(LOG_ERROR, "Failed to reate a renderer!");
        return 1;
    }

    logger(LOG_INFO, "Window and renderer initialized successfully");

    if (TTF_Init()) {
        logger(LOG_ERROR, "Failed to load init SDL2's TTF module!");
        return 1;
    }

    logger(LOG_INFO, "SDL2 True Typeface module initialized successfully");

    g_font = TTF_OpenFont(font_path, 20);

    if (g_font == NULL) {
        logger(LOG_ERROR, "Failed to load the engine font!");
        return 1;
    }

    logger(LOG_INFO, "Engine font loaded successfully");

    SDL_SetWindowTitle(g_window, GAME_NAME);

    g_world = world_create(WORLD_EDGE_SIZE);
    g_world_save = world_create(WORLD_EDGE_SIZE);

    if (g_world == NULL) {
        logger(LOG_ERROR, "Failed to allocate memory for the world!");
        return 1;
    }

    logger(LOG_SUCCESS, "Window and renderer initialized successfully");

    mainloop();

    cleanup();

    return 0;
}

void mainloop() {
    while (!g_state.quit) {
        tick();
        draw();
        SDL_Delay(THINK_DELAY);
    }
}

void tick() {
    handle_events();
    update_world();
}

void draw_text(char *text, int x, int y) {
    if (g_font == NULL) {
        logger(LOG_ERROR, "Failed to draw text, the font is NULL!");
        return;
    }

    SDL_Color white = {
            .r = 255,
            .g = 255,
            .b = 255,
            .a = 255,
    };

    SDL_Surface *surface = TTF_RenderText_Solid(g_font, text, white);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, surface);

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect rect = {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };

    SDL_RenderCopy(g_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void draw_debug_ui() {
    draw_text(GAME_NAME, 10, 10);
    draw_text(g_state.paused ? "The simulation is PAUSED" : "The simulation is RUNNING", 10, 30);
    draw_text("Press F1 to view controls.", 10, WORLD_EDGE_SIZE * CELL_SIZE - 30);

    if(g_state.help_controls) {
        draw_text("SPACE - PLAY/PAUSE", 10, WORLD_EDGE_SIZE * CELL_SIZE - 150);
        draw_text("  LMB - TOGGLE CELL", 10, WORLD_EDGE_SIZE * CELL_SIZE - 130);
        draw_text("    R - CLEAR", 10, WORLD_EDGE_SIZE * CELL_SIZE - 110);
        draw_text("    S - STEP", 10, WORLD_EDGE_SIZE * CELL_SIZE - 90);
        draw_text("   F6 - SAVE", 10, WORLD_EDGE_SIZE * CELL_SIZE - 70);
        draw_text("   F9 - LOAD", 10, WORLD_EDGE_SIZE * CELL_SIZE - 50);
    }
}

void draw() {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    for (int y = 0; y < WORLD_EDGE_SIZE; y++) {
        for (int x = 0; x < WORLD_EDGE_SIZE; x++) {

            bool cell = world_get_cell(g_world, x, y, false);
            if (cell) {
                SDL_Rect rect = {
                        .x = x * CELL_SIZE,
                        .y = y * CELL_SIZE,
                        .w = CELL_SIZE,
                        .h = CELL_SIZE
                };

                SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(g_renderer, &rect);
                SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
                SDL_RenderDrawRect(g_renderer, &rect);
            }
        }
    }

    draw_debug_ui();

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
            g_state.quit = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x / CELL_SIZE;
            int y = event.button.y / CELL_SIZE;

            bool isAlive = world_get_cell(g_world, x, y, false);
            world_set_cell(g_world, x, y, !isAlive, false);
        }

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                g_state.paused = !g_state.paused;
                if (g_state.paused) {
                    logger(LOG_INFO, "Simulation paused");
                } else {
                    logger(LOG_INFO, "Simulation running");
                }
            }

            if (event.key.keysym.sym == SDLK_r) {
                world_clear(g_world);
            }

            if (event.key.keysym.sym == SDLK_s) {
                g_state.step = true;
            }

            if (event.key.keysym.sym == SDLK_F6) {
                world_copy(g_world, g_world_save);
            }

            if (event.key.keysym.sym == SDLK_F9) {
                world_copy(g_world_save, g_world);
            }

            if (event.key.keysym.sym == SDLK_F1) {
                g_state.help_controls = !g_state.help_controls;
            }
        }
    }
}

void update_world() {
    if (g_state.paused && !g_state.step) {
        return;
    }

    if (g_state.step) {
        g_state.step = false;
    }

    for (int y = 0; y < WORLD_EDGE_SIZE; y++) {
        for (int x = 0; x < WORLD_EDGE_SIZE; x++) {
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
