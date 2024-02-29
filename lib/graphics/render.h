#ifndef RENDER_H
#define RENDER_H

#include "engine.h"

void graphics_engine_draw_axises(GraphicsEngine *engine, float size);
void graphics_engine_render_sphere(GraphicsPosition *position, GraphicsColor *color, float radius, int slices, int stacks);
void graphics_engine_render_line(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color);
void *graphics_engine_render(void *__argument);

#endif