cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(PLATFORM_TARGET STREQUAL PSVITA)
  if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
      set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else()
      message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
  endif()
endif()

if (NOT DEFINED PLATFORM_TARGET)
  set(PLATFORM_TARGET "")
endif()

string(TOUPPER "${PLATFORM_TARGET}" PLATFORM_TARGET_UPPER)
string(TOLOWER "${PLATFORM_TARGET}" PLATFORM_TARGET_LOWER)

project(muglib)

include(CTest)

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpmachine OUTPUT_VARIABLE COMPILER_TARGET OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "The CXX compiler target architecture is ${COMPILER_TARGET}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/${COMPILER_TARGET}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/${COMPILER_TARGET}/lib)
set(CMAKE_BINARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/${COMPILER_TARGET})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/${COMPILER_TARGET})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  platform/**
  utils/**
  core/**
)

add_library(${PROJECT_NAME}
  src/core/types.h
  src/core/graphics.c
  src/core/system.c
  src/core/input.c
  src/core/keys.c
  src/utils/time.c
  src/utils/random.c
  src/utils/maths.c
  src/utils/array.c
  src/utils/list.c
  src/utils/strings.c
  src/utils/linked_list.c
  src/graphics/drawing.c
  src/platform/defines.h
)

add_executable(test_str tests/test_str.c)
add_test(NAME test_str COMMAND ${CMAKE_BINARY_OUTPUT_DIRECTORY}/test_str)
target_link_libraries(test_str ${PROJECT_NAME})

add_executable(test_list tests/test_list.c)
add_test(NAME test_list COMMAND ${CMAKE_BINARY_OUTPUT_DIRECTORY}/test_list)
target_link_libraries(test_list ${PROJECT_NAME})

add_executable(test_log tests/test_log.c)
add_test(NAME test_log COMMAND ${CMAKE_BINARY_OUTPUT_DIRECTORY}/test_log)
target_link_libraries(test_log ${PROJECT_NAME})

IF (NOT WIN32)
  target_link_libraries(${PROJECT_NAME}
    m
  )
ENDIF()

if(PLATFORM_TARGET STREQUAL PSVITA)
  include("${VITASDK}/share/vita.cmake" REQUIRED)

  set(VITA_APP_NAME "Muglib")
  set(VITA_TITLEID  "MUG00001")
  set(VITA_VERSION  "00.01")

  add_library(${PROJECT_NAME}-${PLATFORM_TARGET_LOWER}
    src/main.c
    src/platform/psvita/inputmap.h
    src/platform/psvita/console/debugScreen.c
  )

  target_link_libraries(${PROJECT_NAME}-${PLATFORM_TARGET_LOWER}
    ${PROJECT_NAME}

    SceDisplay_stub
    SceCtrl_stub
    SceTouch_stub

    SceGxm_stub
    SceAppUtil_stub
    SceCommonDialog_stub
    SceSysmodule_stub
    SceIme_stub
  )

  target_compile_options(${PROJECT_NAME}-${PLATFORM_TARGET_LOWER} PUBLIC -D TARGET_${PLATFORM_TARGET_UPPER})
endif()
