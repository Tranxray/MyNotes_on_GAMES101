# Lecture 17 Materials and Appearances

## What is Material in Computer Graphics

### Material == BRDF

1. Diffuse/Lambertian Material
   - Light is equally reflected in each output direction
   - 能量守恒: irradiance 不变
    ![alt text](image-141.png)
    albedo: 反射率

2. Glossy material 

3. Ideal reflective / refravtive material
   - perfect specular reflection
    ![alt text](image-142.png)
    方向由theta和phi共同定义
   - specular refraction 折射
    ![alt text](image-144.png)
   - Fresnel Reflection/Term 菲涅耳项
    ![alt text](image-145.png)
    ![alt text](image-146.png)
    ![alt text](image-147.png)
    ![alt text](image-148.png)

4. Microfacet Material 微表面模型: 忽略远处物体表面的粗糙
   - Rough surface
     - Macroscale: flat & rough
     - Microscale: bumpy & specular
   - Individual elements of surface act like mirrors
     - Known as Microfacets
     - Each microfacet has its own normal
   - Microfacet BRDF
     - key: the distribution of microfacets' normal
        ![alt text](image-149.png)
        ![alt text](image-150.png)

5. Isotropic/Anisotropic Materials 各向同性/各向异性
   - Key: directionality of underlying surface
    ![alt text](image-151.png)
   - Anisotropic BRDFs: Reflection depends on azimuthal angle $\phi$
     - $f_r(\theta_i,\phi_i;\theta_r,\phi_r) != f_r(\theta_i,\theta_r,\phi_r-\phi_i)$
     - Results from oriented microstructure of surface, e.g., brushed metal
        ![alt text](image-152.png)

6. Properties of BRDFs
   - Non-negativity: $f_r(\omega_i->\omega_r)\ge 0$
   - Linearity: $L_r(p,\omega_r)=\int_{H^2}f_r(p,\omega_i->\omega_r)L_i(p,\omega_i)\cos\theta_id\omega_i$
   - Reciprocity principle 可逆性: $f_r(\omega_r->\omega_i)=f_r(\omega_i->\omega_r)$
   - Energy conservtion 能量守恒: $\forall\omega_r\int_{H^2}f_r(\omega_i->\omega_r)\cos\theta_id\omega_i\le 1$
   - Isotropic v.s. anisotropic
   ![alt text](image-153.png)

7. Measuring BRDFs
   - Motivation
   ![alt text](image-154.png)
   - Image-Based BRDF Measurement
   ![alt text](image-155.png)
   ![alt text](image-156.png)
   - Tabular Representation
   ![alt text](image-157.png)