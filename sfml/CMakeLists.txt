cmake_minimum_required(VERSION 3.13.4)
project(zappy_graphic)

include_directories(include)
add_executable(zappy_graphic src/Application.cpp src/Client.cpp src/Main.cpp src/Player.cpp src/Render.cpp src/Server.cpp src/Team.cpp src/Utils.cpp)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(zappy_graphic PRIVATE sfml-graphics sfml-window sfml-system)
