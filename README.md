# NexDynFEM

> NexDynFEM 是基于 **VegaFEM** 项目进行更新的一个计算高效且稳定的三维可变形物体物理仿真 C/C++ 库。它能够模拟大变形，包括几何和材料非线性，同时也能高效模拟线性系统。

## 目录

- [项目简介](#项目简介)
- [项目参考](#项目参考)
- [项目结构](#项目结构)
- [快速开始](#快速开始)
- [Windows 安装指南](#windows-安装指南)
- [WSL (Ubuntu) 安装指南](#wsl-ubuntu-安装指南)
- [故障排除](#故障排除)
- [致谢](#致谢)

---

## 项目简介

NexDynFEM 专为三维可变形物体的物理仿真而设计，具有以下特点：

- **高效计算**：优化的算法实现，支持大规模仿真
- **数值稳定**：稳定的积分方案和求解器
- **大变形支持**：支持几何和材料非线性
- **跨平台**：支持 Linux (WSL) 和 Windows

### 系统要求

| 平台 | 编译器 | 依赖管理 |
|------|--------|----------|
| Windows | MSVC 2019+ 或 Clang | vcpkg |
| Linux/WSL | GCC/Clang | apt + vcpkg |

### 主要依赖

- **线性代数**：OpenBLAS / LAPACK / Intel MKL
- **图形渲染**：OpenGL / GLUT / GLEW / GLUI
- **并行计算**：Intel TBB
- **GUI 框架**：wxWidgets
- **数值计算**：arpack-ng / CGAL / Eigen3

---

## 项目参考

本项目参考了 [VegaFEM](https://github.com/FabienPean/VegaFEM) 项目，这是一个计算高效且稳定的三维可变形物体物理仿真 C/C++ 库。

VegaFEM 的特点：
- 包含约 14.5 万行代码，开源且免费
- 采用 3-clause BSD 许可证，可用于学术研究和商业应用
- 提供距离网格（水平集）和四面体网格生成器
- 支持大变形仿真，包括几何和材料非线性

NexDynFEM 在 VegaFEM 的基础上进行了改进和扩展，包括：
- 使用 CMake 构建系统，支持跨平台编译
- 使用 OpenBLAS 和 LAPACK 作为 Intel MKL 的开源替代方案
- 修复了部分编译问题和平台兼容性问题
- 重构了代码框架，将核心功能模块分离，提高了代码的可维护性和可扩展性。

---

## 项目结构

```
libraries/
├── core/                    # 核心功能
│   ├── containers/          # 容器类和数据结构
│   ├── io/                  # 输入/输出操作
│   └── math/                # 数学工具
├── mesh/                    # 网格处理和操作
│   ├── geometry/            # 几何基元
│   ├── triMesh/             # 三角网格操作
│   ├── tetMesh/             # 四面体网格操作
│   ├── spatial/             # 空间数据结构
│   ├── predicates/          # 几何谓词
│   ├── operations/          # 网格操作
│   ├── windingNumber/       # 环绕数计算
│   ├── objMesh/             # OBJ 网格格式支持
│   ├── volumetricMesh/      # 体网格实现
│   ├── generation/          # 网格生成工具
│   └── processing/          # 网格处理工具
├── physics/                 # 物理仿真引擎
│   ├── force_models/        # 力模型
│   ├── integrators/         # 时间积分方案
│   ├── solvers/             # 线性求解器
│   └── systems/             # 物理系统
├── rendering/               # 渲染工具
├── utilities/               # 通用工具
└── include/                 # 公共头文件
```

---

## 快速开始

### 下载预编译二进制文件

如果只需要使用工具，最简单的方式是从 Release 页面下载预编译的二进制文件。

### 从源码构建

#### 方式一：Windows 平台

```cmd
:: 1. 克隆仓库
git clone https://github.com/W-Moorer/NexDynFEM.git
cd NexDynFEM

:: 2. 创建构建目录
mkdir build && cd build

:: 3. 配置 CMake
cmake .. -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DNEXDYNFEM_BUILD_COPYLEFT=OFF

:: 4. 编译项目
cmake --build . --config Release --parallel
```

#### 方式二：WSL/Ubuntu 平台

```bash
# 1. 克隆仓库
git clone https://github.com/W-Moorer/NexDynFEM.git
cd NexDynFEM

# 2. 创建构建目录
mkdir build && cd build

# 3. 配置 CMake
cmake .. -DNEXDYNFEM_BUILD_COPYLEFT=OFF

# 4. 编译项目
make -j$(nproc)
```

---

## Windows 安装指南

### 第一步：安装 Visual Studio

1. 下载并安装 [Visual Studio Community](https://visualstudio.microsoft.com/downloads/)
2. 选择 **"使用 C++ 的桌面开发"** 工作负载
3. 确保包含以下组件：
   - MSVC v143 - VS 2022 C++ x64/x86 生成工具
   - Windows 10/11 SDK
   - CMake 工具

### 第二步：安装 vcpkg

vcpkg 是 Windows 上管理 C++ 依赖的最佳工具。

```cmd
:: 1. 克隆 vcpkg 仓库
cd C:\
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

:: 2. 编译 vcpkg
.\bootstrap-vcpkg.bat

:: 3. 集成到 Visual Studio
.\vcpkg integrate install

:: 4. 设置环境变量 VCPKG_ROOT
setx VCPKG_ROOT "C:\vcpkg" /M
```

### 第三步：安装依赖库

```cmd
cd C:\vcpkg

:: 基础依赖
.\vcpkg install opengl-registry:x64-windows
.\vcpkg install freeglut:x64-windows
.\vcpkg install glew:x64-windows
.\vcpkg install tbb:x64-windows

:: GUI 相关依赖
.\vcpkg install glui:x64-windows
.\vcpkg install wxwidgets:x64-windows

:: 数学/几何库
.\vcpkg install arpack-ng:x64-windows
.\vcpkg install cgal:x64-windows
.\vcpkg install eigen3:x64-windows
.\vcpkg install openblas:x64-windows
.\vcpkg install lapack-reference:x64-windows
```

**注意**：安装过程可能需要 30-60 分钟。

### 第四步：克隆和构建项目

```cmd
:: 1. 克隆仓库
cd C:\
git clone https://github.com/W-Moorer/NexDynFEM.git
cd NexDynFEM

:: 2. 创建构建目录
mkdir build && cd build

:: 3. 配置 CMake（在 x64 Native Tools Command Prompt 中执行）
cmake .. -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DNEXDYNFEM_BUILD_COPYLEFT=OFF

:: 4. 编译项目
cmake --build . --config Release --parallel
```

### 第五步：验证安装

```cmd
cd C:\NexDynFEM\build\utilities\Release
.\displayObj.exe --help
```

### 第六步：配置运行环境（可选）

为了让程序能找到运行时依赖的 DLL：

**方案一**：将 DLL 复制到可执行文件目录
```cmd
cd C:\NexDynFEM\build\utilities\Release
copy "C:\vcpkg\installed\x64-windows\bin\*.dll" .
```

**方案二**：添加环境变量
- 打开 **系统属性** → **环境变量**
- 编辑 `Path` 变量，添加 `C:\vcpkg\installed\x64-windows\bin`

---

## WSL (Ubuntu) 安装指南

### 第一步：安装系统依赖

```bash
# 更新系统
sudo apt update && sudo apt upgrade -y

# 安装核心依赖
sudo apt install -y build-essential git cmake wget unzip \
    freeglut3-dev libxi-dev libxmu-dev \
    liblapack-dev libblas-dev \
    libglew-dev libglu1-mesa-dev \
    libwxgtk3.0-gtk3-dev
```

### 第二步：安装 vcpkg

```bash
cd ~
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
```

### 第三步：安装 vcpkg 依赖

```bash
./vcpkg install arpackng glui
```

### 第四步：克隆和构建项目

```bash
# 克隆仓库
cd ~
git clone https://github.com/W-Moorer/NexDynFEM.git
cd NexDynFEM

# 创建构建目录
mkdir build && cd build

# 配置 CMake
cmake .. -DNEXDYNFEM_BUILD_COPYLEFT=OFF

# 编译项目
make -j$(nproc)
```

### 第五步：验证安装

```bash
cd build/utilities
./displayObj --help
```

---

## 故障排除

### Windows 平台

#### 问题 1：找不到 vcpkg 工具链文件

**错误信息**：
```
Could not find toolchain file: C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

**解决方案**：
- 确认 vcpkg 安装路径正确
- 路径使用正斜杠 `/` 或双反斜杠 `\\`
- 确保已运行 `.\vcpkg integrate install`

#### 问题 2：找不到 OpenBLAS 或 LAPACK

**错误信息**：
```
Could not find OpenBLAS package
Could not find LAPACK package
```

**解决方案**：
```cmd
.\vcpkg install openblas:x64-windows
.\vcpkg install lapack-reference:x64-windows
```

#### 问题 3：运行时缺少 DLL

**错误信息**：
```
The code execution cannot proceed because openblas.dll was not found
```

**解决方案**：
```cmd
copy "C:\vcpkg\installed\x64-windows\bin\*.dll" .
```

#### 问题 4：链接错误 LNK2019

**错误信息**：
```
error LNK2019: unresolved external symbol __imp_gluPerspective
```

**解决方案**：
```cmd
.\vcpkg install freeglut:x64-windows
```

#### 问题 5：编译器版本不匹配

**错误信息**：
```
No CMAKE_C_COMPILER could be found
```

**解决方案**：
- 使用 **x64 Native Tools Command Prompt for VS** 而不是普通 cmd
- 重新安装 Visual Studio C++ 工具链

### WSL/Ubuntu 平台

#### 问题 1：找不到 MKL 包

**错误信息**：
```
Could not find MKL package
```

**解决方案**：
安装 Intel oneAPI MKL：
```bash
wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB | \
    gpg --dearmor | sudo tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null
echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" | \
    sudo tee /etc/apt/sources.list.d/oneAPI.list
sudo apt update
sudo apt install -y intel-oneapi-mkl-devel
source /opt/intel/oneapi/setvars.sh
```

#### 问题 2：找不到 arpackng 包

**错误信息**：
```
Could not find arpackng package
```

**解决方案**：
```bash
cd ~/vcpkg
./vcpkg install arpackng
```

#### 问题 3：找不到 glui 包

**错误信息**：
```
Could not find glui package
```

**解决方案**：
```bash
cd ~/vcpkg
./vcpkg install glui
```

#### 问题 4：GLU 函数未定义

**错误信息**：
```
undefined reference to `gluPerspective'
```

**解决方案**：
```bash
sudo apt install -y libglu1-mesa-dev
```

#### 问题 5：Target 链接到未导出的 target

**错误信息**：
```
Target 'nexdynfem' links to target 'igl_core' that is not in any export set
```

**解决方案**：
```bash
cmake .. -DNEXDYNFEM_BUILD_COPYLEFT=OFF
```

### 通用建议

1. **清理构建目录**：遇到奇怪错误时，删除 build 目录重新配置
2. **检查依赖版本**：确保所有库使用相同的架构（x64）
3. **使用并行构建**：`make -j$(nproc)` 或 `cmake --build . --parallel 4`
4. **保持工具更新**：定期更新 vcpkg 和系统包

---

## 致谢

本项目参考了 [VegaFEM](https://github.com/FabienPean/VegaFEM) 项目，感谢原作者和贡献者的辛勤工作。

VegaFEM 是一个优秀的三维可变形物体物理仿真库，为计算机图形学和物理仿真领域做出了重要贡献。NexDynFEM 在其基础上进行了改进和扩展，以更好地支持现代开发 workflow 和跨平台编译。

特别感谢：
- VegaFEM 的原作者和开发团队
- [FabienPean](https://github.com/FabienPean) 提供的 CMake 构建系统改进
- 所有为开源物理仿真库做出贡献的开发者

## 许可证

本项目开源且免费，具体许可证信息请参考项目仓库。

## 联系方式

如有问题或建议，请通过 GitHub Issues 提交。
