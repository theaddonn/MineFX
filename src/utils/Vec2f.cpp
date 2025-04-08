#pragma once
#include "Json.cpp"
#include <cmath>
#include <expected>
#include <iostream>
#include <type_traits>

template <typename T>
struct Vec2f {
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    T x = 0;
    T y = 0;

    // Constructors
    constexpr Vec2f() = default;
    constexpr Vec2f(T x, T y) : x(x), y(y) {
    }

    // Static constants
    static constexpr Vec2f Zero() {
        return Vec2f(0.0, 0.0);
    }
    static constexpr Vec2f One() {
        return Vec2f(1.0, 1.0);
    }

    // Unary operators
    constexpr Vec2f operator+() const {
        return *this;
    }
    constexpr Vec2f operator-() const {
        return Vec2f(-x, -y);
    }

    // Compound assignment
    inline Vec2f& operator+=(const Vec2f& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    inline Vec2f& operator-=(const Vec2f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    inline Vec2f& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    inline Vec2f& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Basic operations
    [[nodiscard]] inline T lengthSquared() const {
        return x * x + y * y;
    }

    [[nodiscard]] inline T length() const {
        return std::sqrt(lengthSquared());
    }

    // Dot product
    [[nodiscard]] inline T dot(const Vec2f& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    // Normalize the vector
    inline void normalize() {
        T lenSquared = lengthSquared();
        if (lenSquared != 0) {
            T length = std::sqrt(lenSquared);
            x /= length;
            y /= length;
        }
    }

    [[nodiscard]] inline Vec2f normalized() const {
        Vec2f result = *this;
        result.normalize();
        return result;
    }

    // Perpendicular vector (rotated 90 degrees)
    [[nodiscard]] inline Vec2f perpendicular() const {
        return Vec2f(-y, x);
    }

    // Comparison operators
    constexpr bool operator==(const Vec2f& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    constexpr bool operator!=(const Vec2f& rhs) const {
        return !(*this == rhs);
    }

    // Json serialization/deserialization
    static std::expected<Vec2f<T>, JsonError> from_json(const nlohmann::json& j) {
        if (!j.is_array()) {
            return std::unexpected(JsonError::InvalidType);
        }

        if (j.size() != 2) {
            return std::unexpected(JsonError::InvalidSize);
        }

        try {
            T x = j.at(0).get<T>();
            T y = j.at(1).get<T>();
            return Vec2f<T>(x, y);
        } catch (...) {
            return std::unexpected(JsonError::InvalidType);
        }
    }

    nlohmann::json to_json() const {
        return json {x, y};
    }
};

// Non-member binary operators
template <typename T>
[[nodiscard]] inline Vec2f<T> operator+(Vec2f<T> lhs, const Vec2f<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
[[nodiscard]] inline Vec2f<T> operator-(Vec2f<T> lhs, const Vec2f<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
[[nodiscard]] inline Vec2f<T> operator*(Vec2f<T> vec, T scalar) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec2f<T> operator*(T scalar, Vec2f<T> vec) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec2f<T> operator/(Vec2f<T> vec, T scalar) {
    return vec /= scalar;
}

// Stream output
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec2f<T>& v) {
    return os << "Vec2f(" << v.x << ", " << v.y << ")";
}
