#include "graphics/engine.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void graphics_engine_draw_axises(GraphicsEngine *engine, float size)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(engine->camera.tx,
                 engine->camera.ty,
                 engine->camera.tz);

    glBegin(GL_LINES);
    
    // X axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-size, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    
    // Y axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -size, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    
    // Z axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -size);
    glVertex3f(0.0f, 0.0f, size);
    
    glEnd();

    glPopMatrix();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL error: %d\n", error);
    }
}

void graphics_engine_render_sphere(GraphicsPosition *position, GraphicsColor *color, float radius, int slices, int stacks)
{
    //printf("Sphere [%d]: position=(%f, %f, %f) color=(%f, %f, %f) radius=%f slices=%d stacks=%d\n", 0, position->x, position->y, position->z, color->r, color->g, color->b, radius, slices, stacks);

    const float PI = 3.1415926f;
    const float TWO_PI = 2.0f * PI;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); // Push current matrix
    glTranslatef(position->x,
                 position->y,
                 position->z);

    glColor3f(color->r,
              color->g,
              color->b);

    //glBegin(GL_QUADS);

    int i, j;

    for (i = 0; i <= stacks; ++i) {
        double lat0 = PI * (-0.5 + (double) (i - 1) / stacks);

        double z0  = radius * sin(lat0);
        double zr0 = radius * cos(lat0);

        double lat1 = PI * (-0.5 + (double) i / stacks);

        double z1 = radius * sin(lat1);
        double zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= slices; ++j) {
            double lng = 2 * PI * (double) (j - 1) / slices;

            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }

        glEnd();
    }

    //glEnd();

    glPopMatrix(); // Restore previous matrix
}

void graphics_engine_render_line(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color)
{
    if (!start || !end || !color)
    {
        return;
    }

    printf("Rendering line: start=(%f, %f, %f) end=(%f, %f, %f) color=(%f, %f, %f)\n", start->x, start->y, start->z, end->x, end->y, end->z, color->r, color->g, color->b);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); // Push current matrix
    glTranslatef(0.0f,
                 0.0f,
                 0.0f);

    glBegin(GL_LINES);

    glColor3f(color->r,
             color->g,
             color->b);

    glVertex3f(start->x, start->y, start->z);
    glVertex3f(end->x, end->y, end->z);

    glEnd();

    glPopMatrix(); // Restore previous matrix
}

void *graphics_engine_render(void *__argument)
{
    GraphicsEngine *engine = (GraphicsEngine *) __argument;

    if (!engine)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to dereference __argument -> GraphicsEngine object");

        pthread_exit(NULL);
    }

    /* Initialize OpenGL again for same thread */

    int glfwInitializationStatus = glfwInit();

    if (!glfwInitializationStatus)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to initialize GLFW");

        pthread_exit(NULL);
    }

    glfwSetErrorCallback(engine->error_callback);
    
    engine->window.window = glfwCreateWindow(engine->window.width,
                                             engine->window.height,
                                             engine->window.title,
                                             NULL,
                                             NULL);

    if (!engine->window.window)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to initialize window");

        glfwTerminate();

        pthread_exit(NULL);
    }

    glfwMakeContextCurrent(engine->window.window);
    glfwSetKeyCallback(engine->window.window, engine->key_callback);

    GLenum error = glewInit();

    if (error != GLEW_OK)
    {
        DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to initialize GLEW");

        glfwTerminate();

        pthread_exit(NULL);
    }

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(engine->config.pre_matrix_mode);
    glLoadIdentity();
    gluPerspective(engine->camera.fovy,
                   engine->camera.aspect,
                   engine->camera.z_near,
                   engine->camera.z_far);

    glMatrixMode(engine->config.post_matrix_mode);
    glLoadIdentity();  

    graphics_engine_set_origin(engine);
    graphics_engine_set_camera(engine);
    graphics_engine_rotate_camera(engine, 45.0f);

    while (!glfwWindowShouldClose(engine->window.window) && engine->render_job_is_running)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //graphics_engine_draw_axises(engine, ENGINE_DEFAULT_AXIS_SIZE);

        for (int i = 0; i < engine->objects.sphere_count; i++)
        {
            GraphicsSphere *sphere = engine->objects.spheres[i];

            if (!sphere)
            {
                DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to get sphere object");

                pthread_exit(NULL);
            }

            graphics_engine_render_sphere(sphere->position,
                                          sphere->color,
                                          sphere->radius,
                                          sphere->slices,
                                          sphere->stacks);
        }

        for (int i = 0; i < engine->objects.line_count; i++)
        {
            GraphicsLine *line = engine->objects.lines[i];

            if (!line)
            {
                DEBUG(GRAPHICS_ENGINE_ERROR, "Failed to get line object");

                pthread_exit(NULL);
            }

            graphics_engine_render_line(line->start, line->end, line->color);
        }

        glfwSwapBuffers(engine->window.window);
        glfwPollEvents();
    }

    glfwTerminate();

    pthread_exit(NULL);
}