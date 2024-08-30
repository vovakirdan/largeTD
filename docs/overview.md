# Overview:
1. [`vector3d.hpp`](vector3d.md):

    * Defines a `Vector3D` class for basic vector operations like addition, subtraction, scaling, dot product, cross product, normalization, etc.
    * Includes methods for transforming vectors with a Matrix4x4, as well as utility functions like printing and checking for intersection.
2. [`matrix.hpp`](matrix4x4.md):

    * Defines a `Matrix4x4` class for representing and manipulating 4x4 matrices, which are crucial for transformations in 3D space.
    * Includes methods for matrix operations like addition, subtraction, multiplication, inversion, and transposition.
    * Provides static methods for generating common transformation matrices (translation, scaling, rotation, perspective, orthographic).
3. [`mesh.hpp`](mesh.md):

    * Defines a `Mesh` class for representing and manipulating 3D models consisting of vertices, indices (for defining faces), normals, and texture coordinates.
    * Includes methods for transforming the mesh, manipulating geometry (e.g., merging vertices, smoothing, subdividing), and loading/saving meshes in OBJ format.
4. [`camera.hpp`](camera.md):

    * Defines a `Camera` class for setting up the view and projection matrices that define how the 3D scene is viewed.
    * Includes methods for setting up both perspective and orthographic projections, moving the camera, and updating the view matrix.
5. [`viewport.hpp`](viewport.md):

    * Defines a `Viewport` class for handling screen dimensions and aspect ratio.
    * Includes methods for converting normalized device coordinates to screen coordinates and applying viewport transformations.