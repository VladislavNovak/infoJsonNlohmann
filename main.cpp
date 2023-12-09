#include <iostream>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

using std::cout;
using std::endl;
using std::string;
using json = nlohmann::json;

// Примеры создания json объекта обычным присваиванием как в JS
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

void printDoc() {
    string data{R"({"name": "Roderick", "guild": {"name": "Reds"}})"};
    json jDoc(json::parse(data));
    // Без конвертации в string можем распечатать json или целиком ...
    cout << "Entire: " << jDoc << endl;
    // ... или по частям
    cout << "Part: " << jDoc["guild"] << endl;
}

void convertJDocToString() {
    string data{R"({"name": "Roderick", "guild": {"name": "Reds"}})"};
    json jDoc(json::parse(data));

    // Метод dump позволяет конвертировать json объект снова в строку.
    // Аргументом можно задать форматирование для отступа
    string data2{jDoc.dump(2)};

    cout << data2 << endl;
}

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

void validateJson() {
    string data{R"({"first": "John", "second": "Anne"})"};

    // Можно узнать, корректно ли конвертируется строка в Json объект
    if (json::accept(data)) {
        cout << "It looks valid" << endl;
    }
}

// Можно разобрать строку с массивом как единый объект
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

// Можно разобрать строку по частям
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

void parseDataToMap() {
    string data{R"({"name": "Roderick", "role": "Barbarian"})"};

    std::map<string, string> Map;

    json jDoc(json::parse(data));

    jDoc.get_to(Map);

    cout << Map["name"] << ": " << Map["role"] << endl;
}

int main() {
    // createSimpleJDoc();
    // printDoc();
    // convertJDocToString();
    // createJsObj();
    // createJsArr();
    // validateJson();
    // parseDataAsWholeWithGet();
    // parseDataAsPartsWithGet();
    // parseDataToMap();

    return 0;
}
