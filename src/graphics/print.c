#include "graphics/engine.h"

#include <stdlib.h>
#include <stdio.h>

void graphics_engine_print(GraphicsEngine *engine)
{
    if (!engine)
    {
        return;
    }

    printf("Render Job Running: %d\n", engine->render_job_is_running);
    printf("Window->width=%f\n", engine->window.width);
    printf("Window->height=%f\n", engine->window.height);
    printf("Window->title=`%s`\n", engine->window.title);
    printf("Config->pre_matrix_mode=%d\n", engine->config.pre_matrix_mode);
    printf("Config->post_matrix_mode=%d\n", engine->config.post_matrix_mode);
    printf("Camera->fovy=%f\n", engine->camera.fovy);
    printf("Camera->aspect=%f\n", engine->camera.aspect);
    printf("Camera->z_near=%f\n", engine->camera.z_near);
    printf("Camera->z_far=%f\n", engine->camera.z_far);

    for (int i = 0; i < engine->objects.sphere_count; i++)
    {
        GraphicsSphere *sphere = engine->objects.spheres[i];

        printf("Sphere [%d]: position=(%f, %f, %f) color=(%f, %f, %f) radius=%f slices=%d stacks=%d\n", i, sphere->position->x, sphere->position->y, sphere->position->z, sphere->color->r, sphere->color->g, sphere->color->b, sphere->radius, sphere->slices, sphere->stacks);
    }
}