#pragma once

#include "application.h"

namespace Cardinal {

class Platform {
 public:
  Platform() { Init(); }
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
};

}  // namespace Cardinal