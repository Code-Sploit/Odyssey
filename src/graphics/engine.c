#include "graphics/engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Builtin debug function

char *CONVERT_DEBUG_TYPE(GraphicsEngineDebugType type)
{
    switch (type)
    {
        case GRAPHICS_ENGINE_DEBUG: { return "\033[0;32m"; }
        case GRAPHICS_ENGINE_WARN:  { return "\033[1;33m"; }
        case GRAPHICS_ENGINE_ERROR: { return "\033[0;31m"; }
    }

    return 0;
}

void DEBUG(GraphicsEngineDebugType type, const char *msg)
{
    printf("[ENGINE]: %s%s\033[0m\n", CONVERT_DEBUG_TYPE(type), msg);
}

// Allocate the main engine struct in memory and set pre-defined stuff

GraphicsEngine *graphics_engine_init(void *error_callback, void *key_callback)
{
    GraphicsEngine *engine = calloc(1, sizeof(GraphicsEngine));

    if (!engine)
    {
        return NULL;
    }

    engine->callback_count = ENGINE_CALLBACK_START;

    // Check if the error and key callback are valid pointers

    if (!error_callback || !key_callback)
    {
        DEBUG(GRAPHICS_ENGINE_WARN, "Error and/or Key callback(s) are NULL");

        return engine;
    }

    // Register error and key callback functions

    engine->error_callback = error_callback;
    engine->key_callback   = key_callback;

    // Set defaults

    engine->window.width  = ENGINE_DEFAULT_WIDTH;
    engine->window.height = ENGINE_DEFAULT_HEIGHT;
    engine->window.title  = ENGINE_DEFAULT_TITLE;

    engine->config.pre_matrix_mode  = ENGINE_DEFAULT_PRE_MATRIX_MODE;
    engine->config.post_matrix_mode = ENGINE_DEFAULT_POST_MATRIX_MODE;

    engine->camera.fovy             = ENGINE_DEFAULT_FOVY;
    engine->camera.aspect           = (GLfloat) engine->window.width / (GLfloat) engine->window.height;
    engine->camera.z_near           = ENGINE_DEFAULT_Z_NEAR;
    engine->camera.z_far            = ENGINE_DEFAULT_Z_FAR;

    // Set render job running to false because no rendering job has been started yet

    engine->render_job_is_running = false;

    // Allocate a dummy sphere

    engine->objects.spheres      = calloc(1, sizeof(GraphicsSphere *));
    engine->objects.sphere_count = 0;

    // Allocate a dummy line

    engine->objects.lines      = calloc(1, sizeof(GraphicsLine *));
    engine->objects.line_count = 0;

    // Set camera position

    engine->camera.x = ENGINE_DEFAULT_CAMERA_X;
    engine->camera.y = ENGINE_DEFAULT_CAMERA_Y;
    engine->camera.z = ENGINE_DEFAULT_CAMERA_Z;

    engine->camera.tx = ENGINE_DEFAULT_CAMERA_TARGET_X;
    engine->camera.ty = ENGINE_DEFAULT_CAMERA_TARGET_Y;
    engine->camera.tz = ENGINE_DEFAULT_CAMERA_TARGET_Z;

    engine->camera.x_isup = ENGINE_DEFAULT_CAMERA_ISUP_X;
    engine->camera.y_isup = ENGINE_DEFAULT_CAMERA_ISUP_Y;
    engine->camera.z_isup = ENGINE_DEFAULT_CAMERA_ISUP_Z;

    return engine;
}

// Deallocate the main engine struct in memory

void graphics_engine_close(GraphicsEngine *engine)
{
    if (!engine)
    {
        // Main struct is already not allocated

        return;
    }

    free(engine);
}

void graphics_engine_stop(GraphicsEngine *engine)
{
    if (!engine)
    {
        DEBUG(GRAPHICS_ENGINE_WARN, "Failed to stop graphics engine because of NULL object");

        return;
    }

    engine->render_job_is_running = false;
}

void graphics_velocity_set(GraphicsEngine *engine, void *object, GraphicsVelocity *velocity, GraphicsObjectType type)
{
    if (!engine || !object || !velocity)
    {
        return;
    }

    if (type == GRAPHICS_OBJECT_SPHERE)
    {
        GraphicsSphere *sphere = (GraphicsSphere *) object;

        if (!sphere)
        {
            return;
        }

        sphere->velocity = velocity;
    }
}

GraphicsPosition *graphics_velocity_calculate_new_position(GraphicsVelocity *velocity, GraphicsPosition *old_position, double delta)
{
    if (!velocity || !old_position)
    {
        return NULL;
    }

    GraphicsPosition *new_position = graphics_pos_new(0.0f, 0.0f, 0.0f);

    if (!new_position)
    {
        return NULL;
    }

    float new_x = old_position->x + (delta * velocity->x_speed);
    float new_y = old_position->y + (delta * velocity->y_speed);
    float new_z = old_position->z + (delta * velocity->z_speed);

    new_position->x = new_x;
    new_position->y = new_y;
    new_position->z = new_z;

    return new_position;
}

void *graphics_velocity_handler(void *arg)
{
    GraphicsEngine *engine = (GraphicsEngine *) arg;

    if (!engine)
    {
        pthread_exit(NULL);
    }

    while (engine->velocity_job_is_running)
    {
        GraphicsVelocity *velocity;
        GraphicsPosition *old_position;

        for (int i = 0; i < engine->objects.sphere_count; i++)
        {
            GraphicsSphere *sphere = engine->objects.spheres[i];

            if (!sphere)
            {
                pthread_exit(NULL);
            }

            velocity = sphere->velocity;
            old_position = sphere->position;

            sphere->position = graphics_velocity_calculate_new_position(velocity, old_position, 0.1f);
        }

        for (int i = 0; i < engine->objects.line_count; i++)
        {
            GraphicsLine *line = engine->objects.lines[i];

            if (!line)
            {
                pthread_exit(NULL);
            }

            if (line->is_linked)
            {
                GraphicsPosition *link_start_pos;
                GraphicsPosition *link_end_pos;

                if (line->link_start_type == GRAPHICS_OBJECT_SPHERE)
                {
                    GraphicsSphere *link_start = (GraphicsSphere *) line->link_start;
                    GraphicsSphere *link_end   = (GraphicsSphere *) line->link_end;

                    link_start_pos = link_start->position;
                    link_end_pos   = link_end->position;
                }

                line->start = link_start_pos;
                line->end   = link_end_pos;
            }
        }

        usleep(100000);
    }

    pthread_exit(NULL);
}

GraphicsEngineExitStatus graphics_engine_start(GraphicsEngine *engine)
{
    engine->render_job_is_running = true;

    if (pthread_create(&engine->render_thread, NULL, graphics_engine_render, engine) != 0)
    {
        printf("Error while starting renderer!\n");

        return GRAPHICS_ENGINE_EXIT_FAILURE;
    }

    engine->velocity_job_is_running = true;

    if (pthread_create(&engine->velocity_thread, NULL, graphics_velocity_handler, engine) != 0)
    {
        printf("Error while starting velocity!\n");

        return GRAPHICS_ENGINE_EXIT_FAILURE;
    }

    return GRAPHICS_ENGINE_EXIT_SUCCESS;
}

void graphics_engine_object_add(GraphicsEngine *engine, void *object, GraphicsObjectType type)
{
    if (!engine || !object)
    {
        return;
    }

    if (type == GRAPHICS_OBJECT_SPHERE)
    {
        engine->objects.sphere_count++;

        engine->objects.spheres = realloc(engine->objects.spheres, engine->objects.sphere_count * sizeof(GraphicsSphere *));

        engine->objects.spheres[engine->objects.sphere_count - 1] = (GraphicsSphere *) object;
    }
    else if (type == GRAPHICS_OBJECT_LINE)
    {
        engine->objects.line_count++;

        engine->objects.lines = realloc(engine->objects.lines, engine->objects.line_count * sizeof(GraphicsLine *));

        engine->objects.lines[engine->objects.line_count - 1] = (GraphicsLine *) object;
    }
    else
    {
        return;
    }
}