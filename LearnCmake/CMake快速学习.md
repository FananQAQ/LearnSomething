# CMake 快速学习指南（详细版）

这份文档会从“原理”讲到“可运行样例”，目标是让你不仅会写，还知道为什么这么写。

---

## 1) CMake 的工作原理（先理解再记命令）

CMake 不是编译器，它的职责是**生成编译器需要的构建文件**。  
你可以把它理解为：

- 你写 `CMakeLists.txt`（描述“我要构建什么”）
- CMake 做“配置阶段”（configure），检查编译器、平台、依赖
- CMake 做“生成阶段”（generate），生成 Visual Studio 工程 / Ninja / Makefile
- 然后由底层工具真正编译链接

核心流程：

1. Configure：读取脚本、解析变量、检查工具链
2. Generate：输出构建系统
3. Build：执行编译和链接

常用命令：

```bash
# 配置
cmake -S . -B build

# 构建
cmake --build build

# 安装（可选）
cmake --install build --prefix ./install
```

---

## 2) 一切围绕 target（最重要的思想）

CMake 的现代写法核心是：**每个可执行文件/库都是一个 target**，配置尽量“挂在 target 上”。

常见 target：

- `add_executable(app ...)` 可执行程序
- `add_library(math_utils ...)` 库（静态/动态/接口）

为什么强调 target？

- 配置不会污染全局
- 依赖关系清晰
- 可维护性高（大项目非常明显）

---

## 3) 最小可运行示例 + 逐行解释

```cmake
cmake_minimum_required(VERSION 3.16)
project(hello_cmake LANGUAGES CXX)

add_executable(hello main.cpp)
```

解释：

- `cmake_minimum_required`：约束最低版本，避免旧行为差异
- `project`：定义项目名和语言（这里是 C++）
- `add_executable`：告诉 CMake 生成一个叫 `hello` 的可执行文件

---

## 4) C++ 标准配置为什么这么写

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

原理：

- `CMAKE_CXX_STANDARD`：目标是 C++17
- `REQUIRED ON`：如果编译器不支持，就直接报错，而不是悄悄降级
- `EXTENSIONS OFF`：禁用编译器私有扩展（如 `gnu++17`），更可移植

---

## 5) include 路径和链接：PUBLIC / PRIVATE / INTERFACE

这三个关键字决定“配置是否传递给依赖方”。

### 5.1 含义

- `PRIVATE`：只对当前 target 生效
- `PUBLIC`：当前 target + 依赖当前 target 的下游都生效
- `INTERFACE`：只对下游生效，当前 target 本身不使用

### 5.2 例子（math 库被 app 使用）

```cmake
add_library(math_utils src/math_utils.cpp)
target_include_directories(math_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE math_utils)
```

为什么 `math_utils` 的 include 用 `PUBLIC`？

- 因为 `app` 需要包含 `math_utils.h`
- 如果写 `PRIVATE`，`app` 可能找不到头文件

---

## 6) 变量、缓存与 option（配置开关）

```cmake
option(ENABLE_VERBOSE_LOG "Enable verbose log output" ON)
message(STATUS "ENABLE_VERBOSE_LOG = ${ENABLE_VERBOSE_LOG}")
```

`option` 的本质是一个缓存变量（Cache Variable），可通过命令行覆盖：

```bash
cmake -S . -B build -DENABLE_VERBOSE_LOG=OFF
```

典型用法：结合预处理宏

```cmake
if(ENABLE_VERBOSE_LOG)
    target_compile_definitions(app PRIVATE ENABLE_VERBOSE_LOG=1)
endif()
```

---

## 7) 单配置 vs 多配置（你在 Windows 最容易踩坑）

### 单配置生成器（Ninja / Unix Makefiles）

构建类型在 configure 阶段确定：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### 多配置生成器（Visual Studio）

构建类型在 build 阶段选择：

```bash
cmake -S . -B build
cmake --build build --config Release
```

Windows 下如果你用 VS 生成器，运行文件通常在：

- `build/Debug/xxx.exe`
- `build/Release/xxx.exe`

---

## 8) 多目录工程写法（推荐）

目录结构：

```text
project/
  CMakeLists.txt
  app/
    CMakeLists.txt
    main.cpp
  lib/
    CMakeLists.txt
    math_utils.cpp
    math_utils.h
```

根目录 `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.16)
project(sample LANGUAGES CXX)

add_subdirectory(lib)
add_subdirectory(app)
```

`lib/CMakeLists.txt`：

```cmake
add_library(math_utils math_utils.cpp)
target_include_directories(math_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

`app/CMakeLists.txt`：

```cmake
add_executable(app main.cpp)
target_link_libraries(app PRIVATE math_utils)
```

原理：

- `add_subdirectory` 会递归进入子目录执行子 CMakeLists
- 子目录定义的 target（如 `math_utils`）可被上层/同层引用

---

## 9) 三类库：STATIC / SHARED / INTERFACE

```cmake
add_library(a_static STATIC a.cpp)     # 静态库
add_library(a_shared SHARED b.cpp)     # 动态库
add_library(a_header_only INTERFACE)   # 仅头文件库

target_include_directories(a_header_only INTERFACE include)
```

使用场景：

- `STATIC`：部署简单，单文件可执行常见
- `SHARED`：减小主程序体积，方便动态替换
- `INTERFACE`：头文件库（模板库）常用

---

## 10) 安装与发布（基本模板）

```cmake
install(TARGETS app
    RUNTIME DESTINATION bin
)

install(TARGETS math_utils
    ARCHIVE DESTINATION lib
)

install(FILES src/math_utils.h DESTINATION include)
```

执行：

```bash
cmake --install build --prefix ./install
```

---

## 11) 常见错误与定位方法

### 1. `fatal error: xxx.h: No such file or directory`

原因：include 路径没配对。  
排查：检查 `target_include_directories` 是否挂在正确 target，`PUBLIC/PRIVATE` 是否正确。

### 2. `undefined reference` / `LNK2019`

原因：声明有了，定义没链接进来。  
排查：检查 `target_link_libraries` 是否漏写、源文件是否加进 `add_library/add_executable`。

### 3. 改了 CMakeLists 但行为没变化

原因：缓存残留。  
排查：删除 `build` 目录重新 configure。

---

## 12) 对照你当前的 lab1 看代码

你的 `lab1` 已经覆盖了这些知识点：

- `add_library` + `add_executable`
- `target_include_directories(... PUBLIC ...)`
- `target_link_libraries(... PRIVATE ...)`
- `option(...)` + `target_compile_definitions(...)`

建议你立刻做这三个练习来巩固“原理 -> 实践”：

1. 把 `math_utils` 移到 `lib/` 并改成 `add_subdirectory(lib)` 结构
2. 增加一个 `INTERFACE` 库（例如只提供 `config.h`）
3. 增加 install 规则并安装到 `install/`

---

## 13) 速查模板（平时直接复制）

```cmake
cmake_minimum_required(VERSION 3.16)
project(my_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_LOG "Enable logs" ON)

add_library(my_lib src/my_lib.cpp)
target_include_directories(my_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE my_lib)

if(ENABLE_LOG)
    target_compile_definitions(my_app PRIVATE ENABLE_LOG=1)
endif()
```

---

如果你想，我可以下一步直接给你再生成一份 `lab2`：  
“多目录工程 + `add_subdirectory` + install”，并配一套逐步任务清单。

---

## 14) 常用语句速查（含用法）

下面是最常用、最值得优先掌握的一组 CMake 语句。

### `cmake_minimum_required`

作用：指定最低 CMake 版本，避免旧版本行为不一致。

```cmake
cmake_minimum_required(VERSION 3.16)
```

常见场景：每个项目根 `CMakeLists.txt` 第一行附近几乎都要写。

### `project`

作用：定义项目名、版本、语言。

```cmake
project(my_project VERSION 1.0.0 LANGUAGES CXX)
```

常见场景：初始化工程元信息；后续可用 `PROJECT_NAME`、`PROJECT_VERSION`。

### `set`

作用：设置变量（普通变量或缓存变量）。

```cmake
set(MY_VAR "hello")
set(CMAKE_CXX_STANDARD 17)
```

常见场景：设置编译标准、路径、开关默认值等。

### `option`

作用：定义布尔开关，通常给用户通过 `-D` 覆盖。

```cmake
option(ENABLE_LOG "Enable log output" ON)
```

命令行覆盖：

```bash
cmake -S . -B build -DENABLE_LOG=OFF
```

常见场景：控制日志、测试、额外功能开关。

### `message`

作用：打印调试信息或状态信息。

```cmake
message(STATUS "C++ standard = ${CMAKE_CXX_STANDARD}")
message(WARNING "This is a warning")
message(FATAL_ERROR "Compiler not supported")
```

常见场景：调试变量值、做配置阶段的提示和错误中止。

### `add_executable`

作用：定义可执行 target。

```cmake
add_executable(app src/main.cpp src/app.cpp)
```

常见场景：生成命令行工具、服务程序、测试程序。

### `add_library`

作用：定义库 target（静态 / 动态 / 接口）。

```cmake
add_library(math_static STATIC src/math.cpp)
add_library(math_shared SHARED src/math.cpp)
add_library(config_header_only INTERFACE)
```

常见场景：拆分公共模块，给多个可执行程序复用。

### `target_sources`

作用：给已存在的 target 增加源文件（比把所有文件塞进 `add_executable` 更易维护）。

```cmake
add_executable(app)
target_sources(app PRIVATE src/main.cpp src/app.cpp)
```

常见场景：分阶段组织文件，按平台添加不同源码。

### `target_include_directories`

作用：为 target 配置头文件搜索路径。

```cmake
target_include_directories(math_utils
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
```

常见场景：

- `PUBLIC include`：下游也要用该头文件
- `PRIVATE src`：仅库内部实现用

### `target_link_libraries`

作用：链接依赖库，并传播依赖属性。

```cmake
target_link_libraries(app PRIVATE math_utils)
target_link_libraries(service PUBLIC core_lib)
```

常见场景：可执行程序链接业务库；库之间建立依赖链。

### `target_compile_definitions`

作用：给 target 添加预处理宏（`-DXXX`）。

```cmake
target_compile_definitions(app PRIVATE ENABLE_LOG=1)
```

代码中使用：

```cpp
#ifdef ENABLE_LOG
// log code
#endif
```

常见场景：功能开关、平台差异宏。

### `target_compile_options`

作用：给 target 添加编译选项。

```cmake
target_compile_options(app PRIVATE /W4)
```

跨平台常见写法：

```cmake
if(MSVC)
    target_compile_options(app PRIVATE /W4)
else()
    target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)
endif()
```

常见场景：开启警告等级、严格编译策略。

### `target_link_options`

作用：给 target 添加链接器选项。

```cmake
target_link_options(app PRIVATE /DEBUG)
```

常见场景：调试符号、链接器特性开关。

### `add_subdirectory`

作用：包含子目录工程并执行其 `CMakeLists.txt`。

```cmake
add_subdirectory(lib)
add_subdirectory(app)
```

常见场景：多模块项目分层管理。

### `find_package`

作用：查找外部依赖包并导入其 target（推荐）。

```cmake
find_package(fmt REQUIRED)
target_link_libraries(app PRIVATE fmt::fmt)
```

常见场景：使用第三方库（如 `fmt`、`OpenSSL`、`Boost`）。

### `include`

作用：包含额外的 CMake 脚本文件。

```cmake
include(cmake/Warnings.cmake)
```

常见场景：把通用逻辑拆到独立 `.cmake` 文件复用。

### `if / elseif / else / endif`

作用：条件判断。

```cmake
if(WIN32)
    message(STATUS "Build on Windows")
elseif(UNIX)
    message(STATUS "Build on Unix-like")
else()
    message(STATUS "Other platform")
endif()
```

常见场景：平台分支、功能开关分支。

### `foreach / endforeach`

作用：循环处理列表。

```cmake
set(MODULES core net ui)
foreach(m IN LISTS MODULES)
    message(STATUS "module = ${m}")
endforeach()
```

常见场景：批量处理模块、批量打印配置。

### `file`

作用：文件系统相关操作（读取、写入、遍历等）。

```cmake
file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
message(STATUS "sources = ${SRC_FILES}")
```

注意：`GLOB` 方便但在大型项目中可能不如手动列文件稳定可控。

### `install`

作用：定义安装规则。

```cmake
install(TARGETS app RUNTIME DESTINATION bin)
install(TARGETS math_utils ARCHIVE DESTINATION lib)
install(FILES include/math_utils.h DESTINATION include)
```

常见场景：生成可分发目录结构（`bin/lib/include`）。

### `enable_testing` 与 `add_test`

作用：启用并注册测试（CTest）。

```cmake
enable_testing()
add_executable(test_math tests/test_math.cpp)
add_test(NAME math_test COMMAND test_math)
```

常见场景：CI 自动化测试。

---

## 15) 一段“常用语句组合模板”

```cmake
cmake_minimum_required(VERSION 3.16)
project(template_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_LOG "Enable logs" ON)

add_library(core STATIC src/core.cpp)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE core)

if(ENABLE_LOG)
    target_compile_definitions(app PRIVATE ENABLE_LOG=1)
endif()

if(MSVC)
    target_compile_options(app PRIVATE /W4)
else()
    target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS app RUNTIME DESTINATION bin)
```

你后续写项目时，直接从这段模板改就可以。
