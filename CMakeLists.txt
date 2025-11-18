cmake_minimum_required(VERSION "3.23")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Realease>")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build SFML as static libraries" FORCE)
set(SFML_STATIC_LIBRARIES TRUE)

project(snake)

add_subdirectory(thirdparty/SFML)

set(PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries("${CMAKE_PROJECT_NAME}" 
	sfml-graphics 
	sfml-window 
	sfml-system
    pthread
    -static-libgcc 
    -static-libstdc++
)