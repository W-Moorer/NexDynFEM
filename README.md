# NexDynFEM

> NexDynFEM is a computationally efficient and stable C/C++ physics library for three-dimensional deformable object simulation. It is designed to model large deformations, including geometric and material nonlinearities, and can also efficiently simulate linear systems. NexDynFEM contains about 145,000 lines of code, and is open-source and free.

## Quickstart

If you just need the utilities, the simplest is to download the binaries in the release section. Otherwise you can build the repository on your system assuming the following:

* A Linux with Clang or Windows with Clang or MSVC
* [Intel oneAPI MKL](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html) is installed on the system
* As well as the following dependencies: `intel-mkl opengl glui glew cgal openblas eigen3` which can be obtained via [vcpkg](https://vcpkg.io/en/index.html)
* CMake 3.21

## Project Structure

The NexDynFEM library has been reorganized into a functional domain-based structure for better maintainability and clarity:

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

This guide provides step-by-step instructions for building NexDynFEM in a WSL (Windows Subsystem for Linux) environment.

### Step 1: Prepare WSL Environment and Dependencies

First, ensure you have WSL installed (typically Ubuntu). Open your WSL terminal and execute the following commands to update the system and install necessary compilers and graphics libraries.

NexDynFEM depends on C/C++ compilers, OpenGL utility libraries (GLUT/GLUI), and linear algebra libraries (BLAS/LAPACK).

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
- `freeglut3-dev`: OpenGL utilities required for NexDynFEM graphics interface
- `liblapack-dev` / `libblas-dev`: Numerical computing libraries (NexDynFEM can also use Intel MKL, but system BLAS/LAPACK is simplest and least error-prone)

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

### Step 6: Clone and Build NexDynFEM

Clone the repository:

```bash
cd ~
git clone https://github.com/W-Moorer/NexDynFEM.git
cd NexDynFEM
```

Create a build directory and configure CMake:

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="/opt/intel/oneapi/mkl/latest;/root/vcpkg/installed/x64-linux" -DNEXDYNFEM_BUILD_COPYLEFT=OFF
```

Note: Adjust the MKL path if your version is different (check `/opt/intel/oneapi/mkl/` for the actual version number).

### Step 7: Build the Project

Build with multiple cores:

```bash
make -j$(nproc)
```

The build process will compile the NexDynFEM library and all utilities. Once complete, you can find the executables in the `build/utilities/` directory.

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
cmake .. -DCMAKE_PREFIX_PATH="/opt/intel/oneapi/mkl/2025.3;/root/vcpkg/installed/x64-linux" -DNEXDYNFEM_BUILD_COPYLEFT=OFF
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
Target 'nexdynfem' links to target 'igl_core' that is not in any export set
```

**Solution:**
Disable copyleft components in CMake configuration:
```bash
cmake .. -DNEXDYNFEM_BUILD_COPYLEFT=OFF
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

---

## Installation Guide for Windows

本指南提供在 Windows 平台上构建 NexDynFEM 的详细步骤。

### 系统要求

- Windows 10/11 (64位)
- Visual Studio 2019 或更高版本（需安装 C++ 桌面开发工作负载）
- CMake 3.21 或更高版本
- Git for Windows

### 依赖项概览

NexDynFEM 在 Windows 上需要以下依赖：

| 依赖项 | 用途 | 安装方式 |
|--------|------|----------|
| Intel oneAPI MKL | 线性代数计算库 | 官方安装包 |
| vcpkg | C++ 包管理器 | 源码编译 |
| OpenGL/GLUT/GLEW | 图形渲染 | vcpkg |
| TBB | 并行计算 | vcpkg |
| GLUI | GUI 界面 | vcpkg |
| wxWidgets | 跨平台 GUI | vcpkg |
| arpackng | 特征值计算 | vcpkg |
| CGAL | 计算几何 | vcpkg |
| Eigen3 | 矩阵运算 | vcpkg |

### Step 1: 安装 Visual Studio

1. 下载并安装 [Visual Studio Community](https://visualstudio.microsoft.com/downloads/)
2. 在安装过程中选择 **"使用 C++ 的桌面开发"** 工作负载
3. 确保包含以下组件：
   - MSVC v143 - VS 2022 C++ x64/x86 生成工具（或对应版本）
   - Windows 10/11 SDK
   - CMake 工具（可选，也可单独安装）

### Step 2: 安装 Intel oneAPI MKL

1. 下载 [Intel oneAPI Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html)
2. 运行安装程序，选择自定义安装
3. 确保选中 **Intel oneAPI Math Kernel Library (MKL)**
4. 完成安装并记录安装路径（默认为 `C:\Program Files (x86)\Intel\oneAPI\`）

### Step 3: 安装 CMake

**方式一：通过 Visual Studio 安装**
- 已在 Step 1 中完成

**方式二：独立安装**
1. 下载 [CMake Windows 安装包](https://cmake.org/download/)
2. 安装时选择 **"Add CMake to the system PATH"**
3. 验证安装：
   ```cmd
   cmake --version
   ```

### Step 4: 安装和配置 vcpkg

vcpkg 是 Windows 上管理 C++ 依赖的最佳工具。

1. 打开 **x64 Native Tools Command Prompt for VS**（在开始菜单中找到）

2. 克隆 vcpkg 仓库：
   ```cmd
   cd C:\
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   ```

3. 编译 vcpkg：
   ```cmd
   .\bootstrap-vcpkg.bat
   ```

4. 集成到 Visual Studio：
   ```cmd
   .\vcpkg integrate install
   ```

5. 设置环境变量 `VCPKG_ROOT`：
   - 打开 **系统属性** → **环境变量**
   - 新建系统变量：`VCPKG_ROOT = C:\vcpkg`
   - 编辑 `Path` 变量，添加 `%VCPKG_ROOT%`

### Step 5: 通过 vcpkg 安装依赖库

在 vcpkg 目录下，安装所有需要的库（x64-windows  triplet）：

```cmd
cd C:\vcpkg

:: 安装基础依赖
.\vcpkg install opengl-registry:x64-windows
.\vcpkg install freeglut:x64-windows
.\vcpkg install glew:x64-windows
.\vcpkg install tbb:x64-windows

:: 安装 GUI 相关依赖
.\vcpkg install glui:x64-windows
.\vcpkg install wxwidgets:x64-windows

:: 安装数学/几何库
.\vcpkg install arpack-ng:x64-windows
.\vcpkg install cgal:x64-windows
.\vcpkg install eigen3:x64-windows
.\vcpkg install openblas:x64-windows
.\vcpkg install lapack-reference:x64-windows
```

**注意**：安装过程可能需要 30-60 分钟，取决于网络速度和硬件配置。

### Step 6: 克隆 NexDynFEM 仓库

```cmd
cd C:\
git clone https://github.com/W-Moorer/NexDynFEM.git
cd NexDynFEM
```

### Step 7: 配置 CMake

创建构建目录并运行 CMake 配置：

```cmd
mkdir build
cd build

:: 配置项目（单条命令）
cmake .. -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DNEXDYNFEM_BUILD_COPYLEFT=OFF
```

**注意**：本项目使用 OpenBLAS 和 LAPACK 作为 Intel MKL 的开源替代方案，无需安装 Intel oneAPI MKL。

**参数说明**：
- `-G "Visual Studio 17 2022"`：指定生成器（VS2022），根据你的版本调整
  - VS2019: `"Visual Studio 16 2019"`
  - VS2022: `"Visual Studio 17 2022"`
- `-A x64`：指定 64 位架构
- `-DCMAKE_TOOLCHAIN_FILE`：vcpkg 工具链文件路径
- `-DNEXDYNFEM_BUILD_COPYLEFT=OFF`：禁用 copyleft 组件（避免 igl_core 链接问题）

### Step 8: 构建项目

**方式一：使用 CMake 命令行**

```cmd
cmake --build . --config Release --parallel
```

**方式二：使用 Visual Studio**

1. 在 build 目录中找到 `NexDynFEM.sln`
2. 双击打开解决方案
3. 在顶部工具栏选择 **Release** 配置和 **x64** 平台
4. 选择菜单 **生成** → **生成解决方案**（或按 Ctrl+Shift+B）

构建完成后，可执行文件位于：
- `C:\NexDynFEM\build\utilities\Release\`

### Step 9: 验证安装

测试一个简单工具验证安装：

```cmd
cd C:\NexDynFEM\build\utilities\Release
displayObj.exe --help
```

如果显示帮助信息，说明安装成功！

### Step 10: 运行环境配置（可选）

为了让程序能找到运行时依赖的 DLL，需要设置环境变量：

1. 找到 vcpkg 运行时库路径：
   ```
   C:\vcpkg\installed\x64-windows\bin
   ```

2. 添加到系统 Path 环境变量：
   - 打开 **系统属性** → **环境变量**
   - 编辑 `Path` 变量，添加 `C:\vcpkg\installed\x64-windows\bin`

3. 或者将所需的 DLL 复制到可执行文件目录：
   ```cmd
   cd C:\NexDynFEM\build\utilities\Release
   copy "C:\vcpkg\installed\x64-windows\bin\*.dll" .
   ```

---

## Windows 平台故障排除

### 错误 1: 找不到 vcpkg 工具链文件

**错误信息：**
```
Could not find toolchain file: C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

**解决方案：**
- 确认 vcpkg 安装路径正确
- 检查路径是否使用了正斜杠 `/` 或双反斜杠 `\\`
- 确保已运行 `.\vcpkg integrate install`

### 错误 2: 找不到 OpenBLAS 或 LAPACK 包

**错误信息：**
```
Could not find OpenBLAS package
Could not find LAPACK package
```

**解决方案：**
安装 OpenBLAS 和 LAPACK：
```cmd
.\vcpkg install openblas:x64-windows
.\vcpkg install lapack-reference:x64-windows
```

### 错误 3: 找不到 TBB 包

**错误信息：**
```
Could not find TBB CONFIG
```

**解决方案：**
```cmd
.\vcpkg install tbb:x64-windows
```

### 错误 4: 找不到 GLUI 包

**错误信息：**
```
Could not find glui CONFIG
```

**解决方案：**
```cmd
.\vcpkg install glui:x64-windows
```

### 错误 5: 找不到 wxWidgets 包

**错误信息：**
```
Could not find wxWidgets
```

**解决方案：**
```cmd
.\vcpkg install wxwidgets:x64-windows
```

### 错误 6: 编译器版本不匹配

**错误信息：**
```
No CMAKE_C_COMPILER could be found
```

**解决方案：**
- 确保使用 **x64 Native Tools Command Prompt for VS** 而不是普通 cmd
- 或重新安装 Visual Studio C++ 工具链

### 错误 7: 运行时缺少 DLL

**错误信息：**
```
The code execution cannot proceed because openblas.dll was not found
```

**解决方案：**
1. 将 vcpkg 的 DLL 复制到可执行文件目录：
   ```cmd
   copy "C:\vcpkg\installed\x64-windows\bin\*.dll" .
   ```
2. 或将 vcpkg bin 目录添加到系统 Path：
   ```
   C:\vcpkg\installed\x64-windows\bin
   ```

### 错误 8: 链接错误 LNK2019（未解析的外部符号）

**错误信息：**
```
error LNK2019: unresolved external symbol __imp_gluPerspective
```

**解决方案：**
确保 OpenGL 和 GLU 库正确链接。CMake 已配置为使用 `OPENGL_glu_LIBRARY`，如果仍有问题，检查 vcpkg 的 freeglut 是否正确安装：
```cmd
.\vcpkg install freeglut:x64-windows
```

### 错误 9: CGAL 或 Eigen3 找不到

**错误信息：**
```
Could not find CGAL CONFIG
Could not find Eigen3 CONFIG
```

**解决方案：**
```cmd
.\vcpkg install cgal:x64-windows eigen3:x64-windows
```

### 错误 10: 构建时内存不足

**错误信息：**
```
fatal error C1060: compiler is out of heap space
```

**解决方案：**
1. 使用并行度较低的构建：
   ```cmd
   cmake --build . --config Release --parallel 2
   ```
2. 关闭 Visual Studio 其他项目
3. 增加系统虚拟内存

### Windows 平台通用建议

1. **始终使用 x64 Native Tools Command Prompt**：确保使用正确的编译器环境
2. **路径使用正斜杠或双反斜杠**：在 CMake 命令中避免使用单反斜杠
3. **检查 vcpkg  triplet**：确保所有库使用相同的 triplet（推荐 `x64-windows`）
4. **保持 vcpkg 更新**：定期运行 `git pull` 和 `.\bootstrap-vcpkg.bat`
5. **清理构建目录**：遇到奇怪错误时，删除 build 目录重新配置
6. **使用静态链接**：如需简化部署，可考虑使用 `x64-windows-static` triplet



