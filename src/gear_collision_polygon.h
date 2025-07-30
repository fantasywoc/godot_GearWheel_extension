#ifndef GEAR_COLLISION_POLYGON_H
#define GEAR_COLLISION_POLYGON_H

#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/classes/collision_polygon2d.hpp>
#include <GearWheelCalculator.h>

using namespace godot;

class GearCollisionPolygon : public CollisionPolygon2D {
    GDCLASS(GearCollisionPolygon, CollisionPolygon2D);

private:
    int teeth_count = 20;
    float tooth_width_angle = 1.0f;
    bool is_driving = false;
    float up_tooth_width = 10;
    float down_tooth_width = 15;
    float tooth_height = 18;
    float radius = 50;
    PackedVector2Array polygon;
protected:
    static void _bind_methods();

public:
    GearCollisionPolygon();

    PackedVector2Array generate_gear_vertices();
    
    void set_teeth_count(int count){teeth_count = count;};
    int get_teeth_count() const{return teeth_count;};
    
    void set_tooth_width_angle(float angle){ tooth_width_angle = angle;};
    float get_tooth_width_angle() const{return tooth_width_angle;};
    
    void set_is_driving(bool driving){ is_driving = driving;};
    bool get_is_driving() const{return is_driving;};

    void set_up_tooth_width(float width){ up_tooth_width = width;};
    float get_up_tooth_width() const{return up_tooth_width;};

    void set_down_tooth_width(float width){ 
        
        down_tooth_width = width;
        GearWheelCalculator gear(radius,down_tooth_width);
        int count=0;
        if (!gear.isDivisibleBy360(count)) {
            radius = gear.findNearestValidRadius();
            teeth_count = gear.getTeethCount();
            set_tooth_width_angle(radius);
            UtilityFunctions::print("--------------->   teeth_count:" , teeth_count );
        }
    };
    float get_down_tooth_width() const{return down_tooth_width;};

    void set_tooth_height(float height){ tooth_height = height;};
    float get_tooth_height() const{return tooth_height;};

    void set_radius(float m_radius){ 
        GearWheelCalculator gear(m_radius,down_tooth_width);
        int count=0;
        if (!gear.isDivisibleBy360(count)) {
            radius = gear.findNearestValidRadius();
            teeth_count = gear.getTeethCount();
            set_tooth_width_angle(radius);
            UtilityFunctions::print("--------------->   teeth_count:" , teeth_count );
        }
    };
    float get_radius() {
         
        set_polygon(generate_gear_vertices());
        return radius; 
    };


    // void update_polygon();
    // void _notification(int p_what);



};

#endif