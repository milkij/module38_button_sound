cmake_minimum_required(VERSION 3.23)
project(RedButton)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/local")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(RedButton main.cpp)
target_link_libraries(RedButton
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Multimedia
        )





