# Universe Simulator

Welcome to the Universe Simulator project! This project is designed to simulate the behavior of objects in a virtual universe using a graphics engine. Currently, the project provides a base graphics engine to render and manipulate objects within the simulated universe.

## Features

- Render spheres and lines in a 3D environment.
- Control camera position and orientation.
- Support for adding callback functions to handle events.
- Multi-threaded rendering and velocity calculation.

## Getting Started

To get started with the project, follow these steps:

1. Clone the repository to your local machine:

```git clone https://github.com/your-username/universe-simulator.git```

2. Compile the project:

```chmod +x ./compile && ./compile```

3. Run the project:

```./engine```

## Dependencies

- OpenGL
- GLFW
- pthread

## Contributing

Contributions to the project are welcome! If you'd like to contribute, please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Structures

- `GraphicsPosition`: Represents a position in 3D space.
- `GraphicsColor`: Represents a color with RGB components.
- `GraphicsVelocity`: Represents velocity in 3D space.
- `GraphicsSphere`: Represents a sphere object with position, velocity, color, and radius.
- `GraphicsLine`: Represents a line object with start and end positions, color, and optional links to other objects.

### Enums

- `GraphicsEngineDebugType`: Indicates the type of debugging message.
- `GraphicsEngineExitStatus`: Indicates the exit status of the graphics engine.

### Typedefs

- `CallbackFunc`: Typedef for callback functions.

### Functions

- `graphics_engine_init`: Initializes the graphics engine.
- `graphics_engine_start`: Starts the graphics engine.
- `graphics_engine_close`: Closes the graphics engine.
- `graphics_engine_stop`: Stops the graphics engine.
- `graphics_sphere_new`: Creates a new sphere object.
- `graphics_line_new`: Creates a new line object.
- `graphics_engine_add_callback`: Adds a callback function to the graphics engine.
- `graphics_engine_del_callback`: Removes a callback function from the graphics engine.
- `graphics_engine_handle_callbacks`: Handles callback functions.
- `graphics_velocity_set`: Sets the velocity of an object.
- `graphics_engine_render`: Renders the graphics.
- `graphics_engine_set_origin`: Sets the origin of the graphics engine.
- `graphics_engine_set_camera`: Sets the camera position and orientation.
- `graphics_engine_rotate_camera`: Rotates the camera.


