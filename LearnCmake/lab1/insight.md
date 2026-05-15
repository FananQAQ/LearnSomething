# Lab1 学习笔记（Insight）

> 记录 CMake 入门实战中的概念、命令与个人踩坑。  
> 工程：`lab1_cmake` — 可执行程序 `lab1_app` + 静态库 `math_utils` + GoogleTest。

---

## 1. CMake 在干什么

CMake **不是编译器**，而是：

1. **Configure（配置）**：读 `CMakeLists.txt`，检查编译器、解析选项  
2. **Generate（生成）**：产出 VS 工程 / Ninja / Makefile  
3. **Build（构建）**：调用底层工具真正编译链接  

常用三条命令：

```powershell
cmake -S . -B build                          # 配置
cmake --build build --config Debug           # 构建
cmake --install build --config Debug --prefix ./install   # 安装（可选）
```

- `-S .`：源码目录（含根 `CMakeLists.txt`）  
- `-B build`：构建目录（产物、缓存，一般不提交 Git）

---

## 2. 核心思想：一切皆 target

现代 CMake 围绕 **target** 组织，而不是全局乱设变量：

| 语句 | 作用 |
|------|------|
| `add_library(math_utils ...)` | 定义库 target |
| `add_executable(lab1_app ...)` | 定义可执行 target |
| `target_link_libraries(lab1_app PRIVATE math_utils)` | 声明依赖 |
| `target_include_directories(... PUBLIC ...)` | 头文件路径 |
| `target_compile_definitions(... PRIVATE ...)` | 编译宏 `-DXXX` |

配置尽量挂在 target 上，依赖清晰、不污染全局。

---

## 3. 我的工程结构

```text
lab1/
  CMakeLists.txt       # 根：标准、option、CTest、add_subdirectory
  lib/                 # 静态库 math_utils
  src/                 # lab1_app + main.cpp
  tests/               # GoogleTest
  build/               # 构建输出（本地）
  install/             # 安装输出（cmake --install 后）
```

根目录通过 `add_subdirectory(lib/src/tests)` 串联子工程。

---

## 4. 链接与头文件：PUBLIC / PRIVATE

- `target_link_libraries(lab1_app PRIVATE math_utils)`  
  - `app` 用 `math_utils`，但**不**把依赖传给更上层  
- `target_include_directories(math_utils PUBLIC ...)`  
  - 库自己要用，**且**链接它的 `lab1_app` 也要能找到 `math_utils.h`  

记法：**谁需要头文件，谁就要能通过 PUBLIC/INTERFACE 传路径。**

---

## 5. 编译开关：option + 宏

### 5.1 定义开关（根 CMakeLists.txt）

```cmake
option(ENABLE_VERBOSE_LOG "Enable verbose output in app" OFF)
option(USE_DOUBLE_VALUE "Use double value" OFF)
```

### 5.2 把开关变成编译宏（src/CMakeLists.txt）

```cmake
if(ENABLE_VERBOSE_LOG)
    target_compile_definitions(lab1_app PRIVATE ENABLE_VERBOSE_LOG=1)
endif()

if(USE_DOUBLE_VALUE)
    target_compile_definitions(lab1_app PRIVATE USE_DOUBLE_VALUE=1)
endif()
```

### 5.3 在 C++ 里使用（main.cpp）

```cpp
#ifdef USE_DOUBLE_VALUE
    x *= 2;
    y *= 2;
#endif

#ifdef ENABLE_VERBOSE_LOG
    std::cout << "[VERBOSE] ...\n";
#endif
```

**要点：** `option` 只存在于 CMake 配置阶段；C++ 里要用 `#ifdef`，中间必须靠 `target_compile_definitions` 桥接。

---

## 6. 缓存：为什么改了默认值还不生效

`option()` 会写入 `build/CMakeCache.txt`。

| 操作 | 结果 |
|------|------|
| 第一次 `-DUSE_DOUBLE_VALUE=ON` | 缓存为 ON |
| 再次 `cmake -S . -B build`（不带 -D） | **仍读缓存 ON**，不会恢复 CMakeLists 里的默认 OFF |
| 想改回 OFF | `cmake -S . -B build -DUSE_DOUBLE_VALUE=OFF` 或删除 `build/` |

这是实践中很容易踩的坑：**不带 -D 的重新配置 ≠ 恢复默认值。**

---

## 7. 多目录：add_subdirectory

```cmake
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
```

子目录里的 `CMakeLists.txt` 定义的 target（如 `math_utils`）可在其他子目录里通过 `target_link_libraries` 引用。

---

## 8. 测试：CTest + GoogleTest

根目录：

```cmake
include(CTest)
enable_testing()
```

`tests/CMakeLists.txt` 用 `FetchContent` 拉取 googletest，`gtest_discover_tests` 注册测试。

运行：

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

---

## 9. 安装：install 的意义

在 `src/CMakeLists.txt`：

```cmake
install(TARGETS lab1_app RUNTIME DESTINATION bin)
```

执行：

```powershell
cmake --install build --config Debug --prefix ./install
```

得到规整目录：`install/bin/lab1_app.exe`。

**理解：**

- `build/`：编译产物，路径深、和生成器/配置相关  
- `install/`：按规则**拷贝/部署**到固定结构（`bin`、`lib`、`include`），便于分发  

| 参数 | 含义 |
|------|------|
| `--prefix ./install` | 安装根目录；不写则可能装到 `Program Files` |
| `--config Debug` | VS 多配置生成器需指定 Debug/Release |

---

## 10. Windows 上 Debug / Release

Visual Studio 生成器：**配置阶段不固定** Debug/Release，**构建/安装时**用 `--config` 选择。

```powershell
cmake --build build --config Debug
cmake --build build --config Release
```

exe 常见路径：

- `build\src\Debug\lab1_app.exe`  
- `build\src\Release\lab1_app.exe`  

Release 通常比 Debug 更小（Debug 含调试信息、优化少）。

---

## 11. 踩坑记录

| 问题 | 原因 | 处理 |
|------|------|------|
| `Flow control statements are not properly nested` | `if` 写了 `en` / 缺少 `endif()` | 每个 `if` 配对 `endif()` |
| 关掉 `-DUSE_DOUBLE_VALUE` 仍双倍 | CMake 缓存仍是 ON | `-D...=OFF` 或删 `build` |
| 有 VERBOSE 但 CMakeLists 默认 OFF | `ENABLE_VERBOSE_LOG` 缓存为 ON | 同上 |
| 找不到头文件 | `target_include_directories` 未 PUBLIC | 库对头文件路径用 PUBLIC |

---

## 12. 命令速查

```powershell
# 完整流程
cd lab1
cmake -S . -B build
cmake --build build --config Debug
.\build\src\Debug\lab1_app.exe

# 打开某个 option
cmake -S . -B build -DUSE_DOUBLE_VALUE=ON
cmake --build build --config Debug

# 测试
ctest --test-dir build -C Debug --output-on-failure

# 安装到项目内 install/
cmake --install build --config Debug --prefix ./install
.\install\bin\lab1_app.exe
```

---

## 13. 一句话总结

Lab1 让我建立起这条链路：**CMakeLists 描述 target → configure 生成工程 → build 出 exe → option/宏 控制编译行为 → install 规整部署 → CTest 自动测**。  
下一步（Lab2）可以继续学：INTERFACE 库、SHARED 库、`configure_file`、更完整的 `install(EXPORT)` 等。
