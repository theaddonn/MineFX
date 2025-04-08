#pragma once
#include "Json.cpp"
#include <cmath>
#include <iostream>
#include <type_traits>

template <typename T>
struct Vec3 {
    static_assert(std::is_integral<T>::value, "T must be an integral type");

    T x = 0;
    T y = 0;
    T z = 0;

    // Constructors
    constexpr Vec3() = default;
    constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {
    }

    // Static constants
    static constexpr Vec3 Zero() return Vec3(0, 0, 0);
    static constexpr Vec3 One() return Vec3(1, 1, 1);

    // Unary operators
    constexpr Vec3 operator+() const {
        return *this;
    }
    constexpr Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }

    // Compound assignment
    inline Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    inline Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    inline Vec3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    inline Vec3& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Basic operations
    [[nodiscard]] inline T lengthSquared() const {
        return x * x + y * y + z * z;
    }

    [[nodiscard]] inline double length() const {
        return std::sqrt(static_cast<double>(lengthSquared()));
    }

    // Dot product
    [[nodiscard]] inline T dot(const Vec3& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    // Cross product
    [[nodiscard]] inline Vec3 cross(const Vec3& rhs) const {
        return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }

    // Normalize the vector
    inline void normalize() {
        T lenSquared = lengthSquared();
        if (lenSquared != 0) {
            T length = static_cast<T>(std::sqrt(static_cast<double>(lenSquared)));
            x /= length;
            y /= length;
            z /= length;
        }
    }

    [[nodiscard]] inline Vec3 normalized() const {
        Vec3 result = *this;
        result.normalize();
        return result;
    }

    // Comparison operators
    constexpr bool operator==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    constexpr bool operator!=(const Vec3& rhs) const {
        return !(*this == rhs);
    }

    // Json serialization/deserialization
    static std::expected<Vec3<T>, JsonError> from_json(const json& j) {
        if (!j.is_array()) {
            return std::unexpected(JsonError::InvalidType);
        }

        if (j.size() != 3) {
            return std::unexpected(JsonError::InvalidSize);
        }

        try {
            T x = j.at(0).get<T>();
            T y = j.at(1).get<T>();
            T z = j.at(2).get<T>();
            return Vec3<T>(x, y, z);
        } catch (...) {
            return std::unexpected(JsonError::InvalidType);
        }
    }

    json to_json() const {
        return json {x, y, z};
    }
};

// Non-member binary operators
template <typename T>
[[nodiscard]] inline Vec3<T> operator+(Vec3<T> lhs, const Vec3<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
[[nodiscard]] inline Vec3<T> operator-(Vec3<T> lhs, const Vec3<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
[[nodiscard]] inline Vec3<T> operator*(Vec3<T> vec, T scalar) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec3<T> operator*(T scalar, Vec3<T> vec) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec3<T> operator/(Vec3<T> vec, T scalar) {
    return vec /= scalar;
}

// Stream output
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
    return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
}
