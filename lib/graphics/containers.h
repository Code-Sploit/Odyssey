#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "engine.h"

GraphicsColor *graphics_color_new(double r, double g, double b);
GraphicsPosition *graphics_pos_new(double x, double y, double z);
GraphicsSphere *graphics_sphere_new(GraphicsPosition *position, GraphicsVelocity *velocity, GraphicsColor *color, double radius, int slices, int stacks);
GraphicsVelocity *graphics_velocity_new(double x, double y, double z);
GraphicsLine *graphics_line_new(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color, void *link_start, void *link_end, GraphicsObjectType link_start_type, GraphicsObjectType link_end_type, bool is_linked);

#endif