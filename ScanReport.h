#pragma once

#include "Suspitions.h"

#include <iostream>
#include <chrono>

// Класс, представляющий отчет о сканировании 
class ScanReport {
public:
    void addDetectedSuspition(Suspitions::SuspicionType type);

    void addError();

    void addProcessedFile();

    void addExecutionTime(const std::chrono::duration<double>& time);

    size_t getProcessedFiles() const;

    size_t getErrors() const;

    auto getDetectedSuspitions() const;

    auto getExecutionTime() const;

    void print(std::ostream& out = std::cout) const;

private:
    size_t processed_files_{0};
    size_t errors_{0};
    std::array<size_t, Suspitions::suspicions_cnt> detected_suspicions_{0};
    std::chrono::duration<double> exec_time_;
};