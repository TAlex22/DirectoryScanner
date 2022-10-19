#include "Scanner.h"

#include <iostream>
#include <ctime>

int main(int argc, char* argv[]) {

    // Проверка, что утилита была вызвана корректно
    if (argc != 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        std::exit(-1);
    }

    try {

        // Пробуем запустить сканирование в переданной директории и вывести отчет в стандартный поток вывода
        Scanner scanner(argv[1]);
        scanner.runScan();
        auto report = scanner.getScanReport();
        report.print(std::cout);
        
    } // В случае возниконовения ошибки, выведем ее в стандартный поток ошибок и завершим работу программы
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::exit(-1);
    }
    return 0;
}