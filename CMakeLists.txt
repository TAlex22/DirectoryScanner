cmake_minimum_required(VERSION 3.13)  
project(KasperskyTask)               
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-pedantic -Wall)          

set(SOURCE_FILES main.cpp Suspitions.h Scanner.h Scanner.cpp ScanReport.h ScanReport.cpp)

add_executable(scan_util ${SOURCE_FILES})
