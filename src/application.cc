#include "application.h"

#include <imgui.h>

namespace Cardinal {

void Application::Render() {}

void Application::ProcessEvent(const SDL_Event* event) {
  ImGuiIO& io = ImGui::GetIO();

  switch (event->type) {
    case SDL_EVENT_KEY_DOWN:
      if (io.WantCaptureKeyboard) break;
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (io.WantCaptureKeyboard) break;
      break;
    case SDL_EVENT_MOUSE_WHEEL:
      if (io.WantCaptureKeyboard) break;
      break;
  }
}

bool Application::Quit() { return true; }

}  // namespace Cardinal