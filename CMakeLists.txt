cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
  message("hello apple")
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml")
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)
## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths" SYSTEM INTERFACE ${SFML_INCS})
## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES engine/lib_tile_level_loader/*.cpp engine/lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)
## ECM lib
file(GLOB_RECURSE SOURCE_FILES engine/lib_ecm/*.cpp engine/lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

#### Add Practical Projects####
#file(GLOB_RECURSE SOURCES practical_1_pong/stage_1.cpp)
#add_executable(PRACTICAL_1_PONG ${SOURCES} ${RESOURCE_FILES})
#target_include_directories(PRACTICAL_1_PONG SYSTEM PRIVATE ${SFML_INCS})
#set(EXECUTABLES ${EXECUTABLES} PRACTICAL_1_PONG)

#file(GLOB_RECURSE SOURCES practical_1_pong/finished.cpp)
#add_executable(PRACTICAL_1_PONG_F ${SOURCES} ${RESOURCE_FILES})
#target_include_directories(PRACTICAL_1_PONG_F SYSTEM PRIVATE ${SFML_INCS})
#set(EXECUTABLES ${EXECUTABLES} PRACTICAL_1_PONG_F)

file(GLOB_RECURSE SOURCES practical_1_pong/*.cpp)
add_executable(PRACTICAL_1_PONG ${SOURCES} ${RESOURCE_FILES})
target_include_directories(PRACTICAL_1_PONG SYSTEM PRIVATE ${SFML_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_1_PONG)


## Space invaders
file(GLOB_RECURSE SOURCES practical_2_space_invaders/*.cpp practical_2_space_invaders/*.h)
add_executable(PRACTICAL_2_INVADERS ${SOURCES} ${RESOURCE_FILES})
target_include_directories(PRACTICAL_2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_2_INVADERS)

## tiled level maze
file(GLOB_RECURSE SOURCES practical_3_tiled_levels/*.cpp practical_3_tiled_levels/*.h)
add_executable(PRACTICAL_3_TILED_LEVELS ${SOURCES} ${RESOURCE_FILES})
target_include_directories(PRACTICAL_3_TILED_LEVELS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_3_TILED_LEVELS lib_tile_level_loader)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_3_TILED_LEVELS)

## ECM
file(GLOB_RECURSE SOURCES practical_4_ecm/*.cpp practical_4_ecm/*.h)
add_executable(PRACTICAL_4_ECM ${SOURCES} ${RESOURCE_FILES})
target_include_directories(PRACTICAL_4_ECM SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_4_ECM lib_tile_level_loader lib_ecm)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_4_ECM)

## physics
file(GLOB_RECURSE SOURCES practical_5_physics/*.cpp practical_5_physics/*.h)
add_executable(PRACTICAL_5_PHYSICS ${SOURCES} ${RESOURCE_FILES})
target_include_directories(PRACTICAL_5_PHYSICS SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PRACTICAL_5_PHYSICS Box2D)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_5_PHYSICS)

## platformer
file(GLOB_RECURSE SOURCES practical_6_platformer/*.cpp practical_6_platformer/*.h)
file(GLOB_RECURSE CMPNTS practical_6_platformer/components/*.cpp practical_6_platformer/components/*.h)
file(GLOB_RECURSE SCENES practical_6_platformer/scenes/*.cpp practical_6_platformer/scenes/*.h)
add_executable(PRACTICAL_6_PLATFORMER ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
#target_include_directories(PRACTICAL_6_PLATFORMER SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PRACTICAL_6_PLATFORMER lib_engine)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_6_PLATFORMER)

## movement
file(GLOB_RECURSE SOURCES practical_7_steering/*.cpp practical_7_steering/*.h)
file(GLOB_RECURSE CMPNTS practical_7_steering/components/*.cpp practical_7_steering/components/*.h)
file(GLOB_RECURSE SCENES practical_7_steering/scenes/*.cpp practical_7_steering/scenes/*.h)
add_executable(PRACTICAL_7_STEERING ${SOURCES} ${CMPNTS} ${SCENES} ${RESOURCE_FILES})
target_link_libraries(PRACTICAL_7_STEERING lib_engine)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_7_STEERING)

#### Target for copying resources to build dir####
if(APPLE)
  add_custom_target(copy_resources ALL
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/lib/sfml/extlibs/libs-osx/Frameworks" ${CMAKE_BINARY_DIR}/lib/sfml/Frameworks
          )
else()
  add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
          )
endif()

#### Link Dependencies ####
foreach (exe ${EXECUTABLES})
  #Set working directory to build dir
  set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
  )

  target_link_libraries(${exe}
          lib_maths
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-audio debug sfml-audio-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d
    optimized sfml-graphics debug sfml-graphics-d
    #optimized sfml-main
  )

  #target_link_libraries(${exe} "${CMAKE_SOURCE_DIR}/lib/sfml/extlibs/libs-osx/Frameworks/f‌​reetype.framework/Ve‌​rsions/A/freetype")

  add_dependencies(${exe} sfml-graphics sfml-audio copy_resources)
endforeach ()
