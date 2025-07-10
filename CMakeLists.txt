cmake_minimum_required(VERSION 3.10.0)
project(coursework VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network)

qt_add_resources(QRC_FILES 
    interface/styles/styles.qrc
)

set(SOURCE_FILES
    pieces/src/figure.cpp
    pieces/src/pawn.cpp
    pieces/src/castle.cpp
    pieces/src/bishop.cpp
    pieces/src/knight.cpp
    pieces/src/queen.cpp
    pieces/src/king.cpp
    game/src/chessboard.cpp
    Interface/src/ChessWidget.cpp
    Interface/src/MainMenu.cpp
    Interface/src/ColorSelectionMenu.cpp
    Interface/src/MainWindow.cpp

    interface/src/IpInputMenu.cpp
    interface/include/IpInputMenu.h  
    interface/src/IntermediateMenu.cpp
    interface/include/IntermediateMenu.h  

    network_game/src/GameClient.cpp
    network_game/include/GameClient.h  
    network_game/src/GameServer.cpp
    network_game/include/GameServer.h

    main.cpp
)


qt_add_resources(RESOURCE_FILES
    Interface/resources/chess_resources.qrc
)


qt_generate_moc(
    Interface/include/ChessWidget.h
    ${CMAKE_CURRENT_BINARY_DIR}/moc_ChessWidget.cpp
)

qt_generate_moc(
    Interface/include/MainMenu.h
    ${CMAKE_CURRENT_BINARY_DIR}/moc_MainMenu.cpp
)

qt_generate_moc(
    Interface/include/ColorSelectionMenu.h
    ${CMAKE_CURRENT_BINARY_DIR}/moc_ColorSelectionMenu.cpp
)

qt_generate_moc(
    Interface/include/MainWindow.h
    ${CMAKE_CURRENT_BINARY_DIR}/moc_MainWindow.cpp
)

qt_generate_moc(
    Interface/include/IntermediateMenu.h
    ${CMAKE_CURRENT_BINARY_DIR}/moc_IntermediateMenu.cpp
)

qt_generate_moc(
    Interface/include/IpInputMenu.h
    ${CMAKE_CURRENT_BINARY_DIR}/moc_IpInputMenu.cpp
)

add_executable(coursework 
    ${SOURCE_FILES} 
    ${RESOURCE_FILES}
    ${QRC_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}/moc_ChessWidget.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/moc_MainMenu.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/moc_ColorSelectionMenu.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/moc_MainWindow.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/moc_IntermediateMenu.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/moc_IpInputMenu.cpp
)

target_include_directories(coursework PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Interface/include
    ${CMAKE_CURRENT_SOURCE_DIR}/network_game/include
    ${CMAKE_CURRENT_BINARY_DIR}  
)

target_link_libraries(coursework PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Network
)


add_custom_command(TARGET coursework POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/img
    ${CMAKE_CURRENT_BINARY_DIR}/img
)