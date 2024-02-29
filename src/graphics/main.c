#include "graphics/callbacks.h"
#include "graphics/camera.h"
#include "graphics/containers.h"
#include "graphics/engine.h"
#include "graphics/print.h"
#include "graphics/render.h"
#include "graphics/utils.h"

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// Key callback function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Check if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // Close the window
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// Callback functions

int main(int argc, char **argv) {
    GraphicsEngine *engine = graphics_engine_init(error_callback, key_callback);

    if (!engine) {
        // Engine initialization failed
        printf("Failed to initialize engine\n");
        return -1;
    }

    if (graphics_engine_start(engine) == GRAPHICS_ENGINE_EXIT_FAILURE) {
        // Engine start failed
        printf("Failed to start engine\n");
        graphics_engine_close(engine);
        return -1;
    }

    GraphicsColor *color = graphics_color_new(0.0f, 0.0f, 1.0f);
    GraphicsColor *color2 = graphics_color_new(1.0f, 0.0f, 0.0f);
    GraphicsPosition *position = graphics_pos_new(0.0f, 0.0f, 0.0f);
    GraphicsPosition *position2 = graphics_pos_new(0.0f, 0.0f, 0.0f);
    GraphicsVelocity *velocity = graphics_velocity_new(0.0f, 0.0f, 0.1f);
    GraphicsVelocity *velocity2 = graphics_velocity_new(0.0f, 0.0f, -0.1f);
    GraphicsSphere *sphere = graphics_sphere_new(position, velocity, color, 0.2f, 60, 60);
    GraphicsSphere *sphere2 = graphics_sphere_new(position2, velocity2, color2, 0.2f, 60, 60);

    GraphicsLine *line = graphics_line_new(sphere->position, sphere2->position, graphics_color_new(0.0f, 1.0f, 0.0f), sphere, sphere2, GRAPHICS_OBJECT_SPHERE, GRAPHICS_OBJECT_SPHERE, true);

    graphics_engine_object_add(engine, sphere, GRAPHICS_OBJECT_SPHERE);
    graphics_engine_object_add(engine, sphere2, GRAPHICS_OBJECT_SPHERE);
    graphics_engine_object_add(engine, line, GRAPHICS_OBJECT_LINE);

    pthread_join(engine->render_thread, NULL);
    pthread_join(engine->velocity_thread, NULL);

    graphics_engine_close(engine);

    return 0;
}
