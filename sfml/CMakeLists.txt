cmake_minimum_required(VERSION 3.13.4)
project(zappy_graphic)

include_directories(include)
add_executable(zappy_graphic src/App.cpp src/Cli.cpp src/Home.cpp src/Ia.cpp src/Render.cpp src/Serv.cpp src/Team.cpp src/Tools.cpp)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(zappy_graphic PRIVATE sfml-graphics sfml-window sfml-system)
