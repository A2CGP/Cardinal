cmake_minimum_required(VERSION 3.26)

project(glad LANGUAGES CXX)

set(SOURCES_GLAD
  "include/glad/glad.h"
  "include/KHR/khrplatform.h"
  "src/glad.c"
)

add_library(glad STATIC ${SOURCES_GLAD})
set_target_properties(glad PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")
endif()