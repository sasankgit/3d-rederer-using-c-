#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vec3 cross(const Vec3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        float len = length();
        return {x / len, y / len, z / len};
    }
};

struct Mat4 {
    float m[4][4];

    static Mat4 identity() {
        Mat4 result = {};
        for (int i = 0; i < 4; ++i) {
            result.m[i][i] = 1.0f;
        }
        return result;
    }

    static Mat4 translate(const Vec3& translation) {
        Mat4 result = identity();
        result.m[3][0] = translation.x;
        result.m[3][1] = translation.y;
        result.m[3][2] = translation.z;
        return result;
    }

    static Mat4 rotate(float angle, const Vec3& axis) {
        Mat4 result = identity();
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        float oneMinusCosA = 1.0f - cosA;

        result.m[0][0] = cosA + axis.x * axis.x * oneMinusCosA;
        result.m[0][1] = axis.x * axis.y * oneMinusCosA - axis.z * sinA;
        result.m[0][2] = axis.x * axis.z * oneMinusCosA + axis.y * sinA;

        result.m[1][0] = axis.y * axis.x * oneMinusCosA + axis.z * sinA;
        result.m[1][1] = cosA + axis.y * axis.y * oneMinusCosA;
        result.m[1][2] = axis.y * axis.z * oneMinusCosA - axis.x * sinA;

        result.m[2][0] = axis.z * axis.x * oneMinusCosA - axis.y * sinA;
        result.m[2][1] = axis.z * axis.y * oneMinusCosA + axis.x * sinA;
        result.m[2][2] = cosA + axis.z * axis.z * oneMinusCosA;

        return result;
    }
};

#endif // MATH_UTILS_H