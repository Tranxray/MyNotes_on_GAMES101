# Lecture 04 Transformation in 3D

## Homogeneous coordinates in 3D
- 3D point = $(x,y,z,1)^T$
- 3D vector = $(x,y,z,0)^T$
- $(x,y,z,w)^T$(w≠0) is the 3D point: $(x/w,y/w,z/w)^T$


## 3D Transformations
- Use 4x4 matrix for affine transformations
$$
\begin{bmatrix}
    x'\\
    y'\\
    z'\\
    1
\end{bmatrix}
=
\begin{bmatrix}
    a&b&c&t_x\\
    d&e&f&t_y\\
    g&h&i&t_z\\
    0&0&0&1
\end{bmatrix}
•
\begin{bmatrix}
    x\\
    y\\
    z\\
    1
\end{bmatrix}
$$
- Note: Linear transform first, then translation