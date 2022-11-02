#pragma once

#include "ScanReport.h"

#include <filesystem>
#include <chrono>

// Класс, представляющий объект, проводящий поиск подозрительных файлов в указанной директории 
class Scanner {
public:
    Scanner(std::string_view path);

    // Метод, запускающий сканирование 
    void runScan();

    // Метод, возвращающий отчет о сканировании
    ScanReport getScanReport() const;

private:
    // Закрытый метод, проводяющий поиск “подозрительного” содержимого в переданном файле
    void runFileScan(const std::filesystem::path& path); 

    std::string_view path_;
    ScanReport report_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};