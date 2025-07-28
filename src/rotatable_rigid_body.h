#ifndef ROTATABLE_RIGID_BODY_H
#define ROTATABLE_RIGID_BODY_H

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class RotatableRigidBody : public RigidBody2D {
    GDCLASS(RotatableRigidBody, RigidBody2D);

private:
    float rotation_speed = 1.0f;
    bool clockwise = false;
    bool auto_rotate = true;

protected:
    static void _bind_methods();

public:
    RotatableRigidBody();

    // 属性设置/获取
    void set_rotation_speed(float p_speed);
    float get_rotation_speed() const;

    void set_clockwise(bool p_clockwise);
    bool get_clockwise() const;

    void set_auto_rotate(bool p_auto);
    bool get_auto_rotate() const;

    // 旋转控制函数
    void rotate_body(double delta);

    // 重写物理更新（修正函数签名为double）
    void _physics_process(double delta) override;
};

#endif // ROTATABLE_RIGID_BODY_H