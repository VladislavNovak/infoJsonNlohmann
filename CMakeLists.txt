cmake_minimum_required(VERSION 3.26)
project(infoJsonNlohmann)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_CPR_TESTS OFF)
set(CMAKE_USE_OPENSSL OFF)
# Синхронизирует библиотеки
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
# block #1 ->
# Здесь можно добавлять дополнительные библиотеки

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# block #1 <-

add_executable(infoJsonNlohmann main.cpp)

# block #2 ->
# Здесь можно подключить дополнительные библиотеки
target_link_libraries(infoJsonNlohmann PRIVATE cpr::cpr)
target_link_libraries(infoJsonNlohmann PRIVATE nlohmann_json::nlohmann_json)
# block #2 <-

