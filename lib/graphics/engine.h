#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>
#include <pthread.h>

// Constants

#define MAX_CALLBACK_FUNCTIONS 25

#define ENGINE_CALLBACK_START 0

#define ENGINE_DEFAULT_WIDTH            1920
#define ENGINE_DEFAULT_HEIGHT           1080
#define ENGINE_DEFAULT_TITLE            "Graphics Engine (v1.0)"
#define ENGINE_DEFAULT_PRE_MATRIX_MODE  GL_PROJECTION
#define ENGINE_DEFAULT_POST_MATRIX_MODE GL_MODELVIEW
#define ENGINE_DEFAULT_FOVY             90.0f
#define ENGINE_DEFAULT_Z_NEAR           0.01f
#define ENGINE_DEFAULT_Z_FAR            100.0f

#define ENGINE_DEFAULT_AXIS_SIZE 10.0f

#define ENGINE_DEFAULT_CAMERA_X         0.0f
#define ENGINE_DEFAULT_CAMERA_Y         3.0f
#define ENGINE_DEFAULT_CAMERA_Z         5.0f

#define ENGINE_DEFAULT_CAMERA_TARGET_X         0.0f
#define ENGINE_DEFAULT_CAMERA_TARGET_Y         0.0f
#define ENGINE_DEFAULT_CAMERA_TARGET_Z         0.0f

#define ENGINE_DEFAULT_CAMERA_ISUP_X           0.0f
#define ENGINE_DEFAULT_CAMERA_ISUP_Y           1.0f
#define ENGINE_DEFAULT_CAMERA_ISUP_Z           0.0f

// Error codes
typedef enum GraphicsEngineDebugType
{
    GRAPHICS_ENGINE_DEBUG,
    GRAPHICS_ENGINE_WARN,
    GRAPHICS_ENGINE_ERROR
} GraphicsEngineDebugType;

// Return types
typedef enum GraphicsEngineExitStatus
{
    GRAPHICS_ENGINE_EXIT_FAILURE,
    GRAPHICS_ENGINE_EXIT_SUCCESS
} GraphicsEngineExitStatus;

// Declare DEBUG function
void DEBUG(GraphicsEngineDebugType type, const char *msg);

// Structure for a position

typedef struct GraphicsPosition
{
    double x;
    double y;
    double z;
} GraphicsPosition;

GraphicsPosition *graphics_pos_new(double x, double y, double z);

// Structure for a color

typedef struct GraphicsColor
{
    double r;
    double g;
    double b;
} GraphicsColor;

// Structure for velocity

typedef struct GraphicsVelocity
{
    double x_speed;
    double y_speed;
    double z_speed;
} GraphicsVelocity;

GraphicsVelocity *graphics_velocity_new(double x, double y, double z);

// Structure for a Sphere

typedef struct GraphicsSphere
{
    GraphicsPosition *position;
    GraphicsVelocity *velocity;

    GraphicsColor *color;

    double radius;

    int slices;
    int stacks;
} GraphicsSphere;

typedef enum GraphicsObjectType
{
    GRAPHICS_OBJECT_SPHERE,
    GRAPHICS_OBJECT_LINE,
    GRAPHICS_OBJECT_NOLINK
} GraphicsObjectType;

typedef struct GraphicsLine
{
    GraphicsPosition *start;
    GraphicsPosition *end;

    GraphicsColor *color;

    void *link_start;
    void *link_end;

    GraphicsObjectType link_start_type;
    GraphicsObjectType link_end_type;

    bool is_linked;
} GraphicsLine;

GraphicsColor *graphics_color_new(double r, double g, double b);

// Type to contain pointers to callback functions

typedef void (* CallbackFunc) (void *);

// Main struct for the Engine

typedef struct GraphicsEngine
{
    CallbackFunc callbacks[MAX_CALLBACK_FUNCTIONS];

    int callback_count;

    bool render_job_is_running;
    bool velocity_job_is_running;

    pthread_t render_thread;
    pthread_t velocity_thread;

    struct
    {
        GLfloat width;
        GLfloat height;

        const char *title;

        GLFWwindow *window;
    } window;

    struct
    {
        int pre_matrix_mode;
        int post_matrix_mode;
    } config;

    struct
    {
        GLdouble fovy;
        GLdouble aspect;
        GLdouble z_near;
        GLdouble z_far;

        GLdouble x;
        GLdouble y;
        GLdouble z;

        GLdouble tx;
        GLdouble ty;
        GLdouble tz;

        GLdouble x_isup;
        GLdouble y_isup;
        GLdouble z_isup;
    } camera;

    struct
    {
        GraphicsSphere **spheres;
        GraphicsLine **lines;

        int sphere_count;
        int line_count;
    } objects;

    void *error_callback;
    void *key_callback;
} GraphicsEngine;

// Functions

GraphicsEngine *graphics_engine_init(void *error_callback, void *key_callback);

GraphicsEngineExitStatus graphics_engine_start(GraphicsEngine *engine);

void graphics_engine_close(GraphicsEngine *engine);
void graphics_engine_stop(GraphicsEngine *engine);

GraphicsSphere *graphics_sphere_new(GraphicsPosition *position, GraphicsVelocity *velocity, GraphicsColor *color, double radius, int slices, int stacks);

void graphics_engine_add_callback(GraphicsEngine *engine, CallbackFunc callback);
void graphics_engine_del_callback(GraphicsEngine *engine, CallbackFunc callback);
void graphics_engine_handle_callbacks(GraphicsEngine *engine);

void graphics_velocity_set(GraphicsEngine *engine, void *object, GraphicsVelocity *velocity, GraphicsObjectType type);

GraphicsLine *graphics_line_new(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color, void *link_start, void *link_end, GraphicsObjectType link_start_type, GraphicsObjectType link_end_type, bool is_linked);

void graphics_engine_object_add(GraphicsEngine *engine, void *object, GraphicsObjectType type);

void *graphics_engine_render(void *arg);

void graphics_engine_set_origin(GraphicsEngine *engine);
void graphics_engine_set_camera(GraphicsEngine *engine);
void graphics_engine_rotate_camera(GraphicsEngine *engine, float degrees);

#endif
