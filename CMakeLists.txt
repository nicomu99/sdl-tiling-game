cmake_minimum_required(VERSION 3.29)
project(tiling_game)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Add the include directory to the search path
include_directories(${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/model
        ${PROJECT_SOURCE_DIR}/include/view
        ${PROJECT_SOURCE_DIR}/include/controller)

add_executable(tiling_game src/main.cpp
        include/Constants.hpp
        include/controller/Controller.hpp
        src/controller/Controller.cpp
        include/view/View.hpp
        src/view/View.cpp
        include/model/Model.hpp
        src/model/Model.cpp
        include/model/Grid.hpp
        src/model/Grid.cpp
        include/model/Player.hpp
        src/model/Player.cpp
        include/controller/SDLManager.hpp
        src/controller/SDLManager.cpp)

target_link_libraries(tiling_game SDL2::SDL2)