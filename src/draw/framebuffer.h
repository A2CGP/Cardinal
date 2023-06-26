#pragma once

#include <glad/glad.h>

namespace Cardinal {

class FrameBuffer {
 public:
  FrameBuffer(int width, int height, int samples);
  ~FrameBuffer();
  void Clear(const float r, const float g, const float b);
  void Resize(int width, int height, int samples);
  void BlitToScreen(int width, int height);

 private:
  void Create();
  void Destroy();

 private:
  int width_ = 0;
  int height_ = 0;
  int samples_ = 1;
  GLuint texture_ = 0;
  GLuint framebuffer_ = 0;
};

}  // namespace Cardinal