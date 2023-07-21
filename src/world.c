#include <world.h>

world_t *world_create(size_t edge_size) {
    world_t *p_world = malloc(sizeof(world_t));

    p_world->edge_size = edge_size;
    p_world->world_size = edge_size * edge_size;
    p_world->buffer_size = p_world->world_size * 2;

    p_world->buffer = calloc(p_world->buffer_size, sizeof(bool));
    p_world->current = p_world->buffer;
    p_world->next = p_world->buffer + p_world->world_size;

    if (p_world == NULL || p_world->buffer == NULL) {
        logger(ERROR, "Failed to allocate memory for the world!");
    }

    return p_world;
}

bool world_get_cell(world_t *world, int x, int y, bool is_next) {
    if (x < 0 || x >= WORLD_SIZE) {
        return false;
    }

    if (y < 0 || y >= WORLD_SIZE) {
        return false;
    }

    return (is_next ? world->next : world->current)[y * WORLD_SIZE + x];
}

void world_set_cell(world_t *world, int x, int y, bool cell, bool is_next) {
    if (x < 0 || x >= WORLD_SIZE) {
        return;
    }

    if (y < 0 || y >= WORLD_SIZE) {
        return;
    }

    (is_next ? world->next : world->current)[y * WORLD_SIZE + x] = cell;
}

void world_destroy(world_t *world) {
    free(world->buffer);
    free(world);
}

size_t world_get_neighbours(world_t *world, int x, int y, bool is_next) {
    size_t count = 0;

    for (int y_off = -1; y_off <= 1; y_off++) {
        for (int x_off = -1; x_off <= 1; x_off++) {
            if (x_off == 0 && y_off == 0) {
                continue;
            }

            if (world_get_cell(world, x + x_off, y + y_off, is_next)) {
                count++;
            }
        }
    }

    return count;
}

void world_flip(world_t *world) {
    void *buf = world->current;
    world->current = world->next;
    world->next = buf;
}