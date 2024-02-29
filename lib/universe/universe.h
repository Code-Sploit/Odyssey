#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "universe/config.h"

#include <stdbool.h>

typedef struct UniversePosition
{
    double x;
    double y;
    double z;
} UniversePosition;

typedef struct Atom
{
    UniversePosition *position;

    int periodic_number;
    int max_binds;

    double u_mass;

    bool can_bind;
    bool is_isotope;

    int neutron_count;
    int proton_count;
    int electron_count;
} Atom;

typedef struct UniverseBlock
{
    Atom **atoms;

    bool do_render;
    bool is_full;

    int atom_count;

    double temperature;
} UniverseBlock;

typedef struct Universe
{
    UniverseBlock *blocks[(int) UNIVERSE_LENGTH][(int) UNIVERSE_WIDTH][(int) UNIVERSE_HEIGHT];

    int blocks_using;
} Universe;

UniverseBlock *universe_block_new(bool do_render, bool is_full, double temperature);
UniverseBlock *universe_block_new_random(bool do_render);
UniverseBlock *universe_get_block_by_position(Universe *universe, UniversePosition *position);

void universe_block_add_atom(UniverseBlock *block, Atom *atom);
void universe_block_del_atom_by_pos(UniverseBlock *block, UniversePosition *position);

Universe *universe_init();

void universe_destroy(Universe *universe);
void universe_block_destroy(UniverseBlock *block);

#endif