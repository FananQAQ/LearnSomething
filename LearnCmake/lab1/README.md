# Lab1: CMake 入门实战

这个 lab 的目标：你将亲手完成一个“可执行程序 + 静态库”的 CMake 工程，并学会最常用命令。

## 目录结构

```text
lab1/
  CMakeLists.txt
  src/
    main.cpp
    math_utils.h
    math_utils.cpp
```

## Step 1: 配置与构建

在 `lab1` 目录下执行：

```bash
cmake -S . -B build
cmake --build build
```

## Step 2: 运行程序

### Windows (Visual Studio 生成器常见)

```bash
.\build\Debug\lab1_app.exe
```

如果是 Release：

```bash
.\build\Release\lab1_app.exe
```

### Ninja / Makefile 生成器

```bash
.\build\lab1_app.exe
```

## 预期输出

```text
add(6, 7) = 13
multiply(6, 7) = 42
[VERBOSE] lab1_app finished successfully.
```

## Step 3: 动手任务（建议按顺序）

1. 在 `math_utils` 里新增 `subtract(int a, int b)` 并在 `main.cpp` 调用。
2. 在 `CMakeLists.txt` 中把 `ENABLE_VERBOSE_LOG` 默认改为 `OFF`，重新构建观察输出变化。
3. 新增一个 `option(USE_DOUBLE_VALUE "..." OFF)`，为 `lab1_app` 添加编译宏并在代码中改变输入值。
4. 尝试使用不同构建类型（`Debug/Release`）并比较二进制大小。

## Step 4: 进阶挑战

- 把 `math_utils` 拆到 `lib/` 子目录并用 `add_subdirectory(lib)` 管理。
- 添加安装规则：把可执行文件安装到 `bin`。
- 给项目加一个简单测试（后续可学习 `CTest`）。

## 常见问题

- `cmake` 命令不存在：确认已安装 CMake 并加入 PATH。
- 找不到编译器：Windows 建议安装 Visual Studio C++ 工具链或使用 MinGW。
- 构建目录脏了：删除 `build` 后重新执行配置命令。
