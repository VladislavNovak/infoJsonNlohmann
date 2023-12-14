<details open>
<summary><span style="color:tomato;font-size:16px">Библиотека nlohmann</span></summary>
<details>
<summary><span style="color:tomato;font-size:12px">Установка и CMake</span></summary>

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
Где наименование текущего проекта - infoJsonNlohmann - меняем на своё.

Сама библиотека находится по адресу: [nlohmann](https://json.nlohmann.me/integration/cmake/#supporting-both)

Теперь можем подключить библиотеку к модулю.
И для того чтобы не использовать области имён, подключаем:

```c++
#include <nlohmann/json.hpp>

using json = nlohmann::json;
```

Как подключить ещё дополнительные библиотеки (например, cpr) - можно увидеть в файле CMake в корне проекта

</details>

<details open>
<summary><span style="color:tomato;font-size:12px">Операции</span></summary>

<!-- TOC -->
* [Main](#main)
  * [Examples](#examples)
    * [`createSimpleJDoc`](#createsimplejdoc)
    * [`printDoc`](#printdoc)
    * [`convertJDocToString`](#convertjdoctostring)
    * [`createJsObj`](#createjsobj)
    * [`createJsArr`](#createjsarr)
    * [`validateJson`](#validatejson)
    * [`parseDataAsWholeWithGet`](#parsedataaswholewithget)
    * [`parseDataAsPartsWithGet`](#parsedataaspartswithget)
    * [`parseDataToMap`](#parsedatatomap)
    * [`requestGet`](#requestget)
    * [`requestPost`](#requestpost)
<!-- TOC -->

# Main

## Examples

---
### `createSimpleJDoc`

Примеры создания json объекта обычным присваиванием как в JS

```c++
void createSimpleJDoc() {
    json jDoc;
    // (string, boolean, int)
    jDoc["movie"] = "Star wars";
    jDoc["released"] = true;
    jDoc["year"] = 1977;
    // array
    jDoc["cast"] = { "Mark Hamill", "Harrison Ford", "Carrie Fisher" };
    // object
    jDoc["director"] = {{"name", "George Lucas"}, {"born", 1944}};
    // array of objects
    jDoc["similar_movies"] = {
            {{"name", "Dune"}, {"year", 2021}}, {{"name", "Rogue"}, {"year", 2016}}
    };
    // Можем использовать стандартные контейнеры
    std::vector cast{"Lucie", "Mike", "John"};
    jDoc["other"] = cast;

    cout << jDoc.dump(2) << endl;
}
```

---
### `printDoc`

```c++
void printDoc() {
    string data{R"({"name": "Roderick", "guild": {"name": "Reds"}})"};
    json jDoc(json::parse(data));
    // Без конвертации в string можем распечатать json или целиком ...
    cout << "Entire: " << jDoc << endl;
    // ... или по частям
    cout << "Part: " << jDoc["guild"] << endl;
}
```

---
### `convertJDocToString`

```c++
void convertJDocToString() {
    string data{R"({"name": "Roderick", "guild": {"name": "Reds"}})"};
    json jDoc(json::parse(data));

    // Метод dump позволяет конвертировать json объект снова в строку.
    // Аргументом можно задать форматирование для отступа
    string data2{jDoc.dump(2)};

    cout << data2 << endl;
}
```

---
### `createJsObj`

```c++
void createJsObj() {
    string ageTitle = "age";
    string ageCount = "36";
    // Создать строку с json объектом. Важно: это именно строка
    string data{R"({"city": "London", "guild": {"role": "Driver"}, "age": ")" + ageCount + R"("})"};
    cout << data << endl;

    // Строка, содержащая описание объекта, конвертируется в реальный json объект
    json jDoc(json::parse(data));

    // И обращаться к каждому элементу по имени
    string city{jDoc["city"]};
    cout << "city: " << city << endl;
    // Даже во вложенные
    string role{jDoc["guild"]["role"]};
    cout << "role: " << role << endl;
    // Или даже по имени переменной
    string personAge{jDoc[ageTitle]};
    cout << "age: " << personAge << endl;

    // Или обратиться через оператор .at("name"). Тогда может использоваться в конструкции try-catch
    try {
        string some{jDoc.at("some")};
        cout << "some: " << some << endl;
    }
    catch(json::exception &e) { cout << e.what() << endl; } // key 'some' not found
}
```

---
### `createJsArr`

```c++
void createJsArr() {
    string personName = "John";
    // Создаём js массив
    string data{R"(["John", "Nick", ")" + personName + R"(", "Anne"])"};

    // Строка, содержащая описание массива, конвертируется в реальный json массив
    json jDoc(json::parse(data));

    // Обращаемся к элементам массива по его месту в массиве
    string item{jDoc[2]};
    cout << "name in array: " << item << endl;
}
```

---
### `validateJson`

```c++
void validateJson() {
    string data{R"({"first": "John", "second": "Anne"})"};

    // Можно узнать, корректно ли конвертируется строка в Json объект
    if (json::accept(data)) {
        cout << "It looks valid" << endl;
    }
}
```

---
### `parseDataAsWholeWithGet`

Можно разобрать строку с массивом как единый объект

```c++
void parseDataAsWholeWithGet() {
    json jDoc(json::parse(R"([1,6,6,8])"));

    // Вариант, если хотим инициализировать переменную
    auto numbers{jDoc.get<std::vector<int>>()};
    for (auto &item : numbers) { cout << item << " "; }

    // Вариант, если у нас уже есть переменная
    std::vector<int> arr;
    jDoc.get_to(arr);
    for (auto &item : numbers) { cout << item << " "; }
}
```

---
### `parseDataAsPartsWithGet`

Можно разобрать строку по частям

```c++
void parseDataAsPartsWithGet() {
    string data{R"({
        "greeting": "Hello, World",
        "numbers": [1,2,3]
    })"};

    json jDoc(json::parse(data));

    // Метод get позволяет явно указать тип, который хотим извлечь
    auto greeting{jDoc["greeting"].get<string>()};
    auto numbers{jDoc["numbers"].get<std::vector<int>>()};

    cout << "greeting: " << greeting << endl;
    cout << "numbers: ";
    for (const auto &number : numbers) { cout << number << " "; }
}
```

---
### `parseDataToMap`

```c++
void parseDataToMap() {
    string data{R"({"name": "Roderick", "role": "Barbarian"})"};

    std::map<string, string> Map;

    json jDoc(json::parse(data));

    jDoc.get_to(Map);

    cout << Map["name"] << ": " << Map["role"] << endl;
}
```

---
### `requestGet`

Сделаем просто get request.

```c++
void requestGet() {
    cpr::Url URL{"https://www.dnd5eapi.co/api/monsters/giant-spider"};
    
    cpr::Response response{cpr::Get(URL)};
    
    // Контролируем правильность ответа
    if (response.status_code == 0) { std::cerr << response.error.message << endl; }
    
    // Можем получить информацию о заголовках
    cout << "Headers: " << endl;
    // Можем преобразовать в std::map
    // Ключи заголовков, кстати, нечувствительны к регистру
    for (const auto &[key, value] : response.header) { cout << "  - " << key << ": " << value << endl; }
    
    // Можем получить информацию об отдельном заголовке. Ключи, при этом, нечувствительны к регистру
    cout << "  - type: " << response.header["Content-Type"] << " == " << response.header["content-type"] << endl;
    
    // ---
    auto jDoc(json::parse(response.text));
    // Обратим внимание: конвертировать header не получится
    // auto result(json::parse(response.header));
    
    // Можем получить все данные по body. И распечатать как строку
    cout << "---------------------" << endl;
    cout << "Body: " << endl;
    cout << jDoc.dump(2) << endl;
    
    try {
        // Можем обратиться к конкретному свойству
        auto name{jDoc.at("name").get<string>()};
        auto desc{jDoc.at("desc").get<string>()};
        auto speed(jDoc.at("speed").at("walk").get<string>());
        cout << "name: " << name << endl;
        cout << "desc: " << desc << endl;
        cout << "speed: " << speed << endl;
    }
        catch (json::exception &e) {
        cout << e.what() << endl;
    }
}
```

Из объекта Response мы можем извлечь такую информацию как:

```text
    long status_code;               // The HTTP status code for the request
    std::string text;               // The body of the HTTP response
    Header header;                  // A map-like collection of the header fields
    Url url;                        // The effective URL of the ultimate request
    double elapsed;                 // The total time of the request in seconds
    Cookies cookies;                // A vector-like collection of cookies returned in the request
    Error error;                    // An error object containing the error code and a message
    std::string raw_header;         // The raw header string
    std::string status_line;        // The status line of the response
    std::string reason;             // The reason for the status code
    cpr_off_t uploaded_bytes;       // How many bytes have been send to the server
    cpr_off_t downloaded_bytes;     // How many bytes have been received from the server
    long redirect_count;            // How many redirects occurred
```

---
### `requestPost`

Делаем post request

```c++
void requestPost() {
    cpr::Url URL("https://www.httpbin.org/post");
    // Можем явно заголовок указать
    cpr::Header Headers{ {"content-type", "application/json"} };

    json jDoc(json::parse(R"({"cat": "meow", "dog": "bark"})"));

    // Можно сделать аналогично
    // using namespace nlohmann::literals;
    // json jDoc(R"({"cat": "meow", "dog": "bark"})"_json);

    // Поместим данные в тело запроса
    cpr::Body Body(jDoc.dump());

    // Сам Post запрос
    cpr::Response Response(cpr::Post(URL, Headers, Body));

    for (const auto &[key, value] : Response.header) {
        cout << key << " --- " << value << endl;
    }

    cout << "Body:" << endl;
    cout << Response.text << endl;
}
```

</details>

<details>
<summary><span style="color:tomato;font-size:12px">Полезные ресурсы</span></summary>

<a href="" style="margin-left:16px">https://json.nlohmann.me/integration/cmake/#supporting-both </a>

<a href="" style="margin-left:16px">https://www.studyplan.dev/pro-cpp/json </a>

</details>

</details>