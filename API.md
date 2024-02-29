# API Documentation

This document provides an overview of the API for the graphics engine and related components.

## Contents

1. [Callbacks](#callbacks)
2. [Camera](#camera)
3. [Containers](#containers)
4. [Engine](#engine)
5. [Print](#print)
6. [Render](#render)
7. [Utils](#utils)
8. [Atom](#atom)
9. [Universe Config](#universe-config)
10. [Universe](#universe)

## Callbacks <a name="callbacks"></a>

### `void *graphics_engine_callbacks(void *arg)`
- Description: Executes the registered callback functions of the graphics engine. This function is responsible for triggering all registered callbacks with the specified argument.
- Parameters:
  - `arg`: Argument to be passed to the callback functions.

### `void graphics_engine_add_callback(GraphicsEngine *engine, CallbackFunc callback)`
- Description: Adds a callback function to the graphics engine. Callback functions added through this function will be executed when `graphics_engine_callbacks()` is called.
- Parameters:
  - `engine`: Pointer to the graphics engine.
  - `callback`: Pointer to the callback function to be added.

### `void graphics_engine_del_callback(GraphicsEngine *engine, CallbackFunc callback)`
- Description: Removes a previously added callback function from the graphics engine. Once removed, the specified callback will no longer be triggered by `graphics_engine_callbacks()`.
- Parameters:
  - `engine`: Pointer to the graphics engine.
  - `callback`: Pointer to the callback function to be removed.

### `void graphics_engine_handle_callbacks(GraphicsEngine *engine)`
- Description: Executes all registered callback functions of the graphics engine. This function iterates through all registered callbacks and invokes them with the appropriate argument.
- Parameters:
  - `engine`: Pointer to the graphics engine.

## Camera <a name="camera"></a>

### `void graphics_engine_set_camera(GraphicsEngine *engine)`
- Description: Sets the camera for the graphics engine. This function configures the camera parameters such as position, orientation, and projection settings.
- Parameters:
  - `engine`: Pointer to the graphics engine.

### `void graphics_engine_rotate_camera(GraphicsEngine *engine, float angle)`
- Description: Rotates the camera for the graphics engine. This function adjusts the orientation of the camera by the specified angle.
- Parameters:
  - `engine`: Pointer to the graphics engine.
  - `angle`: Angle of rotation in degrees.

### `void graphics_engine_set_origin(GraphicsEngine *engine)`
- Description: Sets the origin point for the graphics engine. This function repositions the reference point used for rendering objects.
- Parameters:
  - `engine`: Pointer to the graphics engine.

## Containers <a name="containers"></a>

### `GraphicsPosition`
- Description: Represents a position in 3D space. (used by graphics)
- Parameters:
    - `x` X coordinate of the position. type: `double`
    - `y` Y coordinate of the position. type: `double`
    - `z` Z coordinate of the position. type: `double`

### `GraphicsColor`
- Description: Represents a color with RGB components
- Parameters:
    - `r` Red value of the color. type: `double`
    - `g` Green value of the color. type: `double`
    - `b` Blue value of the color.  type: `double`

### `GraphicsVelocity`:
- Description: Represents velocity in 3D space
- Parameters:
    - `x_speed` Speed along the x-axis. type: `double`
    - `y_speed` Speed along the y-axis. type: `double`
    - `z_speed` Speed along the z-axis. type: `double`

    All speed values can be positive and/or negative

### `GraphicsSphere`
- Description: Represents a sphere object with position, velocity, color, and radius
- Parameters:
    - `position` 3D Position of the sphere. type: `GraphicsPosition *`
    - `velocity` Velocity of the sphere. type: `GraphicsVelocity *`
    - `color` Color of the sphere. type: `GraphicsColor *`
    - `radius` Radius of the sphere. type: `double`
    - `slices` Amount of slices to render the sphere. type: `int`
    - `stacks` Amount of stacks to render the sphere. type: `int`

### `GraphicsLine`
- Description: Represents a line object with start and end positions, color, and optional links to other objects.
- Parameters:
    - `start` 3D Position of the start of the line. type: `GraphicsPosition *`
    - `end` 3D Position of the end of the line. type: `GraphicsPosition *`
    - `GraphicsColor *` Color of the line. type: `GraphicsColor *`
    - `link_start` Pointer to the object where the start of the line links to. type: `void *`
    - `link_end` Pointer to the object where the end of the line links to. type: `void *`
    - `link_start_type` Type of the object the start of the line is linked to. type: `GraphicsObjectType`
    - `link_end_type` Type of the object the end of the line is linked to. type: `GraphicsObjectType`
    - `is_linked` Indicator if the line is linked to objects or not. type: `bool`

### `UniversePosition`
- Description: Represents a position in 3D space. (used by universe engine)
- Parameters:
    - `x` X coordinate of the position. type: `double`
    - `y` Y coordinate of the position. type: `double`
    - `z` Z coordinate of the position. type: `double`

### `UniverseBlock`
- Description: Represents a universe block
- Parameters:
    - `atoms` Dynamic array of atom objects that are in the block
    - `do_render` Indicator if the block should be rendered. type: `bool`
    - `is_full` Indicator if the block is full. type: `bool`
    - `atom_count` Counter of how many atoms are in the atoms array. type: `int`
    - `temperature` Temperature of the universe block. type: `double`

### `Universe`
- Description: Represents the unviverse containing a 3D array of UniverseBlocks
- Parameters:
    - `blocks` 3D array of UniverseBlocks *
        - 1D size: `UNIVERSE_LENGTH`
        - 2D size: `UNIVERSE_WIDTH`
        - 3D size: `UNIVERSE_HEIGHT`

### `Atom`
- Description: Represents an atom containing some data about the atom
- Parameters:
    - `position` 3D position of the Atom. type: `UniversePosition *`
    - `periodic_number` Number of the element in periodic table. type: `int`
    - `max_binds` Maximum amount of binds the atom can use. type: `int`
    - `u_mass` Mass of the atom in u. type: `double`
    - `can_bind` Indicator if the atom is able to bind to other atoms. type: `bool`
    - `is_isotope` Indicator if the atom is an isotope. type: `bool`
    - `neutron_count` Amount of neutrons in the atom. type: `int`
    - `proton_count` Amount of protons in the atom. type: `int`
    - `electron_count` Amount of electrons in the atom. type: `int`

(Descriptions for functions in the Containers section can be added based on their specific functionality.)

## Engine <a name="engine"></a>

### `void DEBUG(GraphicsEngineDebugType type, const char *msg)`
- Description: Debugs to the TTY
- Parameters:
    - `type` The type of the debug message type: `GraphicsEngineDebugType`
        - `GRAPHICS_ENGINE_ERROR` Error message
          - `GRAPHICS_ENGINE_WARNING` Warning message
          - `GRAPHICS_ENGINE_DEBUG` Debug message
     - `msg` The message itself type: `const char *`

### `GraphicsEngine *graphics_engine_init(void *error_callback, void *key_callback)`
- Description: Initializes the graphics engine
- Parameters:
    - `error_callback` Pointer to the error callback function for OpenGL type: `void *`
    - `key_callback` Pointer to the keyboard callback function for OpenGL type: `void *`

### `GraphicsEngineExitStatus graphics_engine_start(GraphicsEngine *engine)`
- Description: Starts the graphics engine, including the render, callback and velocity jobs
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

### `void graphics_engine_stop(GraphicsEngine *engine)`
- Description: Stop the engine, stopping all the active jobs
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

### `void graphics_engine_add_callback(GraphicsEngine *engine, CallbackFunc callback)`
- Description: Add a callback function to the graphics_engine
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `callback` Callback function reference. type: `CallbackFunc`

### `void graphics_engine_del_callback(GraphicsEngine *engine, CallbackFunc callback)`
- Description: Delete a callback function from the graphics_engine
- WARNING: Still under development
- Parameters:
    - `engine` Pointer to the GraphcisEngine object. type: `GraphicsEngine *`
    - `callback` Callback function refernce. type: `CallbackFunc`

### `void graphics_velocity_set(GraphicsEngine *engine, void *object, GraphicsVelocity *velocity, GraphicsObjectType type)`
- Description: Set the velocity of an object
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `object` Pointer to the object you want to set the velocity of. type: `void *`
    - `velocity` The velocity you want to set the object to `GraphicsVelocity *`
    - `type` The type of object you are setting the velocity of. type: `GraphicsObjectType`

### `GraphicsLine *graphics_line_new(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color, void *link_start, void *link_end, GraphicsObjectType link_start_type, GraphicsObjectType link_end_type, bool is_linked)`
- Description: Creates a new GraphicsLine object
- Parameters:
    - `start` 3D Position of the start of the line. type: `GraphicsPosition *`
    - `end` 3D Position of the end of the line. type: `GraphicsPosition *`
    - `color` RGB Color of the line. type: `GraphicsColor *`
    - `link_start` Pointer to the object where the start of the line is linked to. type: `void *`
    - `link_end` Pointer to the object where the end of the line is linked to. type: `void *`
    - `link_start_type` Type of object where start of the line is linked to. type: `GraphicsObjectType`
    - `link_end_type` Type of object where end of the line is linked to. type: `GraphicsObjectType`

### `void graphics_engine_object_add(GraphicsEngine *engine, void *object, GraphicsObjectType type)`
- Description: Adds an object to the graphics engine
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `object` Pointer to the object you want to add. type: `void *`
    - `GraphicsObjectType` Type of the object you want to add. type: `GraphicsObjectType`

### `void graphics_engine_set_origin(GraphicsEngine *engine)`
- Description: Sets the origin on the screen
- WARNING: Still under development
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

### `void graphics_engine_set_camera(GraphicsEngine *engine)`
- Description: Sets the camera
- WARNING: Still under development
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

### `void graphics_engine_rotate_camera(GraphicsEngine *engine, float degrees)`
- Description: Rotates the camera by X degrees
- WARNING: Unstable function
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `degrees` How many degrees you want to rotate the camera. Has to be >= 0. Type: `float`


## Print <a name="print"></a>

...

(Descriptions for functions in the Print section can be added based on their specific functionality.)

## Render <a name="render"></a>

...

(Descriptions for functions in the Render section can be added based on their specific functionality.)

## Utils <a name="utils"></a>

...

(Descriptions for functions in the Utils section can be added based on their specific functionality.)

## Atom <a name="atom"></a>

...

(Descriptions for functions in the Atom section can be added based on their specific functionality.)

## Universe Config <a name="universe-config"></a>

...

(Descriptions for functions in the Universe Config section can be added based on their specific functionality.)

## Universe <a name="universe"></a>

...

(Descriptions for functions in the Universe section can be added based on their specific functionality.)
