cmake_minimum_required(VERSION 3.0.0)
project(config_loader VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "下载第三方库")

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    FIND_PACKAGE_ARGS nlohmann_json 3.2.0 REQUIRED
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

message(STATUS "下载第三方库完成")


add_library(${PROJECT_NAME} INTERFACE)

target_compile_options(
    ${PROJECT_NAME} INTERFACE
    -std=c++17
)

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} INTERFACE
    nlohmann_json::nlohmann_json
)

add_executable(test tests/test.cpp)
target_include_directories(test PUBLIC ${PROJECT_NAME})
target_link_libraries(test PUBLIC ${PROJECT_NAME})