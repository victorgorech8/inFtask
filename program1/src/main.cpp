#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <sys/socket.h> // Для Linux
#include <arpa/inet.h>  // Для Linux
#include <unistd.h>     // Для Linux
#include "mylib.h"

// Общий буфер и синхронизация
std::vector<int> buffer;
std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;

// Функция для отправки данных через сокет
void sendDataToProgram2(const std::vector<int>& data) {
    // Создание сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket creation failed." << std::endl;
        return;
    }

    // Настройка адреса сервера (программа №2)
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Порт
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // localhost

    // Подключение к серверу
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Connection failed." << std::endl;
        close(sock);
        return;
    }

    // Отправка данных
    std::string dataStr;
    for (int elem : data) {
        dataStr += std::to_string(elem) + " ";
    }
    send(sock, dataStr.c_str(), dataStr.size(), 0);

    // Закрытие сокета
    close(sock);
}

// Поток 1: Ввод и обработка данных
void thread1() {
    while (true) {
        std::string input;
        std::cout << "Введите строку (только цифры, не более 64 символов): ";
        std::getline(std::cin, input);

        // Проверка ввода
        if (input.empty() || input.size() > 64 || !std::all_of(input.begin(), input.end(), ::isdigit)) {
            std::cout << "Ошибка: строка должна содержать только цифры и быть не длиннее 64 символов." << std::endl;
            continue;
        }

        // Преобразование строки в вектор чисел
        std::vector<int> data;
        for (char ch : input) {
            data.push_back(ch - '0');
        }

        // Обработка данных функцией 1
        sortAndReplace(data);

        // Помещение данных в общий буфер
        {
            std::unique_lock<std::mutex> lock(mtx);
            buffer = data;
            dataReady = true;
            cv.notify_one();
        }

        // Отправка данных в программу №2
        sendDataToProgram2(data);
    }
}

// Поток 2: Обработка и вывод данных
void thread2() {
    while (true) {
        std::vector<int> localBuffer;

        // Ожидание данных
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return dataReady; });
            localBuffer = buffer;
            dataReady = false;
        }

        // Вывод данных
        std::cout << "Обработанные данные: ";
        for (int elem : localBuffer) {
            if (elem == -1) {
                std::cout << "КВ ";
            } else {
                std::cout << elem << " ";
            }
        }
        std::cout << std::endl;

        // Передача данных в функцию 2
        int sum = sumOfNumbers(localBuffer);
        std::cout << "Сумма чисел: " << sum << std::endl;
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}