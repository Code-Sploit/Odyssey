#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "engine.h"

void *graphics_engine_callbacks(void *arg);
void graphics_engine_add_callback(GraphicsEngine *engine, CallbackFunc callback);
void graphics_engine_del_callback(GraphicsEngine *engine, CallbackFunc callback);
void graphics_engine_handle_callbacks(GraphicsEngine *engine);

#endif