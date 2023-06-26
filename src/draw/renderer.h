#pragma once

#include "framebuffer.h"

namespace Cardinal {

class Renderer {
 public:
  Renderer(int width, int height, int samples);
  void Begin();
  void Complete();

 private:
  int width_ = 0;
  int height_ = 0;
  FrameBuffer framebuffer_;
};

}  // namespace Cardinal