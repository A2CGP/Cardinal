#pragma once

#include <SDL3/SDL.h>

#include "gui/manager.h"

namespace Cardinal {

class Application {
 public:
  void Render();
  void ProcessEvent(const SDL_Event* event);
  bool Quit();

 private:
  Manager gui_;
};

}  // namespace Cardinal