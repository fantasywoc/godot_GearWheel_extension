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
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tooth_width_angle", PROPERTY_HINT_RANGE, "0.1,10.0,0.1"), 
        "set_tooth_width_angle", "get_tooth_width_angle");

    ClassDB::bind_method(D_METHOD("set_is_driving", "driving"), &GearCollisionPolygon::set_is_driving);
    ClassDB::bind_method(D_METHOD("get_is_driving"), &GearCollisionPolygon::get_is_driving);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_driving"), "set_is_driving", "get_is_driving");

    ClassDB::bind_method(D_METHOD("set_up_tooth_width", "width"), &GearCollisionPolygon::set_up_tooth_width);
    ClassDB::bind_method(D_METHOD("get_up_tooth_width"), &GearCollisionPolygon::get_up_tooth_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "up_tooth_width", PROPERTY_HINT_RANGE, "0.1,10.0,0.1"), 
        "set_up_tooth_width", "get_up_tooth_width");

    ClassDB::bind_method(D_METHOD("set_down_tooth_width", "width"), &GearCollisionPolygon::set_down_tooth_width);
    ClassDB::bind_method(D_METHOD("get_down_tooth_width"), &GearCollisionPolygon::get_down_tooth_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "down_tooth_width", PROPERTY_HINT_RANGE, "0.1,10.0,0.1"), 
        "set_down_tooth_width", "get_down_tooth_width");

    ClassDB::bind_method(D_METHOD("set_tooth_height", "height"), &GearCollisionPolygon::set_tooth_height);
    ClassDB::bind_method(D_METHOD("get_tooth_height"), &GearCollisionPolygon::get_tooth_height);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "tooth_height", PROPERTY_HINT_RANGE, "0.1,10.0,0.1"), 
        "set_tooth_height", "get_tooth_height");


    ClassDB::bind_method(D_METHOD("set_radius", "radius"), &GearCollisionPolygon::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &GearCollisionPolygon::get_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "0.1,100.0,0.1"), 
        "set_radius", "get_radius");

}


// void GearCollisionPolygon::set_teeth_count(int count) { teeth_count = count; }
// int GearCollisionPolygon::get_teeth_count() const { return teeth_count; }
