#include "rotatable_rigid_body.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

RotatableRigidBody::RotatableRigidBody() {
    // 简化构造函数，移除有问题的物理材质设置
    // 可以在Godot编辑器中手动设置物理属性
}

void RotatableRigidBody::_bind_methods() {
    // 绑定属性
    ClassDB::bind_method(D_METHOD("set_rotation_speed", "speed"), &RotatableRigidBody::set_rotation_speed);
    ClassDB::bind_method(D_METHOD("get_rotation_speed"), &RotatableRigidBody::get_rotation_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_speed", PROPERTY_HINT_RANGE, "0,10,0.1"), 
        "set_rotation_speed", "get_rotation_speed");

    ClassDB::bind_method(D_METHOD("set_clockwise", "clockwise"), &RotatableRigidBody::set_clockwise);
    ClassDB::bind_method(D_METHOD("get_clockwise"), &RotatableRigidBody::get_clockwise);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "clockwise"), "set_clockwise", "get_clockwise");

    ClassDB::bind_method(D_METHOD("set_auto_rotate", "auto"), &RotatableRigidBody::set_auto_rotate);
    ClassDB::bind_method(D_METHOD("get_auto_rotate"), &RotatableRigidBody::get_auto_rotate);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_rotate"), "set_auto_rotate", "get_auto_rotate");

    // 绑定旋转方法
    ClassDB::bind_method(D_METHOD("rotate_body", "delta"), &RotatableRigidBody::rotate_body);
}

// ... existing code ...
void RotatableRigidBody::set_rotation_speed(float p_speed) {
    rotation_speed = p_speed;
}

float RotatableRigidBody::get_rotation_speed() const {
    return rotation_speed;
}

void RotatableRigidBody::set_clockwise(bool p_clockwise) {
    clockwise = p_clockwise;
}

bool RotatableRigidBody::get_clockwise() const {
    return clockwise;
}

void RotatableRigidBody::set_auto_rotate(bool p_auto) {
    auto_rotate = p_auto;
}

bool RotatableRigidBody::get_auto_rotate() const {
    return auto_rotate;
}

// 旋转控制实现
void RotatableRigidBody::rotate_body(double delta) {
    double rotation_amount = rotation_speed * delta * (clockwise ? -1 : 1);
    set_rotation(get_rotation() + rotation_amount);
}

// 物理更新（修正：使用double参数）
void RotatableRigidBody::_physics_process(double delta) {
    if (auto_rotate) {
        rotate_body(delta);
    }
    // 调用父类的物理更新
    RigidBody2D::_physics_process(delta);
}