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
