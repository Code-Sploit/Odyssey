#include "graphics/engine.h"

#include <stdlib.h>
#include <stdio.h>

GraphicsColor *graphics_color_new(double r, double g, double b)
{
    GraphicsColor *color = calloc(1, sizeof(GraphicsColor));

    if (!color)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to allocate graphicscolor");

        return NULL;
    }

    color->r = r;
    color->g = g;
    color->b = b;

    return color;
}

GraphicsPosition *graphics_pos_new(double x, double y, double z)
{
    GraphicsPosition *position = calloc(1, sizeof(GraphicsPosition));

    if (!position)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to allocate graphicsposition");

        return NULL;
    }

    position->x = x;
    position->y = y;
    position->z = z;

    return position;
}

GraphicsSphere *graphics_sphere_new(GraphicsPosition *position, GraphicsVelocity *velocity, GraphicsColor *color, double radius, int slices, int stacks)
{
    GraphicsSphere *sphere = calloc(1, sizeof(GraphicsSphere));

    if (!sphere)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to allocate sphere");
        
        return NULL;
    }

    sphere->position = position;
    sphere->velocity = velocity;
    sphere->color    = color;

    sphere->radius = radius;
    sphere->slices = slices;
    sphere->stacks = stacks;

    return sphere;
}

GraphicsVelocity *graphics_velocity_new(double x, double y, double z)
{
    GraphicsVelocity *velocity = calloc(1, sizeof(GraphicsVelocity));

    if (!velocity)
    {
        return NULL;
    }

    velocity->x_speed = x;
    velocity->y_speed = y;
    velocity->z_speed = z;

    return velocity;
}

GraphicsLine *graphics_line_new(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color, void *link_start, void *link_end, GraphicsObjectType link_start_type, GraphicsObjectType link_end_type, bool is_linked)
{
    GraphicsLine *line = calloc(1, sizeof(GraphicsLine));

    if (!line)
    {
        return NULL;
    }

    line->color = color;
    line->start = start;
    line->end   = end;

    if (is_linked)
    {
        if (!link_start || !link_end)
        {
            return NULL;
        }

        line->link_start = link_start;
        line->link_end   = link_end;
    }

    line->is_linked = is_linked;

    line->link_start_type = link_start_type;
    line->link_end_type   = link_end_type;

    return line;
}

GraphicsCube *graphics_cube_new(GraphicsPosition *position, GraphicsVelocity *velocity, GraphicsColor *color, float size)
{
    GraphicsCube *cube = calloc(1, sizeof(GraphicsCube));

    if (!cube)
    {
        return NULL;
    }

    cube->position = position;
    cube->velocity = velocity;
    cube->color    = color;
    cube->size     = size;

    return cube;
}