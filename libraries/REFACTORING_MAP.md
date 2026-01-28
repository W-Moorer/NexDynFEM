# VegaFEM Libraries 重构映射表

## 方案一：按功能域分层

### 1. core/ - 核心数学和工具

#### core/math/ - 数学计算
- minivector/
- matrix/
- sparseMatrix/
- quaternion/
- polarDecomposition/

#### core/data_structures/ - 数据结构
- hashTable/
- graph/
- listIO/

#### core/io/ - 输入输出
- matrixIO/
- imageIO/
- configFile/
- getopts/

### 2. mesh/ - 网格相关

#### mesh/core/ - 基础网格
- mesh/
- volumetricMesh/
- objMesh/

#### mesh/generation/ - 网格生成
- mesher/
- distanceField/

#### mesh/processing/ - 网格处理
- shapeEdit/
- interpolationCoordinates/

### 3. physics/ - 物理模拟

#### physics/force_models/ - 力模型
- forceModel/
- elasticForceModel/
- reducedElasticForceModel/
- stencilForceModel/

#### physics/integrators/ - 积分器
- integrator/
- integratorDense/
- integratorSparse/

#### physics/solvers/ - 求解器
- sparseSolver/

#### physics/systems/ - 物理系统
- massSpringSystem/
- corotationalLinearFEM/
- isotropicHyperelasticFEM/
- stvk/
- reducedStvk/
- reducedForceModel/

### 4. rendering/ - 渲染相关

#### rendering/graphics/ - 图形渲染
- openGLHelper/
- glslPhong/
- lighting/
- camera/

#### rendering/scene/ - 场景对象
- sceneObject/
- sceneObjectReduced/
- renderVolumetricMesh/

#### rendering/deformers/ - 变形器
- objMeshGPUDeformer/

### 5. utilities/ - 工具类

#### utilities/performance/ - 性能工具
- performanceCounter/

#### utilities/math/ - 数学工具
- basicAlgorithms/
- laplacianMatrix/
- modalMatrix/

#### utilities/constraints/ - 约束
- constrainedDOFs/

#### utilities/rigid_body/ - 刚体动力学
- rigidBodyDynamics/

#### utilities/cloth/ - 布料模拟
- clothBW/

#### utilities/animation/ - 动画工具
- animationHelper/

### 6. third_party/ - 第三方接口
- exactArithmetic/
- libiglInterface/
- immersionMesher/
- virtualTets/

### 7. 特殊目录
- include/ -> 保留在根目录
- private/ -> 保留在根目录
