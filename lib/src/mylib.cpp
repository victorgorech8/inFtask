#include "mylib.h"
#include <algorithm>
#include <numeric>

// Функция 1: Сортировка и замена четных элементов на "КВ"
void sortAndReplace(std::vector<int>& data) {
    std::sort(data.begin(), data.end(), std::greater<int>());
    for (auto& elem : data) {
        if (elem % 2 == 0) {
            elem = -1; // Заменяем на -1 как маркер для "КВ"
        }
    }
}

// Функция 2: Сумма численных элементов
int sumOfNumbers3(const std::vector<int>& data) {
    return std::accumulate(data.begin(), data.end(), 0);
}
int sumOfNumbers(const std::vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        if (num != -1) {
            sum += num;
        }
    }
    return sum;
}
// Функция 3: Проверка длины строки
bool checkStringLength(const std::string& str) {
    return (str.size() > 2 && str.size() % 32 == 0);
}