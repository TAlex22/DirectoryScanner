#pragma once

#include <string_view>
#include <array>

// Данный файл был создан для возможности расширения множества ивестных угроз
// Он позволяет добавлять новые угрозы без надобности изменения остальных файлов

namespace Suspitions {

// перечисление типов угроз
enum class SuspicionType {
    JsSuspicious  ,
    UnixSuspicious,
    MacOsSuspicious
};

// структура для удобного хранения угроз (тип угрозы; название угрозы; строка, определяющая тип угрозы)
struct Suspicion {

    constexpr Suspicion(const SuspicionType type, std::string_view name, std::string_view line) 
        : type_{type}, name_{name}, suspicious_line_{line} {
    }

    const SuspicionType type_;
    const std::string_view name_;
    const std::string_view suspicious_line_;
}; 

// константа времени компиляции, храняющая количество угроз
constexpr size_t suspicions_cnt{3};

// массив, хранящий все угрозы
constexpr std::array<Suspicion, suspicions_cnt> suspitions {
    Suspicion{ SuspicionType::JsSuspicious, "JS", "<script>evil_script()</script>" }, 
    Suspicion{ SuspicionType::UnixSuspicious, "Unix", "rm -rf ~/Documents" }, 
    Suspicion{ SuspicionType::MacOsSuspicious, "macOS", "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")" }
};

} // Suspitions