#pragma once
#include <cstdint>
#include <iostream>

struct RGB {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    // Constructors
    constexpr RGB() = default;
    constexpr RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {
    }

    // Common Colors
    static constexpr RGB Black() {
        return RGB(0, 0, 0);
    }
    static constexpr RGB White() {
        return RGB(255, 255, 255);
    }
    static constexpr RGB Red() {
        return RGB(255, 0, 0);
    }
    static constexpr RGB Green() {
        return RGB(0, 255, 0);
    }
    static constexpr RGB Blue() {
        return RGB(0, 0, 255);
    }

    // Equality operators
    constexpr bool operator==(const RGB& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
    constexpr bool operator!=(const RGB& other) const {
        return !(*this == other);
    }
};

// Stream output for RGB (casting to int to display numeric values)
inline std::ostream& operator<<(std::ostream& os, const RGB& color) {
    return os << "RGB(" << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", "
              << static_cast<int>(color.b) << ")";
}

// RGBA struct with 8-bit components
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
