
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













# TIPS

### 节点初始化调用顺序

当Godot加载节点时，会按以下顺序执行：

1. 创建对象 ：调用构造函数 → 第一次执行计算
2. 恢复属性值 ：从场景文件读取保存的属性值，调用setter方法 → 第二次执行计算

```C++
void set_down_tooth_width(float width) {
    if (_is_initializing) {   // 初始化期间只同步数据，避免没读交互面板数据之前计算，导致数据错乱
        down_tooth_width = width;
        return;  
    }
    // 正常的setter逻辑
    if(width >= radius){
        UtilityFunctions::print("[ERROR]---> teeth_width is greater than radius!!!!!!!");
        return;
    }
    down_tooth_width = width;
    GearWheelCalculator gear(radius, down_tooth_width);
    int count = 0;
    if (!gear.isDivisibleBy360(count)) {
        radius = gear.findNearestValidRadius();
        teeth_count = gear.getTeethCount();
        set_tooth_width_angle(radius);
        UtilityFunctions::print("--------------->   teeth_count:", teeth_count);
    }
    set_polygon(generate_gear_vertices());
}

// 添加_ready方法来完成初始化
void _ready() override {
    _is_initializing = false;
    set_polygon(generate_gear_vertices());
}
```
