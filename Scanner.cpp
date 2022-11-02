#include "Scanner.h"
#include "Suspitions.h"
#include "ScanReport.h"

#include <fstream>

Scanner::Scanner(std::string_view path) 
    : path_{path} {
}

void Scanner::runScan() {
    // Начало замера времени выполнения сканирования
    start_time_ = std::chrono::steady_clock::now();

    // Запускаем поиск  “подозрительного” содержимого для каждого файла в директории
    for (const auto& entry : std::filesystem::directory_iterator(path_)) {
        runFileScan(entry.path());
    }

    // Конец замера времени
    auto end = std::chrono::steady_clock::now();
    report_.addExecutionTime(end - start_time_);
}

void Scanner::runFileScan(const std::filesystem::path& path) {
    std::ifstream fin(path); 

    // Если не удалось открыть файл, увеличим счетчик ошибок
    if (!fin) {
        report_.addError();
        return;
    }

    std::string curr_line;

    // Проверка, что расширение файла - .js
    bool is_js_file = path.extension() == ".js";

    while (std::getline(fin, curr_line)) {

        // Отдельно проверим, является ли файл JS suspicious
        size_t found = curr_line.find(Suspitions::suspitions[0].suspicious_line_);
        if (found != std::string::npos && is_js_file) {
            report_.addDetectedSuspition(Suspitions::SuspicionType::JsSuspicious);
            report_.addProcessedFile();
            return;
        }

        // Проверим на все остальные типы угроз
        for (size_t i = 1; i < Suspitions::suspicions_cnt; ++i) {
            size_t found = curr_line.find(Suspitions::suspitions[i].suspicious_line_);

            if (found != std::string::npos) {
                report_.addDetectedSuspition(Suspitions::suspitions[i].type_);
                report_.addProcessedFile();
                return;
            }
        }
    }
    report_.addProcessedFile();
}

ScanReport Scanner::getScanReport() const {
    return report_;
}