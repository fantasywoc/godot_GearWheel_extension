#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

#include "rotatable_rigid_body.h"
#include "gear_collision_polygon.h"
#include "editor_plugin.h"

using namespace godot;

void initialize_rotatable_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
        ClassDB::register_class<RotatableInspectorPlugin>();
        ClassDB::register_class<RotatableEditorPlugin>();
    }
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        ClassDB::register_class<RotatableRigidBody>();
        ClassDB::register_class<GearCollisionPolygon>();  // 注册新类
        // 可以继续添加更多类
    }
}

void uninitialize_rotatable_module(ModuleInitializationLevel p_level) {
    // 无需清理
}

extern "C" {
    GDExtensionBool GDE_EXPORT rotatable_library_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization
    ) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
        
        init_obj.register_initializer(initialize_rotatable_module);
        init_obj.register_terminator(uninitialize_rotatable_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_EDITOR);
        
        return init_obj.init();
    }
}