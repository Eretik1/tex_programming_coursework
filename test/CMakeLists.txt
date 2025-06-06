cmake_minimum_required(VERSION 3.10.0)
project(chess_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Находим Qt6
find_package(Qt6 REQUIRED COMPONENTS Test Core5Compat)

# Добавляем тестовый исполняемый файл
add_executable(chess_tests
    test_chess.cpp
    ../game/src/chessboard.cpp
    ../pieces/src/figure.cpp
    ../pieces/src/pawn.cpp
    ../pieces/src/castle.cpp
    ../pieces/src/bishop.cpp
    ../pieces/src/knight.cpp
    ../pieces/src/queen.cpp
    ../pieces/src/king.cpp
)

# Подключаем директории
target_include_directories(chess_tests PRIVATE
    ../game/include
    ../pieces/include
)

# Подключаем библиотеки
target_link_libraries(chess_tests PRIVATE
    Qt6::Test
)

# Добавляем тест в CTest
enable_testing()
add_test(NAME chess_tests COMMAND chess_tests)