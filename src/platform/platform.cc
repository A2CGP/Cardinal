#include "platform.h"

#include <glad/glad.h>
#include <glog/logging.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

namespace Cardinal {

void Platform::Init() {
  CHECK(SDL_Init(SDL_INIT_VIDEO) == 0)
      << "Failed to initialize SDL: " << SDL_GetError();

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  window_ = SDL_CreateWindow(
      settings_.title, settings_.width, settings_.height,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
  CHECK(window_) << "Failed to create window: " << SDL_GetError();

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  context_ = SDL_GL_CreateContext(window_);
  CHECK(context_) << "Failed to create OpenGL 4.6 context: " << SDL_GetError();

  SDL_GL_MakeCurrent(window_, context_);
  if (SDL_GL_SetSwapInterval(-1) != 0) {
    CHECK(SDL_GL_SetSwapInterval(1) == 0)
        << "Failed to setSwapInterval(1) for the current context: "
        << SDL_GetError();
  }

  CHECK(gladLoadGL()) << "Failed to load OpenGL functions";

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  ImFontConfig font_cfg;
  font_cfg.SizePixels = 28;
  io.Fonts->AddFontDefault(&font_cfg);
  ImGui_ImplSDL3_InitForOpenGL(window_, context_);
  ImGui_ImplOpenGL3_Init();

  renderer_ = new Renderer(settings_.width, settings_.height, settings_.samples);
}

void Platform::Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
  SDL_Quit();

  window_ = nullptr;
  context_ = nullptr;
  delete renderer_;
  renderer_ = nullptr;
}

void Platform::BeginFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void Platform::CompleteFrame() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(window_);
}

void Platform::Run(Application* app) {
  bool isRunning = true;

  LOG(INFO) << "Starting";
  CHECK(SDL_ShowWindow(window_) == 0)
      << "Failed to show window: " << SDL_GetError();

  while (isRunning) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      switch (event.type) {
        case SDL_EVENT_QUIT:
          isRunning = !app->Quit();
          break;
      }
      app->ProcessEvent(&event);
    }
    BeginFrame();
    renderer_->Begin();
    app->Render();
    renderer_->Complete();
    CompleteFrame();
  }

  LOG(INFO) << "Stopping";
}

}  // namespace Cardinal