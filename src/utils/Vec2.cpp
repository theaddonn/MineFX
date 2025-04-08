#pragma once
#include "Json.cpp"
#include <cmath>
#include <expected>
#include <iostream>
#include <type_traits>

template <typename T>
struct Vec2 {
    static_assert(std::is_integral<T>::value, "T must be an integral type");

    T x = 0;
    T y = 0;

    // Constructors
    constexpr Vec2() = default;
    constexpr Vec2(T x, T y) : x(x), y(y) {
    }

    // Static constants
    static constexpr Vec2 Zero() {
        return Vec2(0, 0);
    }
    static constexpr Vec2 One() {
        return Vec2(1, 1);
    }

    // Unary operators
    constexpr Vec2 operator+() const {
        return *this;
    }
    constexpr Vec2 operator-() const {
        return Vec2(-x, -y);
    }

    // Compound assignment
    inline Vec2& operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    inline Vec2& operator-=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    inline Vec2& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    inline Vec2& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Basic operations
    [[nodiscard]] inline T lengthSquared() const {
        return x * x + y * y;
    }

    [[nodiscard]] inline double length() const {
        return std::sqrt(static_cast<double>(lengthSquared()));
    }

    // Dot product
    [[nodiscard]] inline T dot(const Vec2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    // Normalize the vector
    inline void normalize() {
        T lenSquared = lengthSquared();
        if (lenSquared != 0) {
            T length = static_cast<T>(std::sqrt(static_cast<double>(lenSquared)));
            x /= length;
            y /= length;
        }
    }

    [[nodiscard]] inline Vec2 normalized() const {
        Vec2 result = *this;
        result.normalize();
        return result;
    }

    // Perpendicular vector (rotated 90 degrees)
    [[nodiscard]] inline Vec2 perpendicular() const {
        return Vec2(-y, x);
    }

    // Comparison operators
    constexpr bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    constexpr bool operator!=(const Vec2& rhs) const {
        return !(*this == rhs);
    }

    // Error type for JSON serialization/deserialization
    enum class JsonError { InvalidSize, InvalidType };

    // Json serialization/deserialization
    static std::expected<Vec2<T>, JsonError> from_json(const nloahman::json& json) {
        if (!json.is_array()) {
            return std::unexpected(JsonError::InvalidType);
        }

        if (json.size() != 2) {
            return std::unexpected(JsonError::InvalidSize);
        }

        try {
            T x = json.at(0).get<T>();
            T y = json.at(1).get<T>();
            return Vec2<T>(x, y);
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
[[nodiscard]] inline Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs) {
    return lhs += rhs;
}

template <typename T>
[[nodiscard]] inline Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs) {
    return lhs -= rhs;
}

template <typename T>
[[nodiscard]] inline Vec2<T> operator*(Vec2<T> vec, T scalar) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec2<T> operator*(T scalar, Vec2<T> vec) {
    return vec *= scalar;
}

template <typename T>
[[nodiscard]] inline Vec2<T> operator/(Vec2<T> vec, T scalar) {
    return vec /= scalar;
}

// Stream output
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
    return os << "Vec2(" << +v.x << ", " << +v.y << ")";
}
