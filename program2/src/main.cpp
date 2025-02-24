#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h> // Для Linux
#include <arpa/inet.h>  // Для Linux
#include <unistd.h>     // Для Linux
#include "mylib.h"

// Функция для приёма данных через сокет
void receiveDataFromProgram1() {
    // Создание сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket creation failed." << std::endl;
        return;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Порт
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Привязка сокета
    if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Bind failed." << std::endl;
        close(sock);
        return;
    }

    // Ожидание подключения
    if (listen(sock, 5) == -1) { // Очередь из 5 подключений
        std::cerr << "Listen failed." << std::endl;
        close(sock);
        return;
    }

    std::cout << "Ожидание подключения программы №1..." << std::endl;

    while (true) {
        // Принятие подключения
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSock = accept(sock, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSock == -1) {
            std::cerr << "Accept failed." << std::endl;
            continue; // Продолжаем ожидать новые подключения
        }

        std::cout << "Программа №1 подключена." << std::endl;

        // Приём данных
        char buffer[1024];
        while (true) {
            int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) {
                std::cerr << "Connection closed." << std::endl;
                break; // Выход из цикла приёма данных
            }

            buffer[bytesReceived] = '\0';
            std::string dataStr(buffer);

            // Преобразование строки в вектор чисел
            std::vector<int> data;
            size_t pos = 0;
            while ((pos = dataStr.find(' ')) != std::string::npos) {
                std::string token = dataStr.substr(0, pos);
                if (!token.empty()) {
                    data.push_back(std::stoi(token));
                }
                dataStr.erase(0, pos + 1);
            }

            // Обработка данных
            std::cout << "Программа №2: Получены данные: ";
            for (int elem : data) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;

            // Проверка данных с помощью функции 3
            std::string str;
            for (int elem : data) {
                // Добавляем только положительные числа или цифры в строку
                if (elem >= 0) {
                    str += std::to_string(elem);
                } else {
                    // Для отрицательных чисел добавляем только цифры
                    str += std::to_string(-elem); // Добавляем только модуль числа
                }
            }
            if (checkStringLength(str)) {
             
                std::cout << "Программа №2: Данные соответствуют требованиям." << std::endl;
            } else {
                
                std::cout << "Программа №2: Ошибка: данные не соответствуют требованиям." << std::endl;
            }
        }

        // Закрытие сокета клиента
        close(clientSock);
        std::cout << "Ожидание нового подключения..." << std::endl;
    }

    // Закрытие серверного сокета (эта строка никогда не выполнится в текущей реализации)
    close(sock);
}

int main() {
    receiveDataFromProgram1();
    return 0;
}