cmake_minimum_required(VERSION 3.5)

project(appcore)

find_package(Qt5 COMPONENTS Core Network Sql WebSockets REQUIRED)

include_directories(${PROJECT_NAME})

set(SOURCE_LIB client.h client.cpp)
add_library(appcore STATIC ${SOURCE_LIB})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Network Qt5::Sql Qt5::WebSockets)
