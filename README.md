# Large 3D renderer
### Navigate
* ### [Overview](#overview)
* [Features](#features)
* [Prerequisites](#prerequisites)
* ### [TODO LIST](#to-do-list)
    * [Expand 3D Model Handling](#1-expand-3d-model-handling)✅
    * [Camera and Viewport](#2-camera-and-viewport)✅
    * [Rendering Pipeline](#3-rendering-pipeline)✅
    * [User Interface (UI) Integration](#4-user-interface-ui-integration)🔜
    * [File Input/Output](#5-file-inputoutput)
    * [Testing and Optimization](#6-testing-and-optimization)
    * [Advanced Features (Long-term Goals)](#7-advanced-features-long-term-goals)

## Overview
This project is a basic 3D renderer written from scratch in C++. It is designed to provide a fundamental understanding of how 3D rendering works by implementing core concepts such as vertex transformation, perspective projection, and rasterization. The renderer supports basic shapes, simple shading, and a single light source.

## Features
* 3D Model Loading: Supports basic geometric shapes and custom models in [supported formats, if any].
* Camera System: Includes basic controls for translating and rotating the camera in 3D space.
* Projection: Implements a simple perspective projection to convert 3D coordinates to 2D screen space.
* Shading: Basic shading model using flat shading, with a single directional light source.
* Rasterization: Converts the projected 2D vertices into pixels on the screen.
## Prerequisites
Before you begin, ensure you have met the following requirements:

* `gcc`/`g++` is installed on your machine.
* ~~Graphics library, if any is no need is installed and properly configured.~~ Graphics library is right here!
* ~~Optional dependencies or libraries~~ no depences at all! 

# TO-DO-LIST

## 1. Expand 3D Model Handling
* ### 3D Mesh Representation:

    * Create a `Mesh` class to represent 3D objects, which will consist of vertices (using `Vector3D`) and possibly indices for defining faces (triangles or quads).✅
    * Implement functions for loading, saving, and manipulating these meshes.
* ### Model Transformation:

    * Implement model transformations (translate, rotate, scale) using `Matrix4x4` class to manipulate the entire mesh.
## 2. Camera and Viewport
* ### Camera Class:

    * Create a `Camera` class that holds the view (camera) matrix and projection matrix. This class can handle the perspective and orthographic projections I already implemented.
    * Implement camera controls such as moving, rotating, and zooming, which affect how the 3D scene is viewed.
* ### Viewport Management:

    * Manage multiple viewports or a single viewport where the 3D scene is rendered.
    * Implement basic interaction, like clicking and dragging to rotate the scene or zooming in and out.
## 3. Rendering Pipeline
* ### Basic Software Renderer:

    * Create a basic software renderer that uses `Matrix4x4` and `Vector3D` classes to transform vertices from world space to screen space.
    * Implement a simple rasterizer that can draw wireframes or filled polygons (triangles) on the screen.
* ### Shading and Lighting:

    * Add basic shading models, like flat shading or Gouraud shading, to simulate lighting.
    * Implement a basic lighting system that can include ambient, diffuse, and specular components.
## 4. User Interface (UI) Integration
* ### Basic UI Controls:
    * Create a simple user interface to manipulate objects in the scene (e.g., buttons for transforming objects, sliders for scaling).
    * Integrate rendering viewport into a window with UI elements for better interactivity.
## 5. File Input/Output
* ### 3D Model Import/Export:

    * Implement functionality to import/export 3D models in common formats like OBJ or STL. This will allow me to work with real-world 3D data.
* ### Scene Saving/Loading:

    * Add the ability to save the current state of the scene (camera position, object transformations, etc.) to a file and load it back later.
## 6. Testing and Optimization
* ### Unit Tests:

    * Write unit tests for `Matrix4x4` and `Vector3D` classes to ensure they work correctly under various conditions.
    * Test edge cases like singular matrices, zero-length vectors, and so on.
* ### Performance Optimization:

    * Optimize math operations for speed, especially if you plan on scaling your software for larger scenes or more complex models.
    * Explore SIMD (Single Instruction, Multiple Data) instructions or other optimizations to accelerate matrix and vector calculations.
## 7. Advanced Features (Long-term Goals)
* ### Physics Integration:

    * Integrate a basic physics engine to handle collisions, gravity, and other dynamics.
* ### Animation System:

    * Create a basic animation system that supports keyframe animations, skeletal animations, or simple object animations.
* ### Real-Time Rendering:

    * Integrate a real-time rendering engine (e.g., using OpenGL or Vulkan) to leverage hardware acceleration.