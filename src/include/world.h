//
// Created by DigitalCyan on 7/21/23.
//

#ifndef GAME_OF_LIFE_WORLD_H
#define GAME_OF_LIFE_WORLD_H

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <logger.h>
#include <config.h>
#include <math.h>

typedef struct {
    bool *buffer;
    bool *current;
    bool *next;
    size_t edge_size;
    size_t world_size;
    size_t buffer_size;
} world_t;

world_t *world_create(size_t size);

bool world_get_cell(world_t *world, int x, int y, bool is_next);

void world_set_cell(world_t *world, int x, int y, bool cell, bool is_next);

size_t world_get_neighbours(world_t *world, int x, int y, bool is_next);

void world_destroy(world_t *world);

void world_flip(world_t *world);

void world_clear(world_t *world);

void world_copy(world_t *from, world_t *to);

#endif //GAME_OF_LIFE_WORLD_H
