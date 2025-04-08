#pragma once
#include "Json.cpp"
#include <cmath>
#include <iostream>
#include <type_traits>

template <typename T>
struct Vec3f {
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    T x = 0;
    T y = 0;
    T z = 0;

    // Constructors
    constexpr Vec3f() = default;
    constexpr Vec3f(T x, T y, T z) : x(x), y(y), z(z) {
    }

    // Static constants
    static constexpr Vec3f Zero() {
        return Vec3f(0.0, 0.0, 0.0);
    }
    static constexpr Vec3f One() {
        return Vec3f(1.0, 1.0, 1.0);
    }

    // Unary operators
    constexpr Vec3f operator+() const {
        return *this;
    }
    constexpr Vec3f operator-() const {
        return Vec3f(-x, -y, -z);
    }

    // Compound assignment
    inline Vec3f& operator+=(const Vec3f& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    inline Vec3f& operator-=(const Vec3f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    inline Vec3f& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    inline Vec3f& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Basic operations
    [[nodiscard]] inline T lengthSquared() const {
        return x * x + y * y + z * z;
    }

    [[nodiscard]] inline T length() const {
        return std::sqrt(lengthSquared());
    }

    // Dot product
    [[nodiscard]] inline T dot(const Vec3f& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    // Cross product
    [[nodiscard]] inline Vec3f cross(const Vec3f& rhs) const {
        return Vec3f(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }

    // Normalize the vector
    inline void normalize() {
        T lenSquared = lengthSquared();
        if (lenSquared != 0) {
            T length = std::sqrt(lenSquared);
            x /= length;
            y /= length;
            z /= length;
        }
    }

    [[nodiscard]] inline Vec3f normalized() const {
        Vec3f result = *this;
        result.normalize();
        return result;
    }

    // Comparison operators
    constexpr bool operator==(const Vec3f& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    constexpr bool operator!=(const Vec3f& rhs) const {
        return !(*this == rhs);
    }
};

// Non-member binary operators
template <typename T>
[[nodiscard]] inline Vec3f<T> operator+(Vec3f<T> lhs, const Vec3f<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
[[nodiscard]] inline Vec3f<T> operator-(Vec3f<T> lhs, const Vec3f<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
[[nodiscard]] inline Vec3f<T> operator*(Vec3f<T> vec, T scalar) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec3f<T> operator*(T scalar, Vec3f<T> vec) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec3f<T> operator/(Vec3f<T> vec, T scalar) {
    return vec /= scalar;
}

// Stream output
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3f<T>& v) {
    return os << "Vec3f(" << v.x << ", " << v.y << ", " << v.z << ")";
}
