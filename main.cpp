#include <iostream>
#include <QApplication>
#include "./pieces/include/figure.h"
#include "./pieces/include/pawn.h"
#include "./pieces/include/castle.h"
#include "./pieces/include/bishop.h"
#include "./pieces/include/knight.h"
#include "./pieces/include/queen.h"
#include "./pieces/include/king.h"
#include "./Interface/include/MainWindow.h"
#include "./game/include/chessboard.h"

int main(int argc, char *argv[])
{
    //*/
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(800, 650);
    w.show();
    return a.exec();
    /*/
   /*
   chessboard board;
   std::cout << (board.getBoard()[3][2] == nullptr) << std::endl;
   std::unique_ptr<figure> fig {new knight(1, 3, 2)};
   board.addFigure(3, 2, std::move(fig));
   std::cout << (board.getBoard()[3][2] == nullptr) << std::endl;
   board.moveSquare(3, 2, 2, 3);
   std::cout << (board.getBoard()[3][2] == nullptr) << std::endl;
   std::cout << (board.getBoard()[2][3] == nullptr) << std::endl;
   */
} 