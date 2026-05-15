# Lab2: CMake 进阶实战

在 Lab1（静态库 + 子目录 + 测试）基础上，本实验覆盖**多类型 target、生成头文件、安装导出、INTERFACE 库、可选动态库、CMake 模块复用**等进阶用法。

## 目录结构

```text
lab2/
  CMakeLists.txt
  cmake/
    CompilerWarnings.cmake
    Lab2Config.cmake.in
  include/lab2/
    version.h.in
  lib/
    core/          # 静态库：字符串工具
    config/        # INTERFACE 库：仅头文件配置
    stats/         # 可选 SHARED / STATIC：统计函数
  apps/cli/        # 命令行演示程序
  tests/           # GoogleTest + CTest
```

## Step 1: 配置与构建

在 `lab2` 目录下：

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

### 常用开关

```powershell
# 关闭详细日志
cmake -S . -B build -DLAB2_ENABLE_VERBOSE=OFF

# 统计库改为静态库（默认 ON = 动态库）
cmake -S . -B build -DLAB2_BUILD_SHARED_STATS=OFF

# 演示模式：输入数据放大 2 倍
cmake -S . -B build -DLAB2_ENABLE_DEMO_SCALE=ON
```

## Step 2: 运行

### Visual Studio 多配置生成器

```powershell
.\build\apps\cli\Debug\lab2_cli.exe
```

### Ninja / 单配置生成器

```powershell
.\build\apps\cli\lab2_cli.exe
```

或使用自定义目标：

```powershell
cmake --build build --config Debug --target run_demo
```

## 预期输出（默认配置）

```text
lab2 version 1.0.0
app: lab2_cli
delimiter: ','
raw text: "  hello,world,cmake  "
trimmed:    "hello,world,cmake"
word count: 3
samples: 2 5 9
stats -> min=2 max=9 avg=5.33333
[VERBOSE] lab2_cli finished.
```

## Step 3: 动手任务

1. 在 `string_utils` 中实现 `to_upper(std::string)`，并在 `main.cpp` 打印大写结果。
2. 修改根 `CMakeLists.txt`，把项目版本改为 `1.1.0`，观察 `configure_file` 生成的 `version.h` 变化。
3. 将 `LAB2_ENABLE_VERBOSE` 默认改为 `OFF`，重新配置构建，确认 `[VERBOSE]` 行消失。
4. 分别用 `LAB2_BUILD_SHARED_STATS=ON/OFF` 构建，用 `dumpbin /dependents`（MSVC）或 `ldd`（Linux）观察 `lab2_cli` 是否依赖 `lab2_stats.dll`。
5. 执行安装并检查目录结构：

   ```powershell
   cmake --install build --config Debug --prefix ./install
   dir .\install
   ```

## Step 4: 进阶挑战

- 阅读 `cmake/CompilerWarnings.cmake`，给 `lab2_stats` 单独加更严格的警告选项。
- 在 `lib/stats/stats.h` 中理解 `LAB2_STATS_API` 导出宏（动态库必备）。
- 尝试用 `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` 生成 `compile_commands.json`（clangd / IDE 友好）。
- 阅读根目录 `install(EXPORT ...)` 与 `Lab2Config.cmake.in`，理解“安装后别的项目如何 `find_package(lab2)`”。
- 新增 `benchmarks/` 子目录，用 `add_executable` + `add_custom_target` 注册性能小测试（无需 Google Benchmark）。

## 与 Lab1 的知识对照

| 知识点 | Lab1 | Lab2 |
|--------|------|------|
| `add_subdirectory` | ✅ | ✅ 更深目录 |
| `option` + 宏 | ✅ | ✅ 多个开关 |
| `INTERFACE` 库 | ❌ | ✅ `lab2_config` |
| `SHARED` 库 | ❌ | ✅ 可选 `lab2_stats` |
| `configure_file` | ❌ | ✅ 版本头文件 |
| `install` | 部分 | ✅ 完整 bin/lib/include/cmake |
| `install(EXPORT)` | ❌ | ✅ |
| CMake 模块 `include()` | ❌ | ✅ `CompilerWarnings.cmake` |
| 生成器表达式 | ❌ | ✅ `$<BUILD_INTERFACE:...>` |
| `add_custom_target` | ❌ | ✅ `run_demo` |

## 常见问题

- **找不到 `lab2/version.h`**：该文件在构建目录生成，不要手动复制到源码树；重新 `cmake -S . -B build`。
- **动态库加载失败**：Windows 需保证 `lab2_stats.dll` 与 `lab2_cli.exe` 同目录，或把 DLL 目录加入 `PATH`；安装后一般在 `install/bin`。
- **测试失败**：先 `cmake --build build --config Debug`，再 `ctest --test-dir build -C Debug --output-on-failure`。
