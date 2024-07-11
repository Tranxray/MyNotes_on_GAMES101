# Lecture 05 Rasterization of Triangles

##  Canonical Cube to Screen
- after MVP, the view is converted to "canonical" cube $[-1, 1]^3$

1. what is a screen? (raster)
   - An array of pixels(for now, a little square with uniform color)
   - Size of the array: resolution
   - A typical kind of raster display

2. Defining the screen space
   - Pixels' indices are in the form of (x,y), where both x and y are integers
   - Pixels' indixes are from (0,0) to (width-1, height-1)
   - Pixel (x,y) is centered at (x+0.5, y+0.5)
   - The sreen covers range (0,0) to (width, height)
   - So, we try to transform $[-1,1]^2$ to [0, width]x[0, height] (irrelevant to z)
   - Viewport transform matrix:
$$
M_{viewport}=
\begin{bmatrix}
    \frac{width}{2}&0&0&\frac{width}{2}\\
    0&\frac{height}{2}&0&\frac{height}{2}\\
    0&0&1&0\\
    0&0&0&1
\end{bmatrix}
$$

## Rasterizing Triangles into Pixels

### Drawing Machine
- CNC Sharpie Drawing Machine
- Laser Cutters

### Different Raster Displays
- Oscilloscope 示波器 
- Television - Cathode Ray Tube 阴极射线管 & Raster Scan
- Frame Buffer: Memory for a Raster Display
- Flat Panel Displays - LCD(Liquid Crystal Diaplay)
- LED Array Display (Light emmitting diode array 发光二极管)
- Electrophoretic(Electronic Ink) Display (阅读器)

### Rasterization: Drawing to Raster Displays
1. Triangles - Fundamental Shape Primitives
   - Most basic polygon
   - Break up other polygons
   - Guaranteed to be planar
   - Well-defined interior
   - Well-defined method for interpolating values at vertices over triangle (barycentric interpolation)

2. What Pixel Values Approximate a Triangle?
- Input: Position of triangle vertices projected on screen
- Output: set of pixel values approximating triangle

3. A simple approach: Sampling
- Evaluating a function at a point is sampling. We can discretize a function by sampling.
- Sampling is a core idea in graphics. We sample time (1D), area (2D), direction (2D), volume (3D) ... 
- Rasterization = Sampling a 2D Indicator Function

- Define Binary Function:
  - inside(tri, x, y)= 1, if Point(x, y) in triangle tri
  - inside(tri, x, y)= 0, otherwise
  - use cross product

- Rasterization (only need to check a bounding box containing the triangle)
    ```cpp
    for(int x = xmin; x < xmax; x++){
        for(int y = ymin; y < ymax; y++){
            image[x][y] = inside(tri, x+0.5, y+0.5);
        }
    }

### Rasterization in Real Displays
1. real LCD screen pixels. use RGB pixel geometry
2. color print: observe half-tone pattern

### problems in rasterization
1. Jaggies (锯齿) 
2. Aliasing (走样)