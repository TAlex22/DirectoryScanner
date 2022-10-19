#pragma once

#include "Suspitions.h"

#include <filesystem>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>


// Класс, представляющий отчет о сканировании 
class ScanReport {
public:
    void addDetectedSuspition(Suspitions::SuspicionType type) {
        ++detected_suspicions_[static_cast<size_t>(type)];
    }

    void addError() {
        ++errors_;
    }

    void addProcessedFile() {
        ++processed_files_;
    }

    void addExecutionTime(const std::chrono::duration<double>& time) {
        exec_time_ = time;
    }

    size_t getProcessedFiles() const {
        return processed_files_;
    }

    size_t getErrors() const {
        return errors_;
    }

    auto getDetectedSuspitions() const {
        return detected_suspicions_;
    }

    auto getExecutionTime() const {
        return exec_time_;
    }

    void print(std::ostream& out) const {
        out << "====== Scan result ======" << std::endl;
        out << "Processed files: " << processed_files_ << std::endl;

        for (size_t i = 0; i < Suspitions::suspicions_cnt; ++i) {
            out << Suspitions::suspitions[i].name_ << " detects: " << detected_suspicions_[i] << std::endl;
        }

        out << "Errors: " << errors_ << std::endl;
        auto as_sec = std::chrono::duration_cast<std::chrono::seconds>(exec_time_).count();
        auto seconds = as_sec % 60;
        auto minutes = (as_sec / 60) % 60;
        auto hours = (as_sec / 60) / 60;
        out << "Execution time: " << std::setfill('0') << std::setw(2) << hours << ":" 
            << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') 
            << std::setw(2) << seconds  << std::endl;
        out << "=========================" << std::endl;
    }

private:
    size_t processed_files_{0};
    size_t errors_{0};
    std::array<size_t, Suspitions::suspicions_cnt> detected_suspicions_{0};
    std::chrono::duration<double> exec_time_;
};


// Класс, представляющий объект, проводящий поиск подозрительных файлов в указанной директории 
class Scanner {
public:
    Scanner(std::string_view path) 
        : path_{path} {
    }

    // Метод, запускающий сканирование 
    void runScan();

    // Метод, возвращающий отчет о сканировании
    ScanReport getScanReport() const;

private:

    // Закрытый метод проводяющий поиск “подозрительного” содержимого в указанном файле
    void runFileScan(const std::filesystem::path& path); 

    std::string_view path_;
    ScanReport report_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};