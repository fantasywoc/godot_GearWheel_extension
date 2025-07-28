#include "editor_plugin.h"
#include "example_class.h" // 包含自定义类

ExampleClassEditorPlugin::ExampleClassEditorPlugin() {}
ExampleClassEditorPlugin::~ExampleClassEditorPlugin() {}

void ExampleClassEditorPlugin::_enter_tree() {
// 若 ExampleClass 是节点（需显示在场景中），应继承 Node 或其派生类（如 Node2D），再用 add_custom_type 注册。
// 若 ExampleClass 是数据资源（如配置数据、工具类），继承 RefCounted 即可，注册后可在 Inspector 面板中通过 “新建资源” 选择它。
    // 注册资源类（编辑器会在资源选择器中识别它）
    ClassDB::register_class<ExampleClass>();
    // 可选：添加自定义节点到“创建”菜单的快捷方式
    // 第一个参数：菜单路径（如 "Node2D/GearWheel"）
    // 第二个参数：类名
    // 第三个参数：图标路径
    // add_custom_type(
    //     "ExampleClass",
    //     "RigidBody2D",
    //     &ExampleClass::get_class_static(),
    //     "res://addons/icons/icon.svg"
    // );

     UtilityFunctions::print("ExampleClass Editor Plugin activated");
}

void ExampleClassEditorPlugin::_exit_tree() {
    // 移除自定义类型
    // remove_custom_type("ExampleClass");   // 无需移除资源类注册

        // 清理编辑器插件相关资源
    UtilityFunctions::print("ExampleClass Editor Plugin deactivated");
}