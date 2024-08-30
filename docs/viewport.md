# Explanation
1. Viewport Dimensions and Aspect Ratio:

    * The `Viewport` class keeps track of the screen dimensions (`width`, `height`) and the aspect ratio. It also provides a method to update these dimensions, which recalculates the aspect ratio.
2. Convert to Screen Coordinates:

    * The `convertToScreenCoordinates()` method takes normalized device coordinates (NDC), which are in the range of `[-1, 1]` for both X and Y axes, and maps them to the corresponding pixel coordinates on the screen.
    * The X coordinate is scaled and shifted from `[-1, 1]` to `[0, width]`.
    * The Y coordinate is inverted (to match the screen's top-left origin) and scaled from `[-1, 1]` to `[0, height]`.
3. Apply Viewport Transformation:

    * The `applyViewportTransformation()` method first performs a perspective divide, converting clip space coordinates (output from the projection matrix) to normalized device coordinates (NDC). Then it uses `convertToScreenCoordinates()` to map NDC to screen coordinates.