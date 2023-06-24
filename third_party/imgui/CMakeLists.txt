cmake_minimum_required(VERSION 3.26)

project(imgui LANGUAGES CXX)

set(SOURCES_IMGUI
  "imgui/imconfig.h"
  "imgui/imgui.h"
  "imgui/imstb_truetype.h"
  "imgui/imstb_rectpack.h"
  "imgui/imstb_textedit.h"
  "imgui/imgui_internal.h"
  "imgui/imgui.cpp"
  "imgui/imgui_draw.cpp"
  "imgui/imgui_tables.cpp"
  "imgui/imgui_widgets.cpp"
)

add_library(imgui STATIC ${SOURCES_IMGUI})
set_target_properties(imgui PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")
endif()