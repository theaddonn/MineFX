#pragma once
#include "utils/Color.cpp"
#include "utils/Vec.cpp"
#include <array>

class RenderTexture {
  private:
    static constexpr Vec2<uint8_t> SIZE = {64, 64};

    std::array<std::array<RGBA, SIZE.x>, SIZE.y> pixelData = {};

  public:
};
