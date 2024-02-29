# API Documentation

This document provides an overview of the API for the graphics engine and related components.

## Contents

1. [Containers](#containers)
   
    1.1 [Graphics](#containers_graphics)
   
    1.2 [Universe](#containers_universe)

    1.3 [Atoms](#containers_atoms)

3. [Functions](#functions)

    1.1 [Graphics](#functions_graphics)

    1.2 [Universe](#functions_universe)

    1.3 [Atoms](#functions_atoms)

    1.4 [Utils](#functions_utils)

5. [Universe Config](#universe_config)
---
## Containers <a name="containers"></a>

### Graphics <a name="containers_graphics"></a>

#### `GraphicsPosition`
- Description: Represents a position in 3D space. (used by graphics)
- Parameters:
    - `x` X coordinate of the position. type: `double`
    - `y` Y coordinate of the position. type: `double`
    - `z` Z coordinate of the position. type: `double`

#### `GraphicsColor`
- Description: Represents a color with RGB components
- Parameters:
    - `r` Red value of the color. type: `double`
    - `g` Green value of the color. type: `double`
    - `b` Blue value of the color.  type: `double`

#### `GraphicsVelocity`:
- Description: Represents velocity in 3D space
- Parameters:
    - `x_speed` Speed along the x-axis. type: `double`
    - `y_speed` Speed along the y-axis. type: `double`
    - `z_speed` Speed along the z-axis. type: `double`

    All speed values can be positive and/or negative

#### `GraphicsSphere`
- Description: Represents a sphere object with position, velocity, color, and radius
- Parameters:
    - `position` 3D Position of the sphere. type: `GraphicsPosition *`
    - `velocity` Velocity of the sphere. type: `GraphicsVelocity *`
    - `color` Color of the sphere. type: `GraphicsColor *`
    - `radius` Radius of the sphere. type: `double`
    - `slices` Amount of slices to render the sphere. type: `int`
    - `stacks` Amount of stacks to render the sphere. type: `int`

#### `GraphicsLine`
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
---
### Universe <a name="containers_universe"></a>

#### `UniversePosition`
- Description: Represents a position in 3D space. (used by universe engine)
- Parameters:
    - `x` X coordinate of the position. type: `double`
    - `y` Y coordinate of the position. type: `double`
    - `z` Z coordinate of the position. type: `double`

#### `UniverseBlock`
- Description: Represents a universe block
- Parameters:
    - `atoms` Dynamic array of atom objects that are in the block
    - `do_render` Indicator if the block should be rendered. type: `bool`
    - `is_full` Indicator if the block is full. type: `bool`
    - `atom_count` Counter of how many atoms are in the atoms array. type: `int`
    - `temperature` Temperature of the universe block. type: `double`

#### `Universe`
- Description: Represents the unviverse containing a 3D array of UniverseBlocks
- Parameters:
    - `blocks` 3D array of UniverseBlocks *
        - 1D size: `UNIVERSE_LENGTH`
        - 2D size: `UNIVERSE_WIDTH`
        - 3D size: `UNIVERSE_HEIGHT`
---
### Atoms <a name="containers_atoms"></a>
#### `Atom`
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
---
## Functions <a name="functions"></a>

### Graphics <a name="functions_graphics"></a>

#### `GraphicsEngine *graphics_engine_init(void *error_callback, void *key_callback)`
- Description: Initializes the graphics engine
- Parameters:
    - `error_callback` Pointer to the error callback function for OpenGL type: `void *`
    - `key_callback` Pointer to the keyboard callback function for OpenGL type: `void *`

#### `GraphicsEngineExitStatus graphics_engine_start(GraphicsEngine *engine)`
- Description: Starts the graphics engine, including the render, callback and velocity jobs
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

#### `void graphics_engine_stop(GraphicsEngine *engine)`
- Description: Stop the engine, stopping all the active jobs
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

#### `void graphics_engine_add_callback(GraphicsEngine *engine, CallbackFunc callback)`
- Description: Add a callback function to the graphics_engine
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `callback` Callback function reference. type: `CallbackFunc`

#### `void graphics_engine_del_callback(GraphicsEngine *engine, CallbackFunc callback)`
- Description: Delete a callback function from the graphics_engine
- WARNING: Still under development
- Parameters:
    - `engine` Pointer to the GraphcisEngine object. type: `GraphicsEngine *`
    - `callback` Callback function refernce. type: `CallbackFunc`

#### `void graphics_velocity_set(GraphicsEngine *engine, void *object, GraphicsVelocity *velocity, GraphicsObjectType type)`
- Description: Set the velocity of an object
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `object` Pointer to the object you want to set the velocity of. type: `void *`
    - `velocity` The velocity you want to set the object to `GraphicsVelocity *`
    - `type` The type of object you are setting the velocity of. type: `GraphicsObjectType`

#### `GraphicsLine *graphics_line_new(GraphicsPosition *start, GraphicsPosition *end, GraphicsColor *color, void *link_start, void *link_end, GraphicsObjectType link_start_type, GraphicsObjectType link_end_type, bool is_linked)`
- Description: Creates a new GraphicsLine object
- Parameters:
    - `start` 3D Position of the start of the line. type: `GraphicsPosition *`
    - `end` 3D Position of the end of the line. type: `GraphicsPosition *`
    - `color` RGB Color of the line. type: `GraphicsColor *`
    - `link_start` Pointer to the object where the start of the line is linked to. type: `void *`
    - `link_end` Pointer to the object where the end of the line is linked to. type: `void *`
    - `link_start_type` Type of object where start of the line is linked to. type: `GraphicsObjectType`
    - `link_end_type` Type of object where end of the line is linked to. type: `GraphicsObjectType`

#### `void graphics_engine_object_add(GraphicsEngine *engine, void *object, GraphicsObjectType type)`
- Description: Adds an object to the graphics engine
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `object` Pointer to the object you want to add. type: `void *`
    - `GraphicsObjectType` Type of the object you want to add. type: `GraphicsObjectType`

#### `void graphics_engine_set_origin(GraphicsEngine *engine)`
- Description: Sets the origin on the screen
- WARNING: Still under development
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

#### `void graphics_engine_set_camera(GraphicsEngine *engine)`
- Description: Sets the camera
- WARNING: Still under development
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`

#### `void graphics_engine_rotate_camera(GraphicsEngine *engine, float degrees)`
- Description: Rotates the camera by X degrees
- WARNING: Unstable function
- Parameters:
    - `engine` Pointer to the GraphicsEngine object. type: `GraphicsEngine *`
    - `degrees` How many degrees you want to rotate the camera. Has to be >= 0. Type: `float`

#### `void graphics_engine_handle_callbacks(GraphicsEngine *engine)`
- Description: Executes all registered callback functions of the graphics engine. This function iterates through all registered callbacks and invokes them with the appropriate argument.
- Parameters:
  - `engine`: Pointer to the graphics engine.

#### `GraphicsColor *graphics_color_new(double r, double g, double b)`
- Description: Creates a new GraphicsColor object with an RGB value
- Paramters:
    - `r` Red value of the color. type: `double`
    - `g` Green value of the color. type: `double`
    - `b` Blue value of the color. type: `double`

#### `GraphicsPosition *graphics_pos_new(double x, double y, double z)`
- Description: Creates a new GraphicsPosition object with an RGB value
- Parameters:
    - `x` X coordinate of the position. type: `double`
    - `y` Y coordinate of the position. type: `double`
    - `z` Z coordinate of the position. type: `double`

#### `GraphicsSphere *graphics_sphere_new(GraphicsPosition *position, GraphicsVelocity *velocity, GraphicsColor *color, double radius, int slices, int stacks)`
- Description: Creates a new GraphicsSphere object
- Parameters:
    - `position` Position of the sphere. type: `GraphicsPosition *`
    - `velocity` Velocity of the sphere. type: `GraphicsVelocity *`
    - `color` Color of the sphere. type: `GraphicsColor *`
    - `radius` Radius of the sphere. type: `double`
    - `slices` Amount of slices to use for the renderer. type: `int`
    - `stacks` Amount of stacks to use for the renderer. type: `int`
---
### Universe <a name="functions_universe"></a>

#### `UniverseBlock *universe_block_new(bool do_render, bool is_full, double temperature)`
- Description: Creates a new UniverseBlock object
- Parameters:
    - `do_render` Indicator if the block is to be rendered or not. Type: `bool`
    - `is_full` Indicator if the block is full or not. Type: `bool`
    - `temperature` Temperature of the block. Type: `double`

#### `UniverseBlock *universe_block_new_random(bool do_render)`
- Description: Creates a new UniverseBlock object with random parameters
- Parameters:
    - `do_render` Indicator if the block is to be rendered or not. Type: `bool`

#### `UniverseBlock *universe_get_block_by_position(Universe *universe, UniversePosition *position)`
- Description: Returns the UniverseBlock where the given position is in
- Parameters:
    - `universe` Pointer to the Universe object. Type: `Universe *`
    - `position` Position to find the block. Type: `UniversePosition *`

#### `Universe *universe_init()`
- Description: Initializes the Universe object

#### `void universe_destroy(Universe *universe)`
- Description: Deinitializes the Universe object
- Parameters:
    - `universe` Pointer to the Universe object. Type: `Universe *`

#### `void universe_block_destroy(UniverseBlock *block)`
- Description: Deinitializes a UniverseBlock object
- Parameters:
    - `block` Pointer to the UniverseBlock object. Type: `UniverseBlock *`
---
### Atoms <a name="functions_atoms"></a>

#### `Atom *universe_atom_new(UniversePosition *position, int periodic_number, int max_binds, double u_mass, bool can_bind, bool is_isotope, int neutron_count, int proton_count, int electron_count)`
- Description: Creates a new Atom object
- Parameters:
    - `position` Position of the atom in 3D space. type: `UniversePosition *`
    - `periodic_number` Number of the element in the periodic table. type: `int`
    - `max_binds` Maximum amount of binds the atom can undergo. type: `int`
    - `u_mass` Mass of the element in u. type: `double`
    - `can_bind` Indicator if the atom can bind to other atoms. type: `bool`
    - `is_isotope` Indicator if the atom is an isotope. type: `bool`
    - `neutron_count` Amount of neutrons. type: `int`
    - `proton_count` Amount of protons. type: `int`
    - `electron_count` Amount of electrons. type: `int`

#### `void universe_atom_destroy(Atom *atom)`
- Description: Frees an Atom object from memory
- Parameters:
    - `atom` Pointer to the Atom object

#### `void universe_block_add_atom(UniverseBlock *block, Atom *atom)`
- Description: Add an atom to a block
- Parameters:
    - `block` Pointer to the UniverseBlock object. Type: `UniverseBlock *`
    - `atom` Pointer to the Atom object. Type: `Atom *`

#### `void universe_block_del_atom_by_pos(UniverseBlock *block, UniversePosition *position)`
- Description: Remove an atom by position from the block
- Parameters:
    - `block` Pointer to the UniverseBlock object. Type: `UniverseBlock *`
    - `position` Position of the Atom in the block
---
### Utils <a name="functions_utils"></a>

#### `void DEBUG(GraphicsEngineDebugType type, const char *msg)`
- Description: Debugs to the TTY
- Parameters:
    - `type` The type of the debug message type: `GraphicsEngineDebugType`
        - `GRAPHICS_ENGINE_ERROR` Error message
          - `GRAPHICS_ENGINE_WARNING` Warning message
          - `GRAPHICS_ENGINE_DEBUG` Debug message
     - `msg` The message itself type: `const char *`
---
## Universe Config <a name="universe_config"></a>

| Name                               | Type        | Default Value       | Description                                      |
|------------------------------------|-------------|---------------------|--------------------------------------------------|
| `MAX_CALLBACK_FUNCTIONS`           | `int`       | `25`                | Maximum amount of callback functions            |
| `ENGINE_CALLBACK_START`            | `int`       | `0`                 | Starting index for engine callback functions    |
| `ENGINE_DEFAULT_WIDTH`             | `int`       | `1920`              | Default width of the graphics engine window     |
| `ENGINE_DEFAULT_HEIGHT`            | `int`       | `1080`              | Default height of the graphics engine window    |
| `ENGINE_DEFAULT_TITLE`             | `string`    | `"Odyssey (v1.0)"`  | Default title of the graphics engine window |
| `ENGINE_DEFAULT_PRE_MATRIX_MODE`   | `GLenum`    | `GL_PROJECTION`     | Default OpenGL matrix mode before rendering     |
| `ENGINE_DEFAULT_POST_MATRIX_MODE`  | `GLenum`    | `GL_MODELVIEW`      | Default OpenGL matrix mode after rendering      |
| `ENGINE_DEFAULT_FOVY`              | `float`     | `90.0f`             | Default field of view angle for the camera      |
| `ENGINE_DEFAULT_Z_NEAR`            | `float`     | `0.01f`             | Default near clipping plane distance             |
| `ENGINE_DEFAULT_Z_FAR`             | `float`     | `100.0f`            | Default far clipping plane distance              |
| `ENGINE_DEFAULT_AXIS_SIZE`         | `float`     | `10.0f`             | Default size of axes for visualization          |
| `ENGINE_DEFAULT_CAMERA_X`          | `float`     | `0.0f`              | Default x-coordinate of the camera position     |
| `ENGINE_DEFAULT_CAMERA_Y`          | `float`     | `3.0f`              | Default y-coordinate of the camera position     |
| `ENGINE_DEFAULT_CAMERA_Z`          | `float`     | `5.0f`              | Default z-coordinate of the camera position     |
| `ENGINE_DEFAULT_CAMERA_TARGET_X`   | `float`     | `0.0f`              | Default x-coordinate of the camera target       |
| `ENGINE_DEFAULT_CAMERA_TARGET_Y`   | `float`     | `0.0f`              | Default y-coordinate of the camera target       |
| `ENGINE_DEFAULT_CAMERA_TARGET_Z`   | `float`     | `0.0f`              | Default z-coordinate of the camera target       |
| `ENGINE_DEFAULT_CAMERA_ISUP_X`     | `float`     | `0.0f`              | Default x-indicator of the camera's up vector   |
| `ENGINE_DEFAULT_CAMERA_ISUP_Y`     | `float`     | `1.0f`              | Default y-indicator of the camera's up vector   |
| `ENGINE_DEFAULT_CAMERA_ISUP_Z`     | `float`     | `0.0f`              | Default z-indicator of the camera's up vector   |
| `UNIVERSE_LENGTH`                   | `float`     | `100.0f`            | Length of the simulated universe                |
| `UNIVERSE_WIDTH`                    | `float`     | `100.0f`            | Width of the simulated universe                 |
| `UNIVERSE_HEIGHT`                   | `float`     | `100.0f`            | Height of the simulated universe                |
