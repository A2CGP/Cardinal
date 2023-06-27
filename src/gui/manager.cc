#include "manager.h"

#include <imgui.h>

namespace Cardinal {

void Manager::Render() { RenderMenuBar(); }

float Manager::RenderMenuBar() {
  float menu_bar_height = 0.0f;

  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("Open...", "Ctrl+O");
      ImGui::MenuItem("Save", "Ctrl+S");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      ImGui::MenuItem("Undo", "Ctrl+Z");
      ImGui::MenuItem("Redo", "Shift+Ctrl+Z");
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