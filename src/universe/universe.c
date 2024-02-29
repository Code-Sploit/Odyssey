#include "universe/universe.h"

#include <stdlib.h>

UniverseBlock *universe_block_new(bool do_render, bool is_full, double temperature)
{
    UniverseBlock *block = calloc(1, sizeof(UniverseBlock));

    if (!block)
    {
        return NULL;
    }

    block->do_render   = do_render;
    block->is_full     = is_full;
    block->temperature = temperature;

    block->atom_count = 0;
    
    block->atoms = calloc(1, sizeof(Atom *));

    return block;
}

UniverseBlock *universe_block_new_random(bool do_render)
{
    UniverseBlock *block = calloc(1, sizeof(UniverseBlock));

    if (!block)
    {
        return NULL;
    }

    block->do_render   = do_render;
    block->is_full     = false;

    // Yet to implement
    //block->temperature = universe_generate_random_temperature(UNIVERSE_TEMP_NORMAL_RANGE_START, UNIVERSE_TEMP_NORMAL_RANGE_END);

    //universe_generate_random_atom_spread(block);

    return block;
}

UniverseBlock *universe_get_block_by_position(Universe *universe, UniversePosition *position)
{
    /* Implement algorithm */

    UniverseBlock *block = calloc(1, sizeof(UniverseBlock));

    if (!block)
    {
        return NULL;
    }

    return block;
}

void universe_block_add_atom(UniverseBlock *block, Atom *atom)
{
    if (!block || !atom)
    {
        return;
    }

    block->atom_count++;

    block->atoms = realloc(block->atoms, block->atom_count * sizeof(Atom *));

    block->atoms[block->atom_count - 1] = atom;
}

void universe_block_del_atom_by_pos(UniverseBlock *block, UniversePosition *position)
{
    if (!block || !position)
    {
        return;
    }

    for (int i = 0; i < block->atom_count; i++)
    {
        Atom *atom = block->atoms[i];

        if (!atom)
        {
            continue;
        }

        if (atom->position == position)
        {
            block->atoms[i] = NULL;
        }
    }
}

Universe *universe_init()
{
    Universe *universe = calloc(1, sizeof(Universe));

    if (!universe)
    {
        return NULL;
    }

    for (int i = 0; i < (int) UNIVERSE_LENGTH; i++)
    {
        universe->blocks[i][0][0] = universe_block_new_random(true);

        for (int j = 0; j < (int) UNIVERSE_WIDTH; j++)
        {
            universe->blocks[i][j][0] = universe_block_new_random(true);

            for (int k = 0; k < (int) UNIVERSE_HEIGHT; k++)
            {
                universe->blocks[i][j][k] = universe_block_new_random(true);
            }
        }
    }

    universe->blocks_using = UNIVERSE_LENGTH * UNIVERSE_WIDTH * UNIVERSE_HEIGHT;

    return universe;
}

void universe_destroy(Universe *universe)
{
    if (!universe)
    {
        return;
    }

    free(universe);
}

void universe_block_destroy(UniverseBlock *block)
{
    if (!block)
    {
        return;
    }

    free(block);
}
