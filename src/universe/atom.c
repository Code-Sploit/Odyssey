#include "universe/universe.h"

#include <stdlib.h>

Atom *universe_atom_new(UniversePosition *position, int periodic_number, int max_binds,
                        double u_mass, bool can_bind, bool is_isotope,
                        int neutron_count, int proton_count, int electron_count)
{
    Atom *atom = calloc(1, sizeof(Atom));

    if (!atom)
    {
        return NULL;
    }

    atom->position = position;
    atom->periodic_number = periodic_number;
    atom->max_binds = max_binds;
    atom->u_mass = u_mass;
    atom->can_bind = can_bind;
    atom->is_isotope = is_isotope;
    atom->neutron_count = neutron_count;
    atom->proton_count = proton_count;
    atom->electron_count = electron_count;

    return atom;
}

void universe_atom_destroy(Atom *atom)
{
    if (!atom)
    {
        return;
    }

    free(atom);
}