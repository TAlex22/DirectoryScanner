#include "ScanReport.h"

#include <iomanip>

void ScanReport::addDetectedSuspition(Suspitions::SuspicionType type) {
        ++detected_suspicions_[static_cast<size_t>(type)];
    }

    void ScanReport::addError() {
        ++errors_;
    }

    void ScanReport::addProcessedFile() {
        ++processed_files_;
    }

    void ScanReport::addExecutionTime(const std::chrono::duration<double>& time) {
        exec_time_ = time;
    }

    size_t ScanReport::getProcessedFiles() const {
        return processed_files_;
    }

    size_t ScanReport::getErrors() const {
        return errors_;
    }

    auto ScanReport::getDetectedSuspitions() const {
        return detected_suspicions_;
    }

    auto ScanReport::getExecutionTime() const {
        return exec_time_;
    }

    void ScanReport::print(std::ostream& out) const {
        auto as_sec = std::chrono::duration_cast<std::chrono::seconds>(exec_time_).count();
        auto seconds = as_sec % 60;
        auto minutes = (as_sec / 60) % 60;
        auto hours = (as_sec / 60) / 60;

        out << "====== Scan result ======" << std::endl;
        out << "Processed files: " << processed_files_ << std::endl;

        for (size_t i = 0; i < Suspitions::suspicions_cnt; ++i) {
            out << Suspitions::suspitions[i].name_ << " detects: " << detected_suspicions_[i] << std::endl;
        }

        out << "Errors: " << errors_ << std::endl;
        out << "Execution time: " << std::setfill('0') << std::setw(2) << hours << ":" 
            << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') 
            << std::setw(2) << seconds  << std::endl;
        out << "=========================" << std::endl;
    }