# Lecture 09 Shading 3

## Barycentric coordinates 重心坐标: Interpolation across triangles 三角形内插值

1. goal: With specified values at vertices, obtain smoothly varying values across triangles
2. what to interpolate: texture coordinates, colors, normal vectors, ...
3. Barycentric Coordinates:
   - A coordinate system for triangles $(\alpha,\beta,\gamma)$
   - for each (x,y), $(x,y)=\alpha A+\beta B+\gamma C$ and $\alpha+\beta+\gamma=1$
   - $(\alpha,\beta,\gamma)$ is the barycentric coorinates for $(x,y)$
   - Inside the triangle if all three coordinates are non-negative
   - Geomatric viewpoint -- proportional areas: 
   ![alt text](image-39.png)
   - The barycentric coordinate of centroid(重心) is $(\frac{1}{3},\frac{1}{3},\frac{1}{3})$

4. Using Barycentric Coordinates to Linearly interpolate values at vertices
   ![alt text](image-40.png)
   - note: barycentric coordinates are not invariant under projection 即投影后重心坐标会改变，因此应在投影之前（3维空间中）进行插值

## Texture Magnification 问题：纹理放大

### What if the texture is too small? (Upsampling)
- Generally don't want this — insufficient texture resolution
- A pixel on a texture—a texel（纹理元素、纹素）

1. Bilinear interpolation 双线性插值
   - Want to sample texture value f(x,y) at red point
   - Black points indicate texture sample locations
   - We take 4 nearest sample locations, with texture values as labeled, and fractional offsets, as $(s,t)$
    ![alt text](image-41.png)
   - Linear interpolation (1D): 
    $$lerp(x, v_0, v_1) = v_0+ x(v_1 - v_0)$$
   - Two helper lerps: 
    $$u_0=lerp(s,u_{00},u_{10})$$
    $$u_1=lerp(s,u_{01},u_{11})$$
   - Final vertical lerp, to get result:
    $$f(x,y)=lerp(t,u_0,u_1)$$

2. Bicubic interpolation
   - Instead of using 4 nearest samples, use 16 nearest samples

### What if the texture is too large? (Downsampling)
- may lead to aliase 走样
![alt text](image-42.png)

1. Will supersampling work?
   - Yes, high quality, but costly
   - When highly minified, many texels in pixel footprint
   - Signal frequency too large in a pixel
   - Need even higher sampling frequency

2. Do not sample, use the average value
   - Point Query vs. (Avg.)Range Query
   - Different Pixels -> Different-Sized Footprints
   - Mipmap: Allowing(fast, approxmate, square) range queries 近似的、正方形的范围查询
     - ![alt text](image-43.png)
     - ![alt text](image-44.png) 
     - Computing Mipmap Level D:
       ![alt text](image-45.png)
     - then, fetch the corresponding ave value in level D: (三线性插值)
       ![alt text](image-46.png)
   - Mipmap Liminations: Overblur

3. Anisotropic Filtering 各项异性过滤: 比Mipmap三线性插值好
   - using ripmaps and summed area tables
   - Can look up axis-aligned rectangular zones
    ![alt text](image-47.png)
   - Diagonal footprints still a problem
   ![alt text](image-48.png)

4. EWA Filtering
   - Use multiple lookups
   - Weighted average
   - Mipmap hierarchy still helps
   - Can handle irregular footprints
   - high costs

## Applications for Textures
### In modern GPUs, texture = memory + range query(filtering) 范围查询
- General method to bring data to fragment calculations

### Many applications
- Environment lighting
  - Environment Map 将环境光记录为环境贴图，当作纹理，用来渲染其他物体
  - Spherical Environment Map 将环境光记录在球上，展开成纹理 (边界上会产生扭曲)
   ![alt text](image-49.png)
  - Cube Map 将环境光记录在立方体的六个面上 (扭曲被改善)
   ![alt text](image-50.png)
   ![alt text](image-51.png)

- Texture can affect shading
  - texture doesn't have to only represent colors
  1. Bump/normal mapping.凹凸贴图 it can store height/normal, and affect shading 存储物体表面凹凸、法线信息，从而改变着色
     - Fake the detailed geometry
     - Adding surface detail without adding more triangles
     - perturb surface normal per pixel (for shading computations only)
     - 'height shift' per texel defined by a texture
      ![alt text](image-52.png)
     - How to modify normal vector? (in flatland 一维中)
      ![alt text](image-53.png)
     - How to perturb the normal (in 3D)
      ![alt text](image-54.png)
      Note that this is in local coordinate!
  2. Displacement mapping.位移贴图 -- a more advanced approach
     - use the same texture as in bumping mapping
     - acctually moves the vertices 真实地移动了顶点，改变了几何
     - 要求模型足够细致

- 3D Procedural Noise + Solid Modeling
- 3D Textures and Volume Rendering