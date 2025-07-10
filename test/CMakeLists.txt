cmake_minimum_required(VERSION 3.10.0)
project(chess_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)


find_package(Qt6 REQUIRED COMPONENTS Test Core5Compat)


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


target_include_directories(chess_tests PRIVATE
    ../game/include
    ../pieces/include
)


target_link_libraries(chess_tests PRIVATE
    Qt6::Test
)

enable_testing()
add_test(NAME chess_tests COMMAND chess_tests)