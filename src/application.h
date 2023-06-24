#pragma once

#include <SDL3/SDL.h>

namespace Cardinal {

class Application {
 public:
  void Render();
  void ProcessEvent(const SDL_Event* event);
  bool Quit();
};

}  // namespace Cardinal