<details open>
<summary><span style="color:tomato;font-size:16px">Библиотека nlohmann</span></summary>
<details open>
<summary><span style="color:tomato;font-size:12px">Установить</span></summary>

В самом простейшем случае в CMakeLists прописываем:

```cmake
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
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
# block #1 <-

add_executable(infoJsonNlohmann main.cpp)

# block #2 ->
# Здесь можно подключить дополнительные библиотеки
target_link_libraries(infoJsonNlohmann PRIVATE nlohmann_json::nlohmann_json)
# block #2 <-
```
Где наименование текущего проекта - infoJsonNlohmann - меняем на своё

</details>

<details open>
<summary><span style="color:tomato;font-size:12px">INFO</span></summary>

[//]: # (<a href="" style="margin-left:16px">REF</a>)

</details>
</details>