cmake_minimum_required(VERSION 3.19)
project(_PROG_Robots_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(files)
include_directories(utils)

add_executable(_PROG_Robots_Game main.cpp utils/fileHandler.cpp utils/fileHandler.h menu_control.cpp menu_control.h utils/macros.h exception.h game.cpp game.h utils/utils.cpp utils/utils.h gameSymbol.cpp gameSymbol.h maze.cpp maze.h utils/position.h)