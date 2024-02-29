#ifndef ATOM_H
#define ATOM_H

#include "universe/universe.h"

Atom *universe_atom_new(UniversePosition *position, int periodic_number, int max_binds,
                        double u_mass, bool can_bind, bool is_isotope,
                        int neutron_count, int proton_count, int electron_count);

void universe_atom_destroy(Atom *atom);

#endif