cmake_minimum_required(VERSION 3.26)

project(Cardinal
  VERSION 0.1
  DESCRIPTION "Practice Interactive Computer Graphics"
  HOMEPAGE_URL https://github.com/A2CGP/Cardinal
  LANGUAGES CXX
)

set(SOURCES_CARDINAL_GUI
  "src/gui/manager.h"
  "src/gui/manager.cc"
)
source_group(gui FILES ${SOURCES_CARDINAL_GUI})

set(SOURCES_CARDINAL_PLATFORM
  "third_party/imgui/imgui/backends/imgui_impl_opengl3.h"
  "third_party/imgui/imgui/backends/imgui_impl_opengl3.cpp"
  "third_party/imgui/imgui/backends/imgui_impl_sdl3.h"
  "third_party/imgui/imgui/backends/imgui_impl_sdl3.cpp"
  "src/platform/platform.h"
  "src/platform/platform.cc"
)
source_group(platform FILES ${SOURCES_CARDINAL_PLATFORM})

set(SOURCES_CARDINAL_UTILS
  "src/utils/stb_image.h"
  "src/utils/stb_perlin.h"
)
source_group(utils FILES ${SOURCES_CARDINAL_UTILS})

set(SOURCES_CANDINAL
  ${SOURCES_CARDINAL_GUI}
  ${SOURCES_CARDINAL_PLATFORM}
  ${SOURCES_CARDINAL_UTILS}
  "src/application.h"
  "src/application.cc"
  "src/main.cc"
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(Cardinal ${SOURCES_CANDINAL})
set_target_properties(Cardinal PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  CMAKE_CXX_STANDARD_REQUIRED ON
)

if (MSVC)
  add_definitions(/wd4819)
  set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:msvcrt.lib)
  target_compile_options(Cardinal PRIVATE /W4 /WX)
else()
  target_compile_options(Cardinal PRIVATE -Wall -Wextra -Werror)
endif()

include_directories(
  "${PROJECT_SOURCE_DIR}/third_party/assimp/include"
  "${CMAKE_BINARY_DIR}/third_party/assimp/include"
  "${PROJECT_SOURCE_DIR}/third_party/glad/include"
  "${PROJECT_SOURCE_DIR}/third_party/glm"
  "${CMAKE_BINARY_DIR}/third_party/glog"
  "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui"
  "${PROJECT_SOURCE_DIR}/third_party/imgui/imgui/backends"
)

target_include_directories(Cardinal PRIVATE
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_SOURCE_DIR}/third_party/SDL/include"
  "${CMAKE_BINARY_DIR}/third_party/SDL/include"
)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
add_subdirectory("third_party/assimp")
add_subdirectory("third_party/glad")
set(BUILD_TESTING OFF)
add_subdirectory("third_party/glm")
set(WiTH_GTEST OFF)
add_subdirectory("third_party/glog")
add_subdirectory("third_party/imgui")
set(SDL_TEST OFF)
add_subdirectory("third_party/SDL")

target_link_libraries(Cardinal PRIVATE assimp)
target_link_libraries(Cardinal PRIVATE glad)
target_link_libraries(Cardinal PRIVATE glm)
target_link_libraries(Cardinal PRIVATE glog::glog)
target_link_libraries(Cardinal PRIVATE imgui)
target_link_libraries(Cardinal PRIVATE SDL3::SDL3)