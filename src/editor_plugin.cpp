#include "editor_plugin.h"
#include "rotatable_rigid_body.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_interface.hpp>

using namespace godot;

// RotatableInspectorPlugin 实现


bool RotatableInspectorPlugin::_can_handle(Object *p_object) const {
    return Object::cast_to<RotatableRigidBody>(p_object) != nullptr;
}

void RotatableInspectorPlugin::_parse_category(Object *p_object, const String &p_category) {
    // 可以在这里添加自定义检查器逻辑
}



RotatableEditorPlugin::RotatableEditorPlugin() {
    inspector_plugin.instantiate();
}

RotatableEditorPlugin::~RotatableEditorPlugin() {
}

void RotatableEditorPlugin::_enter_tree() {
    add_inspector_plugin(inspector_plugin);
}

void RotatableEditorPlugin::_exit_tree() {
    remove_inspector_plugin(inspector_plugin);
}