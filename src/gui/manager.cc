#include "manager.h"

#include <imgui.h>

namespace Cardinal {

void Manager::Render() { RenderMenuBar(); }

float Manager::RenderMenuBar() {
  float menu_bar_height = 0.0f;

  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::EndMenu();
    }
    ImGui::Button("Layout");
    ImGui::Button("Model");
    
    menu_bar_height = ImGui::GetWindowSize().y;
    ImGui::EndMainMenuBar();
  }

  return menu_bar_height;
}

}  // namespace Cardinal