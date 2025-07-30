#include <iostream>
#include <cmath>
#include <limits>
#include <vector>


class GearWheel{
private:
    double radius;    // 圆半径
    double chord;     // 弦长
    double angle;     // 弦对应的圆心角（角度制）


public:
    // 构造函数：初始化半径和弦长
    GearWheel(double r, double c) : radius(r), chord(c) {
        validateInput();
        calculateAngle();
    }

    // 验证输入有效性
    void validateInput() {
        if (radius <= 0 || chord <= 0) {
            throw std::invalid_argument("半径和弦长必须大于0");
        }
        if (chord > 2 * radius) {
            throw std::invalid_argument("弦长不能超过直径");
        }
    }

    // 计算弦对应的圆心角（核心公式）
    void calculateAngle() {
        double halfChord = chord / 2;
        double sinValue = halfChord / radius;
        angle = 2 * asin(sinValue) * 180.0 / M_PI; // 弧度转角度[2](@ref)
    }

    // 判断角度是否可整除360°（误差±0.01°）
    bool isDivisibleBy360(int& count) const {
        double ratio = 360.0 / angle;
        double fractionalPart = ratio - std::floor(ratio);
        if (std::abs(fractionalPart) < 0.01 || std::abs(1 - fractionalPart) < 0.01){
            if(std::abs(fractionalPart) < 0.01){ count = int(ratio); }
            if(std::abs(1 - fractionalPart) < 0.01){ count = int(ratio)+1; }
            return true;
        }
        return false;
    }

 // 寻找最近的可整除半径（双向搜索）
    double findNearestValidRadius(double step = 0.01) {
        double originalRadius = radius;
        double upRadius = radius;   // 向上搜索的半径
        double downRadius = radius; // 向下搜索的半径
        bool found_up = false;
        bool found_down = false;
        double valid_up = -1.0;
        double valid_down = -1.0;

        // 双向搜索直到找到有效解
        for (int i = 0; i < 100000; ++i) { // 防无限循环
            // 向上搜索
            if (!found_up) {
                try {
                    GearWheel upCalc(upRadius, chord);
                    int count=0;
                    if (upCalc.isDivisibleBy360(count)) {
                        valid_up = upRadius;
                        found_up = true;
                        std::cout << "------------------->   upRadius:" << upRadius <<"  count:" << count <<std::endl;
                    }
                } catch (...) {
                    // 忽略无效半径
                }
            }

            // 向下搜索
            if (!found_down && downRadius > chord / 2) {
                try {
                    GearWheel downCalc(downRadius, chord);
                    int count=0;
                    if (downCalc.isDivisibleBy360(count)) {
                        valid_down = downRadius;
                        found_down = true;
                        std::cout <<"------------------->   downRadius:" << downRadius <<"  count:" << count  << std::endl;
                    }
                } catch (...) {
                    // 忽略无效半径
                }
            }

            // 如果两个方向都找到了有效解，立即退出循环
            if (found_up && found_down) {

                break;
            }

            // 更新搜索半径
            upRadius += step;
            downRadius -= step;
        }
        if (valid_up < 0 || valid_down < 0){
            if(valid_up > 0){return valid_up;}
            if(valid_down < 0){return valid_down;}
            return -1;
        }
        // std::cout << "upRadius:" << upRadius << "   downRadius:" << downRadius << std::endl;
        return (valid_down-originalRadius) < (upRadius -originalRadius) ? valid_down : upRadius;
    
    }

    // 打印结果
    void printResult() const {
        std::cout << "半径: " << radius << ", 弦长: " << chord
                  << ", 圆心角: " << angle << "°\n";
        int count=0;
        std::cout << "可整除360°: " << (isDivisibleBy360(count) ? "是" : "否") << "\n";
    }

    // Getter方法
    double getAngle() const { return angle; }
    double getRadius() const { return radius; }
};

// // 示例用法
// int main() {
//     try {
//         GearWheel gear(100.0, 50.6); // 120°圆心角
//         gear.printResult();
//         int count=0;
//         if (!gear.isDivisibleBy360(count)) {
//             double newRadius = gear.findNearestValidRadius();
//             std::cout << "最近有效半径: " << newRadius << "\n";
//             gear.printResult();
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "错误: " << e.what() << std::endl;
//     }
//     return 0;
// }