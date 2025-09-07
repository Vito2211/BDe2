cmake_minimum_required(VERSION 3.10)
project(BDe2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# collect all source files
file(GLOB SOURCES src/*.cpp *.cpp)

add_executable(BDe2 ${SOURCES})

# include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# search for raylib package
find_package(raylib 5.0 REQUIRED)
target_link_libraries(BDe2 PRIVATE raylib)

# frameworks and libraries for different platforms
if (APPLE)
    target_link_libraries(BDe2 PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif (UNIX AND NOT APPLE)
    target_link_libraries(BDe2 PRIVATE m pthread dl GL)
elseif (WIN32)
    target_link_libraries(BDe2 PRIVATE opengl32 gdi32 winmm)
endif()

# RAYGUI_IMPLEMENTATION 
target_compile_definitions(BDe2 PRIVATE RAYGUI_IMPLEMENTATION)
