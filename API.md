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

...

(Descriptions for functions in the Containers section can be added based on their specific functionality.)

## Engine <a name="engine"></a>

...

(Descriptions for functions in the Engine section can be added based on their specific functionality.)

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
