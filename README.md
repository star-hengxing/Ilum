# Ilum(WIP)

[![Windows](https://github.com/Chaf-Libraries/Ilum/actions/workflows/windows.yml/badge.svg)](https://github.com/Chaf-Libraries/Ilum/actions/workflows/windows.yml) [![Codacy Badge](https://app.codacy.com/project/badge/Grade/b0cb3a2729ee4be783dd5feb2cc67eb6)](https://www.codacy.com/gh/Chaf-Libraries/IlumEngine/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Chaf-Libraries/IlumEngine&amp;utm_campaign=Badge_Grade)

Ilum Graphics Playground, name after *Planet Ilum* from [Star Wars](

![image-20220424103827290](README/image-20220424103827290.png)

## Build

* Windows 10
* Visual Studio 2022
* C++17
* CMake 3.14+

Run script `build.bat`

## Hardware requirement

NVIDIA Turing GPUs (GeForce RTX 30/20 Series, GeForce GTX 16 Series) are the best, due to supporting for

* Mesh Shader
* Ray Tracing Pipeline
* GPU Acceleration Structure
* Descriptor Indexing

## Feature

* Architecture

  * Render Dependency Graph
    * Customize Render Pass (Graphics, Compute, Ray Tracing)
    * Render Pass Visualization
    * Auto Resource Transition
  * Runtime Shader Compilation and Reflection
    * GLSL -> `glslang` -> SPIR-V
    * HLSL -> `DXC` -> SPIR-V
    * SPIR-V -> `spirv-cross` -> Reflection Info
  * Entity Component System
  * Asynchronous Resource Loading
  * Scene Serialization

* Rendering

  * Mesh Shading Pipeline

    * Meshlet Rendering
    * GPU Frustum Culling
    * GPU Back-Face Cone Culling
    * Bindless Texture
    * GPU Hierarchy Z Buffer Occlusion Culling (Deprecated)

  * Deferred Shading

    | GBuffer | Format |      R      |       G       |        B        |        A        |
    | :--------: | :-----------------------------: | :---------: | :-----------: | :-------------: | :-------------: |
    | `0` |   `RGBA8U`   | `Albedo.r`  |   `Albedo.g`    |    `Albedo.b`     |   `Metallic`    |
    | `1` | `RGBA16F` |  `Normal.x`   |   `Normal.y`    |    `Normal.z`     | `Linear Depth`  |
    | `2` | `RGBA8U` | `Emissive.r`  |  `Emissive.g`   |   `Emissive.b`    |   `Roughness`   |
    | `3` | `RGBA16F` | `Entity ID` | `Instance ID` | `Motion Vector.x` | `Motion Vector.y` |

  * Material

    * For Real Time
      * Lambert Diffuse BRDF
        * Lambertian Reflection
      * Matte BRDF
        * Oren Nayar Reflection
        * Lambertian Reflection
      * Disney Principle BRDF
        * Kulla-Conty Approximation for Multi-Bounce Correction
    * For Offline
      * Matte BRDF
        * Oren Nayar Reflection
        * Lambertian Reflection
      * Plastic BRDF
        * Microfacet Reflection
        * Lambertian Reflection
      * Metal BRDF
        * Microfacet Reflection
      * Mirror BRDF
        * Specular Reflection
      * Glass BSDF
        * Fresnel Specular
        * Microfacet Reflection
        * Microfacet Transmission
      * Disney Principle BSDF
        * Disney Diffuse
        * Disney Fake Subsurface Scattering
        * Specular Transmission
        * Disney Retro
        * Disney Sheen
        * Disney Clearcoat
        * Microfacet Reflection
        * Microfacet Transmission
        * Lambertian Transmission

  * Image Based Lighting

    * Diffuse Term: Spherical Harmonics Projection
    * Specular Term: Split Sum Method

  * Shadow Mapping

    * Spot Light: Shadow Map
    * Directional Light: Cascade Shadow Map
    * Point Light: Omnidirectional Shadow Map

  * Soft Shadow

    * Percentage Closer Filtering (PCF)
    * Percentage Closer Soft Shadows (PCSS)

  * Anti-Aliasing

    * Fast approximate Anti-Aliasing (FXAA)

  * Path Tracing

    * Next Event Estimation
    * Light Source & BSDF Importance Sampling
    * Multi Importance Sampling
    * Russian Roulette

* Geometry
  * Curve Modeling
    * Bézier Curve
    * Cubic Spline Curve
    * B Spline Curve
    * Rational Bézier Curve
    * Rational B Spline Curve
  * Tensor Product Surface Modeling
    * Bézier Surface
    * B Spline Surface
    * Rational Bézier Surface
    * Rational B Spline Surface
  * Triangle Mesh Processing
    * Data Structure
      * Face Based Mesh
      * Edge Based Mesh
      * Half-Edge Mesh
    * Subdivision
      * Loop Subdivision

## Demo

**Render Pass Visualization**

![image-20220424111033580](README/image-20220424111033580.png)

**Mesh Shading**

![image-20211130105935862](README/image-20211130105935862.png)

**Hierarchy Z Buffer Generation**

![image-20220424111109937](README/image-20220424111109937.png)

**Deferred Shading**

|                           GBuffer0                           |                           GBuffer1                           |                           GBuffer2                           |                            Result                            |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| ![image-20220424114224795](README/image-20220424114224795.png) | ![image-20220424114147426](README/image-20220424114147426.png) | ![image-20220424114309646](README/image-20220424114309646.png) | ![image-20220424114350879](README/image-20220424114350879.png) |

**Shadow Map(Spot Light Shadow)**

![image-20220424114606665](README/image-20220424114606665.png)

**Cascade Shadow Map(Directional Light Shadow)**

![image-20220424114627387](README/image-20220424114627387.png)

**Omnidirectional Shadow Map(Point Light Shadow)**

![image-20220424114641418](README/image-20220424114641418.png)

**Percentage Closer Filtering**

|           PCF OFF            |            Uniform Sampling            |            Poisson Sampling            |
| :--------------------------: | :------------------------------------: | :------------------------------------: |
| ![no_pcf](README/no_pcf.png) | ![uniform_pcf](README/uniform_pcf.png) | ![poisson_pcf](README/poisson_pcf.png) |

**Percentage Closer Soft Shadows**

|           PCSS OFF           |             Uniform Sampling             |             Poisson Sampling             |
| :--------------------------: | :--------------------------------------: | :--------------------------------------: |
| ![no_pcf](README/no_pcf.png) | ![uniform_pcss](README/uniform_pcss.png) | ![poisson_pcss](README/poisson_pcss.png) |

**Image Based Lighting**

![IBL](README/IBL-16507723592991.png)

**Spherical Harmonic Projection**

![sh](README/sh.png)

**Split Sum**

|              Roughness=0.8               |              Roughness=0.6               |              Roughness=0.4               |              Roughness=0.2               |              Roughness=0.0               |
| :--------------------------------------: | :--------------------------------------: | :--------------------------------------: | :--------------------------------------: | :--------------------------------------: |
| ![roughness0.8](README/roughness0.8.png) | ![roughness0.6](README/roughness0.6.png) | ![roughness0.4](README/roughness0.4.png) | ![roughness0.2](README/roughness0.2.png) | ![roughness0.0](README/roughness0.0.png) |

**Path Tracing (Render in 1000 SPP)**

|           Matte            |           Metal            |            Plastic             |            Mirror            |
| :------------------------: | :------------------------: | :----------------------------: | :--------------------------: |
| ![matte](README/matte.png) | ![metal](README/metal.png) | ![plastic](README/plastic.png) | ![mirror](README/mirror.png) |

|             Substrate              |           Glass            |            Disney            |
| :--------------------------------: | :------------------------: | :--------------------------: |
| ![substrate](README/substrate.png) | ![glass](README/glass.png) | ![disney](README/disney.png) |

![spaceship](README/spaceship.png)

![coffee](README/coffee.png)

**Bloom**

|                     Bloom OFF                     |                    Bloom ON                     |
| :-----------------------------------------------: | :---------------------------------------------: |
| ![bloom_off](README/bloom_off-16509578159532.png) | ![bloom_on](README/bloom_on-16509578198833.png) |

**Fast Approximate Anti-Aliasing (FXAA)**

|             FXAA OFF             |            FXAA ON             |
| :------------------------------: | :----------------------------: |
| ![fxaa_off](README/fxaa_off.png) | ![fxaa_on](README/fxaa_on.png) |

**Curve Modeling**

![image-20220108150839809](README/image-20220108150839809.png)

**Surface Modeling**

![image-20220108151149909](README/image-20220108151149909.png)

**Loop Subdivision**

|           Origin           |        Iteration #1        |        Iteration #2        |        Iteration #3        |        Iteration #4        |
| :------------------------: | :------------------------: | :------------------------: | :------------------------: | :------------------------: |
| ![loop0](README/loop0.png) | ![loop1](README/loop1.png) | ![loop2](README/loop2.png) | ![loop3](README/loop3.png) | ![loop4](README/loop4.png) |

**Minimum Surface**

|          Origin          |             Minimum Surface              |
| :----------------------: | :--------------------------------------: |
| ![face](README/face.png) | ![mini_surface](README/mini_surface.png) |

**Tutte Parameterization**

**Origin Mesh**

<img src="README/origin.png" alt="origin" style="zoom:50%;" />

|                                       |                       UV Visualization                       |              Parameterization Visualization              |
| :-----------------------------------: | :----------------------------------------------------------: | :------------------------------------------------------: |
|   Circle Boundary + Uniform Weight    |         ![uniform_circle](README/uniform_circle.png)         |   ![uniform_circle_vis](README/uniform_circle_vis.png)   |
|  Rectangle Boundary + Uniform Weight  |       ![uniform_rectange](README/uniform_rectange.png)       | ![uniform_rectange_vis](README/uniform_rectange_vis.png) |
|  Circle Boundary + Cotangent Weight   |       ![cotangent_circle](README/cotangent_circle.png)       | ![cotangent_circle_vis](README/cotangent_circle_vis.png) |
| Rectangle Boundary + Cotangent Weight | ![cotangent_rectange_vis](README/cotangent_rectange_vis.png) |   ![cotangent_rectange](README/cotangent_rectange.png)   |

## Dependencies

* [ImFileDialog](https://github.com/dfranx/ImFileDialog)
* [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
* [assimp](https://github.com/assimp/assimp)
* [cereal](https://github.com/USCiLab/cereal)
* [DirectXCompiler](https://github.com/microsoft/DirectXShaderCompiler)
* [eigen](https://gitlab.com/libeigen/eigen)
* [entt](https://github.com/skypjack/entt)
* [glm](https://github.com/g-truc/glm)
* [glslang](https://github.com/KhronosGroup/glslang)
* [imgui](https://github.com/ocornut/imgui)
* [imgui-node-editor](https://github.com/thedmd/imgui-node-editor)
* [stb](https://github.com/nothings/stb)
* [VulkanMemoryAllocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
* [volk](https://github.com/zeux/volk)
* [Vulkan-Headers](https://github.com/KhronosGroup/Vulkan-Headers)
* [oneTBB](https://github.com/oneapi-src/oneTBB)
* [meshoptimizer](https://github.com/zeux/meshoptimizer)
* [spdlog](https://github.com/gabime/spdlog)
* [SDL](https://github.com/libsdl-org/SDL)
* [SPIRV-Cross](https://github.com/KhronosGroup/SPIRV-Cross)

## Reference

* [https://www.pbr-book.org/](https://www.pbr-book.org/)
* [http://www.realtimerendering.com/](http://www.realtimerendering.com/)
* [https://learnopengl-cn.github.io/](https://learnopengl-cn.github.io/)
* [https://hazelengine.com/](https://hazelengine.com/)
* [https://advances.realtimerendering.com/s2015/aaltonenhaar_siggraph2015_combined_final_footer_220dpi.pdf](https://advances.realtimerendering.com/s2015/aaltonenhaar_siggraph2015_combined_final_footer_220dpi.pdf)
* [https://www.gdcvault.com/play/1024612/FrameGraph-Extensible-Rendering-Architecture-in](https://www.gdcvault.com/play/1024612/FrameGraph-Extensible-Rendering-Architecture-in)
* [https://github.com/SaschaWillems/Vulkan](https://github.com/SaschaWillems/Vulkan)
* [https://github.com/KhronosGroup/Vulkan-Samples](https://github.com/KhronosGroup/Vulkan-Samples)
* [https://github.com/wdas/brdf](https://github.com/wdas/brdf)
* [http://blog.selfshadow.com/publications/s2015-shading-course/burley/s2015_pbs_disney_bsdf_notes.pdf.](http://blog.selfshadow.com/publications/s2015-shading-course/burley/s2015_pbs_disney_bsdf_notes.pdf.)
* [https://www.froyok.fr/blog/2021-12-ue4-custom-bloom/](https://www.froyok.fr/blog/2021-12-ue4-custom-bloom/)

