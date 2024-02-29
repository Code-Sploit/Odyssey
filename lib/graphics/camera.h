#ifndef CAMERA_H
#define CAMERA_H

#include "engine.h"

void graphics_engine_set_camera(GraphicsEngine *engine);
void graphics_engine_rotate_camera(GraphicsEngine *engine, float angle);
void graphics_engine_set_origin(GraphicsEngine *engine);

#endif