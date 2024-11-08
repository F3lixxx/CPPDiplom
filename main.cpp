#include <boost/locale.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include "http_connection.h"
#include "link.h"

int main() {
    // Инициализация локали
    boost::locale::generator gen;
    std::locale loc = gen("en_US.UTF-8");
    boost::locale::generator::global(loc);

    // Исходный текст
    std::string text = "Hello, World! This is a test. Hello again!";
    
    // Нормализация текста
    std::string normalized_text = boost::locale::to_lower(text, loc);
    
    // Индексация текста
    std::unordered_map<std::string, int> index;
    std::istringstream iss(normalized_text);
    std::string word;
    while (iss >> word) {
        // Удаление знаков препинания
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        index[word]++;
    }

    // Вывод индекса
    for (const auto& pair : index) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}