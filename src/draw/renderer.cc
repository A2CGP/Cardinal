#include "renderer.h"

namespace Cardinal {

Renderer::Renderer(int width, int height, int samples)
    : width_(width), height_(height), framebuffer_(width, height, samples) {}

void Renderer::Begin() {
  glViewport(0, 0, width_, height_);
  framebuffer_.Clear(0.0f, 0.0f, 1.0f);
}

void Renderer::Complete() { framebuffer_.BlitToScreen(width_, height_); }

}  // namespace Cardinal