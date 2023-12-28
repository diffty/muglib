cmake_minimum_required(VERSION 3.20.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(muglib_sample)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Muglib")
set(VITA_TITLEID  "MUG00001")
set(VITA_VERSION  "00.01")
set(VITA_EMU_STORAGE_PATH "/Users/diffty/Library/Application Support/Vita3K/Vita3K/ux0/app")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -D TARGET_PSVITA")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  platform/**
  utils/**
  core/**
)

add_executable(${PROJECT_NAME}
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

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
)

add_custom_target(
  ${PROJECT_NAME}.vpk-install
  ALL
  COMMAND unzip -o ${PROJECT_NAME}.vpk -d ${VITA_EMU_STORAGE_PATH}/${VITA_TITLEID}/
  COMMENT "Installing vpk to emulator storage"
)
