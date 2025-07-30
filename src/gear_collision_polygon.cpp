#include "gear_collision_polygon.h"
#include <godot_cpp/core/class_db.hpp>

// using namespace godot;

GearCollisionPolygon::GearCollisionPolygon() {
    // 构造函数

}

void GearCollisionPolygon::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_teeth_count", "count"), &GearCollisionPolygon::set_teeth_count);
    ClassDB::bind_method(D_METHOD("get_teeth_count"), &GearCollisionPolygon::get_teeth_count);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "teeth_count", PROPERTY_HINT_RANGE, "8,100,1"), 
        "set_teeth_count", "get_teeth_count");

    ClassDB::bind_method(D_METHOD("set_tooth_width_angle", "angle"), &GearCollisionPolygon::set_tooth_width_angle);
    ClassDB::bind_method(D_METHOD("get_tooth_width_angle"), &GearCollisionPolygon::get_tooth_width_angle);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tooth_width_angle", PROPERTY_HINT_RANGE, "0.1,360.0,0.001"), 
        "set_tooth_width_angle", "get_tooth_width_angle");

    ClassDB::bind_method(D_METHOD("set_is_driving", "driving"), &GearCollisionPolygon::set_is_driving);
    ClassDB::bind_method(D_METHOD("get_is_driving"), &GearCollisionPolygon::get_is_driving);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_driving"), "set_is_driving", "get_is_driving");

    ClassDB::bind_method(D_METHOD("set_up_tooth_width", "width"), &GearCollisionPolygon::set_up_tooth_width);
    ClassDB::bind_method(D_METHOD("get_up_tooth_width"), &GearCollisionPolygon::get_up_tooth_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "up_tooth_width", PROPERTY_HINT_RANGE, "0.1,50.0,0.001"), 
        "set_up_tooth_width", "get_up_tooth_width");

    ClassDB::bind_method(D_METHOD("set_down_tooth_width", "width"), &GearCollisionPolygon::set_down_tooth_width);
    ClassDB::bind_method(D_METHOD("get_down_tooth_width"), &GearCollisionPolygon::get_down_tooth_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "down_tooth_width", PROPERTY_HINT_RANGE, "0.1,100.0,0.001"), 
        "set_down_tooth_width", "get_down_tooth_width");

    ClassDB::bind_method(D_METHOD("set_tooth_height", "height"), &GearCollisionPolygon::set_tooth_height);
    ClassDB::bind_method(D_METHOD("get_tooth_height"), &GearCollisionPolygon::get_tooth_height);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tooth_height", PROPERTY_HINT_RANGE, "0.1,50.0,0.001"), 
        "set_tooth_height", "get_tooth_height");


    ClassDB::bind_method(D_METHOD("set_radius", "radius"), &GearCollisionPolygon::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &GearCollisionPolygon::get_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "0.1,100.0,0.001"), 
        "set_radius", "get_radius");

}


PackedVector2Array GearCollisionPolygon::generate_gear_vertices() {
    // 检查输入有效性
    if (radius <= 0.01f || down_tooth_width <= 0.01f || up_tooth_width <= 0.01f ||
        teeth_count < 3 || tooth_height <= 0.01f) {
        UtilityFunctions::printerr("Invalid gear parameters");
        return PackedVector2Array();
    }

    PackedVector2Array vertices;

    // 使用标准 C++ PI 和数学函数代替 Math::TAU
    const float PI = 3.14;
    const float TAU = 2.0f * PI;
    const float re = TAU / static_cast<float>(teeth_count); // 每个齿的弧度
    const float half_re = re / 2.0f;

    // 计算齿底Y坐标偏移
    const float base_offset = radius * std::abs(std::cos(half_re));

    // 第一个齿的基础顶点
    Vector2 base_points[4] = {            //godot x 轴 向右为正,Y轴向下为正
        Vector2(down_tooth_width / 2.0f, base_offset),         // 右翅根（
        Vector2(up_tooth_width / 2.0f, base_offset + tooth_height),   // 右齿顶
        Vector2(-up_tooth_width / 2.0f, base_offset + tooth_height),   // 左齿顶
        Vector2(-down_tooth_width / 2.0f, base_offset)          // 左翅根
        
        
    };

    // 预分配内存提高性能
    vertices.resize(teeth_count * 4);

    // 对于每个齿生成顶点
    for (int i = 0; i < teeth_count; i++) {
        // 计算当前齿的旋转角度
        const float rotation_angle = static_cast<float>(i) * re;
        const float cos_theta = std::cos(rotation_angle);
        const float sin_theta = std::sin(rotation_angle);

        // 预计算基础点旋转后的坐标
        for (int j = 0; j < 4; j++) {
            const Vector2& point = base_points[j];
            Vector2 rotated_point;
            
            // 应用旋转矩阵
            rotated_point.x = point.x * cos_theta - point.y * sin_theta;
            rotated_point.y = point.x * sin_theta + point.y * cos_theta;
            
            // 直接赋值给预分配数组
            vertices.set(i * 4 + j, rotated_point);
        }
    }

    return vertices;
}


