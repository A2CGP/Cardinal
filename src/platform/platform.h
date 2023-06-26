#pragma once

#include "application.h"
#include "draw/renderer.h"

namespace Cardinal {

class Platform {
 public:
  struct Settings {
    char* title;
    int width;
    int height;
    int samples;
  };

 public:
  Platform() : settings_({"Cardinal", 1400, 1200, 4}) { Init(); }
  ~Platform() { Shutdown(); }
  void Run(Application* app);

 private:
  void Init();
  void Shutdown();
  void BeginFrame();
  void CompleteFrame();

 private:
  SDL_Window* window_ = nullptr;
  SDL_GLContext context_ = nullptr;
  Settings settings_;
  Renderer* renderer_ = nullptr;
};

}  // namespace Cardinal