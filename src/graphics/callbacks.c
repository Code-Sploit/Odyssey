#include "graphics/engine.h"

#include <stdlib.h>
#include <stdio.h>

void *graphics_engine_callbacks(void *arg)
{
    GraphicsEngine *engine = (GraphicsEngine *) arg;

    if (!engine)
    {
        pthread_exit(NULL);
    }

    // TODO: Implement callbacks
}

// Add a callback function to the engine

void graphics_engine_add_callback(GraphicsEngine *engine, CallbackFunc callback)
{
    if (!engine || !callback)
    {
        // Either the engine or the function pointer is NULL

        return;
    }

    engine->callbacks[engine->callback_count] = callback;
    engine->callback_count++;
}

// Remove a callback function from the engine (testing)

void graphics_engine_del_callback(GraphicsEngine *engine, CallbackFunc callback)
{
    if (!engine || !callback)
    {
        // Either the engine or the function pointer is NULL

        return;
    }

    // Loop through all the pointers

    for (int i = 0; i < engine->callback_count; i++)
    {
        // Check if the pointer matches

        if (callback == engine->callbacks[i])
        {
            // Remove the callback

            engine->callbacks[i] = NULL;
        }
    }
}

void graphics_engine_handle_callbacks(GraphicsEngine *engine)
{
    if (!engine)
    {
        // Either the engine or the argument pointer is NULL

        return;
    }

    // Argument is going to be the engine itself everytime

    void *__argument = engine;

    // Loop through all the pointers

    for (int i = 0; i < engine->callback_count; i++)
    {
        // Check if it exists

        if (engine->callbacks[i])
        {
            // Call the function with the argument

            engine->callbacks[i](__argument);
        }
    }
}