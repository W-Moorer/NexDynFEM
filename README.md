# Vega FEM

**Disclaimer:** This repository is an independent fork and is not affiliated with or endorsed by the original developers of the project. The content herein is maintained separately and may differ from the original project.

Excerpt from the original [website](https://viterbi-web.usc.edu/~jbarbic/vega):

> Vega is a computationally efficient and stable C/C++ physics library for three-dimensional deformable object simulation. It is designed to model large deformations, including geometric and material nonlinearities, and can also efficiently simulate linear systems. Vega contains about 145,000 lines of code, and is open-source and free. It is released under the [3-clause BSD license](http://en.wikipedia.org/wiki/BSD_licenses), which means that it can be used freely both in academic research and in commercial applications.

This repository consists mostly of providing CMake files for simpler and cross-platform build generation, fixing bugs and C-ism. Currently, it is compiling and generating the binaries for Linux and Windows, see the [CI](https://github.com/FabienPean/VegaFEM/actions) script to see how.

## Motivation

The Vega FEM library is relatively less known due to its official absence from principal git forges (GitHub, GitLab, BitBucket, etc). While initially developed for [research](https://doi.org/10.1145/3197517.3201327), you ~~can~~ could see it perform commercially in [Ziva VFX](https://web.archive.org/web/20231002072203/https://docs.zivadynamics.com/vfx/third_party_licenses.html#vega-fem) from [Ziva Dynamics](https://web.archive.org/web/20220804053547/https://zivadynamics.com/) until being acquired and [scraped off](https://unity.com/blog/news/update-about-ziva) by Unity Technologies.

The library provides many necessary tools for the development of physics-based animation with a permissive license. In particular, it contains a distance grid (level set) and tetrahedral mesh generators with little to no dependencies. Common alternatives are [TetGen](https://wias-berlin.de/software/index.jsp?id=TetGen), which is under a [copyleft license](https://tldrlegal.com/license/gnu-affero-general-public-license-v3-(agpl-3.0)), or [fTetWild](https://github.com/wildmeshing/fTetWild), which is a patchwork of many libraries not so easy to build all together.

Former forks available on GitHub are relatively old and with no modification. This fork contains the most recent version accompanied with fixes and a build generator based on CMake.

## Quickstart

If you just need the utilities, the simplest is to download the binaries in the release section. Otherwise you can build the repository on your system assuming the following:

* A Linux with Clang or Windows with Clang or MSVC
* [Intel oneAPI MKL](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html) is installed on the system
* As well as the following dependencies: `intel-mkl opengl glui glew cgal openblas eigen3` which can be obtained via [vcpkg](https://vcpkg.io/en/index.html)
* CMake 3.21

## Project Structure

The VegaFEM library has been reorganized into a functional domain-based structure for better maintainability and clarity:

```
libraries/
├── core/                    # Core functionality
│   ├── containers/          # Container classes and data structures
│   ├── io/                  # Input/output operations
│   └── math/                # Mathematical utilities
├── mesh/                    # Mesh processing and operations
│   ├── geometry/            # Geometric primitives (BoundingBox, Plane, Sphere)
│   ├── triMesh/             # Triangular mesh operations
│   ├── tetMesh/             # Tetrahedral mesh operations
│   ├── spatial/             # Spatial data structures (Octree, EdgeKey)
│   ├── predicates/          # Geometric predicates
│   ├── operations/          # Mesh operations (intersection, query)
│   ├── windingNumber/       # Winding number computation
│   ├── objMesh/             # OBJ mesh format support
│   ├── volumetricMesh/      # Volumetric mesh implementations
│   ├── generation/          # Mesh generation tools
│   │   ├── mesher/          # Tetrahedral and isosurface meshers
│   │   └── distanceField/   # Distance field computation
│   └── processing/          # Mesh processing tools
│       ├── shapeEdit/       # Shape editing (ARAP deformation)
│       └── interpolationCoordinates/  # Interpolation schemes
├── physics/                 # Physics simulation engine
│   ├── force_models/        # Force models (elastic, reduced, stencil)
│   ├── integrators/         # Time integration schemes
│   ├── solvers/             # Linear solvers
│   └── systems/             # Physical systems
├── rendering/               # Rendering utilities
├── utilities/               # General utilities
├── third_party/             # Third-party libraries
├── windingNumber/           # Standalone winding number library
├── include/                 # Public header files
└── private/                 # Private implementation details
```

### Key Components

- **Mesh Module**: Comprehensive mesh processing library supporting triangular and tetrahedral meshes, with tools for generation, manipulation, and geometric queries.
- **Physics Module**: Physics simulation engine supporting various force models, integration schemes, and linear solvers for deformable object simulation.
- **Core Module**: Fundamental data structures, mathematical utilities, and I/O operations used throughout the library.
- **Rendering Module**: OpenGL-based rendering utilities for visualization and interactive simulation.

## Installation Guide for WSL (Ubuntu)

This guide provides step-by-step instructions for building VegaFEM in a WSL (Windows Subsystem for Linux) environment.

### Step 1: Prepare WSL Environment and Dependencies

First, ensure you have WSL installed (typically Ubuntu). Open your WSL terminal and execute the following commands to update the system and install necessary compilers and graphics libraries.

VegaFEM depends on C/C++ compilers, OpenGL utility libraries (GLUT/GLUI), and linear algebra libraries (BLAS/LAPACK).

Update package sources:

```bash
sudo apt update && sudo apt upgrade -y
```

Install core dependencies:

```bash
sudo apt install -y build-essential git cmake wget unzip \
freeglut3-dev libxi-dev libxmu-dev \
liblapack-dev libblas-dev \
libglew-dev
```

- `build-essential`: Installs GCC/G++ compilers
- `freeglut3-dev`: OpenGL utilities required for VegaFEM graphics interface
- `liblapack-dev` / `libblas-dev`: Numerical computing libraries (VegaFEM can also use Intel MKL, but system BLAS/LAPACK is simplest and least error-prone)

### Step 2: Install Additional Dependencies

Install wxWidgets (required for some utilities):

```bash
sudo apt install -y libwxgtk3.0-gtk3-dev
```

Install GLU (OpenGL Utility Library):

```bash
sudo apt install -y libglu1-mesa-dev
```

### Step 3: Install vcpkg

vcpkg is used to manage additional dependencies like arpackng and glui.

```bash
cd ~
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
```

### Step 4: Install Dependencies via vcpkg

Install arpackng and glui:

```bash
./vcpkg install arpackng glui
```

### Step 5: Install Intel oneAPI MKL

Download and install Intel oneAPI Base Toolkit which includes MKL:

```bash
wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB | gpg --dearmor | sudo tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null
echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" | sudo tee /etc/apt/sources.list.d/oneAPI.list
sudo apt update
sudo apt install -y intel-oneapi-mkl-devel
```

Set up environment variables (add to your `~/.bashrc` for persistence):

```bash
source /opt/intel/oneapi/setvars.sh
```

### Step 6: Clone and Build VegaFEM

Clone the repository:

```bash
cd ~
git clone https://github.com/FabienPean/VegaFEM.git
cd VegaFEM
```

Create a build directory and configure CMake:

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="/opt/intel/oneapi/mkl/latest;/root/vcpkg/installed/x64-linux" -DVEGAFEM_BUILD_COPYLEFT=OFF
```

Note: Adjust the MKL path if your version is different (check `/opt/intel/oneapi/mkl/` for the actual version number).

### Step 7: Build the Project

Build with multiple cores:

```bash
make -j$(nproc)
```

The build process will compile the VegaFEM library and all utilities. Once complete, you can find the executables in the `build/utilities/` directory.

### Step 8: Verify Installation

Test a simple utility to verify the installation:

```bash
cd utilities
./displayObj --help
```

If the command executes without errors, your installation is successful!

## Troubleshooting

This section documents common errors encountered during the build process and their solutions, based on actual build experience.

### Error 1: Could not find MKL package

**Error Message:**
```
Could not find MKL package
```

**Solution:**
Ensure Intel MKL is installed and specify the correct path in CMake:
```bash
# Check MKL installation
ls /opt/intel/oneapi/mkl/

# Use the actual version number in CMake
cmake .. -DCMAKE_PREFIX_PATH="/opt/intel/oneapi/mkl/2025.3;/root/vcpkg/installed/x64-linux" -DVEGAFEM_BUILD_COPYLEFT=OFF
```

### Error 2: Could not find arpackng package

**Error Message:**
```
Could not find arpackng package
```

**Solution:**
Install arpackng via vcpkg:
```bash
cd ~/vcpkg
./vcpkg install arpackng
```

### Error 3: Could not find glui package

**Error Message:**
```
Could not find glui package
```

**Solution:**
Install glui via vcpkg:
```bash
cd ~/vcpkg
./vcpkg install glui
```

### Error 4: Could not find wxWidgets package

**Error Message:**
```
Could not find wxWidgets package
```

**Solution:**
Install wxWidgets development libraries:
```bash
sudo apt install -y libwxgtk3.0-gtk3-dev
```

### Error 5: Target links to target not in any export set

**Error Message:**
```
Target 'vegafem' links to target 'igl_core' that is not in any export set
```

**Solution:**
Disable copyleft components in CMake configuration:
```bash
cmake .. -DVEGAFEM_BUILD_COPYLEFT=OFF
```

### Error 6: Undefined reference to GLU functions

**Error Message:**
```
undefined reference to `gluPerspective'
undefined reference to `gluOrtho2D'
undefined reference to `gluUnProject'
undefined reference to `gluLookAt'
undefined reference to `gluBuild2DMipmaps'
undefined reference to `gluErrorString'
```

**Solution:**
This error occurs because GLU is not properly linked. The CMakeLists.txt files need to be modified to use `OPENGL_glu_LIBRARY` instead of `GLU_LIBRARIES`.

In `CMakeLists.txt`, change:
```cmake
find_package(GLU REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLU_LIBRARIES})
```
To:
```cmake
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL ${OPENGL_glu_LIBRARY})
```

In `utilities/CMakeLists.txt`, add GLU to the target_link_libraries:
```cmake
target_link_libraries(${exe} PRIVATE ${PROJECT_NAME} 
    OpenGL::GL 
    GLUT::GLUT
    ${OPENGL_glu_LIBRARY}
    $<$<PLATFORM_ID:Linux,Darwin>:X11::X11>
)
```

### Error 7: GLU not found by CMake

**Error Message:**
```
GLU not found
```

**Solution:**
Install GLU development libraries:
```bash
sudo apt install -y libglu1-mesa-dev
```

### General Tips

- Always verify that all dependencies are installed before running CMake configuration
- Check the actual version numbers in `/opt/intel/oneapi/mkl/` and adjust paths accordingly
- Use `make -j$(nproc)` for parallel builds to speed up compilation
- If you encounter linker errors, check that all required libraries are properly linked in CMakeLists.txt

## License

The library itself is released under the BSD 3-clause. 

However, subfolders `exactArithmetic`, `libiglInterface`, `immersionMesher`, and `virtualTets`, have a dependency on the [Polygon Mesh Processing](https://doc.cgal.org/latest/Polygon_mesh_processing/group__PkgPolygonMeshProcessingRef.html) package from [CGAL](https://www.cgal.org/) which is released under the GPL. VegaFEM can be built without the copyleft components by setting the CMake option `VEGAFEM_BUILD_COPYLEFT` to OFF.



