#include "graphics/engine.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void graphics_engine_set_camera(GraphicsEngine *engine)
{
    if (!engine)
    {
        return;
    }

    printf("Camera Parameters:\n");
    printf("Position: (%f, %f, %f)\n", engine->camera.x, engine->camera.y, engine->camera.z);
    printf("Target: (%f, %f, %f)\n", engine->camera.tx, engine->camera.ty, engine->camera.tz);
    printf("Up Vector: (%f, %f, %f)\n", engine->camera.x_isup, engine->camera.y_isup, engine->camera.z_isup);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(engine->camera.x, engine->camera.y, engine->camera.z,
              engine->camera.tx, engine->camera.ty, engine->camera.tz,
              engine->camera.x_isup, engine->camera.y_isup, engine->camera.z_isup);

    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Error!");
    }
}

void graphics_engine_rotate_camera(GraphicsEngine *engine, float angle)
{
    if (!engine)
    {
        return;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double radians = angle * (M_PI / 180.0);

    engine->camera.x = 5.0 * cos(radians);
    engine->camera.y = engine->camera.y;
    engine->camera.z = 5.0 * sin(radians);

    engine->camera.tx = 0.0f;
    engine->camera.ty = 0.0f;
    engine->camera.tz = 0.0f;

    gluLookAt(engine->camera.x, engine->camera.y, engine->camera.z,
              engine->camera.tx, engine->camera.ty, engine->camera.tz,
              engine->camera.x_isup, engine->camera.y_isup, engine->camera.z_isup);

    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Error!");
    }
}

void graphics_engine_set_origin(GraphicsEngine *engine)
{
    if (!engine)
    {
        return;
    }

    // TODO: Add custom settable origin point

    // Set the projection matrix
}