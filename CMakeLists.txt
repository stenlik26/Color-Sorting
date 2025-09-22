cmake_minimum_required(VERSION 3.15)
project(ColorSortingBlocks CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Grab raylib automatically if not present
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# Add your sources
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)
source_group("Header Files" FILES ${HEADERS})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} raylib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
