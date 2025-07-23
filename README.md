# godot-cpp template
This repository serves as a quickstart template for GDExtension development with Godot 4.0+.

## Contents
* An empty Godot project (`demo/`)
* godot-cpp as a submodule (`godot-cpp/`)
* GitHub Issues template (`.github/ISSUE_TEMPLATE.yml`)
* GitHub CI/CD workflows to publish your library packages when creating a release (`.github/workflows/builds.yml`)
* preconfigured source files for C++ development of the GDExtension (`src/`)
* setup to automatically generate `.xml` files in a `doc_classes/` directory to be parsed by Godot as [GDExtension built-in documentation](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_docs_system.html)

## Usage - Template

To use this template, log in to GitHub and click the green "Use this template" button at the top of the repository page.
This will let you create a copy of this repository with a clean git history. Make sure you clone the correct branch as these are configured for development of their respective Godot development branches and differ from each other. Refer to the docs to see what changed between the versions.

For getting started after cloning your own copy to your local machine, you should: 
* initialize the godot-cpp git submodule via `git submodule update --init`
* change the name of your library
  * change the name of the compiled library file inside the `SConstruct` file by modifying the `libname` string.
  * change the pathnames of the to be loaded library name inside the `demo/bin/example.gdextension` file. By replacing `libgdexample` to the name specified in your `SConstruct` file.
  * change the name of the `demo/bin/example.gdextension` file
* change the `entry_symbol` string inside your `demo/bin/your-extension.gdextension` file to be configured for your GDExtension name. This should be the same as the `GDExtensionBool GDE_EXPORT` external C function. As the name suggests, this sets the entry function for your GDExtension to be loaded by the Godot editors C API.
* register the classes you want Godot to interact with inside the `register_types.cpp` file in the initialization method (here `initialize_gdextension_types`) in the syntax `GDREGISTER_CLASS(CLASS-NAME);`.

### Configuring an IDE 
You can develop your own extension with any text editor and by invoking scons on the command line, but if you want to work with an IDE (Integrated Development Environment), you can use a compilation database file called `compile_commands.json`. Most IDEs should automatically identify this file, and self-configure appropriately.
To generate the database file, you can run one of the following commands in the project root directory:
```shell
# Generate compile_commands.json while compiling
scons compiledb=yes

# Generate compile_commands.json without compiling
scons compiledb=yes compile_commands.json
```

## Usage - Actions

This repository comes with a GitHub action that builds the GDExtension for cross-platform use. It triggers automatically for each pushed change. You can find and edit it in [builds.yml](.github/workflows/builds.yml).
After a workflow run is complete, you can find the file `godot-cpp-template.zip` on the `Actions` tab on GitHub.




# `.gdextension` 文件的生成与作用

`.gdextension` 文件是 Godot 4 引入的**手动创建的配置文件**，用于替代 Godot 3 的 `.gdnlib` 文件。

## 文件创建方式

### 手动创建步骤：
1. 在文本编辑器中创建新文件
2. 保存为 `your_extension.gdextension`（名称与你的扩展相关）
3. 使用以下基本结构填充内容：

```ini
[configuration]
entry_symbol = "gdextension_library_init"
compatibility_minimum = "4.1"

[libraries]
windows.x86_64 = "res://bin/libgdexample.dll"
linux.x86_64 = "res://bin/libgdexample.so"
macos = "res://bin/libgdexample.dylib"
```

### 关键配置项说明：

| 节           | 键                  | 描述                                                                 |
|--------------|---------------------|----------------------------------------------------------------------|
| `[configuration]` | `entry_symbol`        | **必须与 C++ 代码中的函数名匹配**，通常是 `gdextension_library_init` |
|              | `compatibility_minimum` | 最低支持的 Godot 版本 (如 "4.0", "4.1")                             |
| `[libraries]`    | `windows.x86_64`       | Windows 平台库文件路径                                                |
|              | `linux.x86_64`         | Linux 平台库文件路径                                                  |
|              | `macos`                | macOS 平台库文件路径                                                  |
| `[dependencies]` | 平台标识              | 依赖的附加库 (可选)                                                  |

## 与代码的关联

### C++ 入口点示例
`.gdextension` 文件中的 `entry_symbol` 必须与 C++ 代码中的初始化函数匹配：

```cpp
// 必须与 .gdextension 中的 entry_symbol 完全一致
extern "C" {
GDE_EXPORT GDExtensionBool GDE_EXPORT gdextension_library_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization
) {
    // 初始化代码
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
    init_obj.register_initializer(initialize_module);
    init_obj.register_terminator(uninitialize_module);
    return init_obj.init();
}
}
```

## 配置示例

1. **文件位置**：
   - 通常放在项目根目录的 `bin/` 或 `addons/your_extension/` 目录
   - 确保路径与库文件实际位置匹配

2. **多平台支持**：
   ```ini
   [libraries]
   # Windows
   windows.x86_64 = "res://bin/windows/libgdexample.dll"
   
   # Linux
   linux.x86_64 = "res://bin/linux/libgdexample.so"
   
   # macOS (通用二进制)
   macos = "res://bin/macos/libgdexample.dylib"
   ```

3. **版本控制**：
   ```ini
   [configuration]
   compatibility_minimum = "4.1"
   reloadable = true
   ```

4. **依赖管理** (如果需要)：
   ```ini
   [dependencies]
   windows.x86_64 = [ "res://bin/windows/dependency.dll" ]
   linux.x86_64 = [ "res://bin/linux/libdependency.so" ]
   ```

## 工作原理

当 Godot 启动时：
1. 扫描项目目录查找 `.gdextension` 文件
2. 根据当前运行平台加载对应的库文件
3. 通过 `entry_symbol` 查找并调用初始化函数
4. 注册扩展中定义的类和方法

> **重要提示**：`.gdextension` 文件是纯文本配置文件，不需要特殊工具生成，但必须确保其内容与你的代码和编译输出精确匹配。



# Godot Extension 编译

## 编译步骤

scons compiledb=yes # 生成编译数据库文件  

scons # 编译
scons -c # 清理

# 单精度调试版
scons target=template_debug float_precision=single

# 双精度发布版
scons target=template_release float_precision=double