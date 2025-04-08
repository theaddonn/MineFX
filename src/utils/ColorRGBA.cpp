#pragma once
#include "ColorRGB.cpp"
#include <cstdint>
#include <iostream>

struct RGBA {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255; // Default to fully opaque

    // Constructors
    constexpr RGBA() = default;
    constexpr RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {
    }

    // Common Colors
    static constexpr RGBA Black() {
        return RGBA(0, 0, 0, 255);
    }
    static constexpr RGBA White() {
        return RGBA(255, 255, 255, 255);
    }
    static constexpr RGBA Red() {
        return RGBA(255, 0, 0, 255);
    }
    static constexpr RGBA Green() {
        return RGBA(0, 255, 0, 255);
    }
    static constexpr RGBA Blue() {
        return RGBA(0, 0, 255, 255);
    }
    static constexpr RGBA Transparent() {
        return RGBA(0, 0, 0, 0);
    }

    // Equality operators
    constexpr bool operator==(const RGBA& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    constexpr bool operator!=(const RGBA& other) const {
        return !(*this == other);
    }

    // Construct an RGBA from an RGB (with full opacity)
    constexpr explicit RGBA(const RGB& color) : r(color.r), g(color.g), b(color.b), a(255) {
    }
};

// Stream output for RGBA (casting to int to display numeric values)
inline std::ostream& operator<<(std::ostream& os, const RGBA& color) {
    return os << "RGBA(" << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", "
              << static_cast<int>(color.b) << ", " << static_cast<int>(color.a) << ")";
}
