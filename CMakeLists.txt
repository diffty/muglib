cmake_minimum_required(VERSION 3.20.0)


if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


project(muglib)

include_directories(
  platform/**
  utils/**
  core/**
)

add_library(${PROJECT_NAME}
  src/main.c
  src/core/types.h
  src/core/graphics.c
  src/core/system.c
  src/core/input.c
  src/core/keys.c
  src/utils/time.c
  src/utils/random.c
  src/utils/maths.c
  src/utils/linked_list.c
  src/graphics/drawing.c
  src/platform/defines.h
  src/platform/psvita/inputmap.h
  src/platform/psvita/console/debugScreen.c
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/lib"
)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Muglib")
set(VITA_TITLEID  "MUG00001")
set(VITA_VERSION  "00.01")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -D TARGET_PSVITA")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries(${PROJECT_NAME}
  SceDisplay_stub
  SceCtrl_stub
  SceTouch_stub

  SceGxm_stub
  SceAppUtil_stub
  SceCommonDialog_stub
  SceSysmodule_stub

  m
)
