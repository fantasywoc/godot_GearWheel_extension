
# godot-cpp-extension
godot C++ 扩展例子
# 编译

```bash
#清理缓存
scons -c
#编译（默认编译debug single）
scons
```
### release版本
```bash
scons target=template_release precision=single
scons target=template_release precision=double

```

### debug版本
```bash
scons target=template_debug precision=single
scons target=template_debug precision=double
```



C++ 编写的 RotatableEditorPlugin（继承 EditorPlugin）和 GDScript 编写的 plugin.gd（同样继承 EditorPlugin）是两个独立的插件入口，但 Godot 会将它们合并为同一个插件的一部分。
具体来说：
plugin.cfg 是插件的核心配置文件，指定了插件的基本信息（名称、描述等）。
C++ 插件通过 EditorPlugin 注册底层功能（如自定义 Inspector、节点类型）。
GDScript 的 plugin.gd 会被 Godot 识别为插件的脚本入口，用于补充编辑器逻辑（如打印日志、添加菜单等）。
两者会在插件启用时同时生效，C++ 部分负责高性能的底层扩展，GDScript 部分负责灵活的上层编辑器逻辑，形成互补。