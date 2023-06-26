#include "framebuffer.h"

#include <glog/logging.h>

namespace Cardinal {

FrameBuffer::FrameBuffer(int width, int height, int samples)
    : width_(width), height_(height), samples_(samples) {
  Resize(width, height, samples);
}

FrameBuffer::~FrameBuffer() {
  Destroy();
  width_ = height_ = 0;
  texture_ = framebuffer_ = 0;
}

void FrameBuffer::Create() {
  glCreateFramebuffers(1, &framebuffer_);
  if (samples_ > 1) {
    glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &texture_);
  } else {
    glCreateTextures(GL_TEXTURE_2D, 1, &texture_);
  }
}

void FrameBuffer::Destroy() {
  if (framebuffer_ != 0) {
    glDeleteFramebuffers(1, &framebuffer_);
  }
  if (texture_ != 0) {
    glDeleteTextures(1, &texture_);
  }
}

void FrameBuffer::Clear(const float r, const float g, const float b) {
  const float value[4] = {r, g, b, 1.0f};

  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
  glClearBufferfv(GL_COLOR, 0, value);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize(int width, int height, int samples) {
  CHECK(width > 0 && height > 0 && samples > 0);

  Destroy();
  Create();
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

  GLenum type = samples == 1 ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE;

  glBindTexture(type, texture_);
  if (samples > 1) {
    glTexImage2DMultisample(type, samples, GL_RGB8, width, height, GL_TRUE);
  } else {
    glTexImage2D(type, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 nullptr);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, type, texture_,
                         0);
  glBindTexture(type, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BlitToScreen(int width, int height) {
  CHECK(width > 0 && height > 0);

  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  glReadBuffer(GL_COLOR_ATTACHMENT0);
  glBlitFramebuffer(0, 0, width_, height_, 0, 0, width, height,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}  // namespace Cardinal