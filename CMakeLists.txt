cmake_minimum_required(VERSION 3.10)
project(BankTellerQueue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES 
    "src/*.cpp"
)

add_executable(bank_teller ${SOURCES} main.cpp)

target_compile_definitions(bank_teller PRIVATE _CRT_SECURE_NO_WARNINGS)
