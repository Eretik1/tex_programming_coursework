#include <QtTest>
#include <clocale>
#include <QCoreApplication>
#include <QStringConverter>
#include <clocale>
#include "../game/include/chessboard.h"

class TestChess : public QObject
{
    Q_OBJECT

private slots:
    void testInitialPosition();
    void testCheckDetection();
    void testStalemate();
    void testCastling();
    void testPieceCapture();
    void testMoveThroughPiece();
};

void TestChess::testInitialPosition()
{
    chessboard board;
    auto& gameBoard = board.getBoard();
    

    for (int x = 0; x < 8; ++x) {
        QVERIFY(dynamic_cast<pawn*>(gameBoard[x][1].get()) != nullptr);
        QVERIFY(dynamic_cast<pawn*>(gameBoard[x][6].get()) != nullptr);
    }

}

void TestChess::testCheckDetection()
{
    chessboard board;
    

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    

    board.addFigure(0, 0, std::make_unique<king>(true, 0, 0));
    board.addFigure(7, 0, std::make_unique<castle>(false, 7, 0));
    
    QVERIFY(board.isCheck(true));
    QVERIFY(!board.isCheck(false)); 
}

void TestChess::testStalemate()
{
    chessboard board;
    

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    

    board.addFigure(0, 0, std::make_unique<king>(true, 0, 0));
    board.addFigure(1, 2, std::make_unique<queen>(false, 1, 2));
    board.addFigure(2, 1, std::make_unique<king>(false, 2, 1));
    
    QVERIFY(board.isStalemate(true));
    QVERIFY(board.isGameOver());
    QCOMPARE(board.getGameResult(), QString("Ничья!"));
}

void TestChess::testCastling()
{
    chessboard board;
    

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    

    board.addFigure(4, 7, std::make_unique<king>(false, 4, 7));
    board.addFigure(7, 7, std::make_unique<castle>(false, 7, 7));
    

    QVERIFY(board.moveSquare(4, 7, 6, 7));

    auto& gameBoard = board.getBoard();
    QVERIFY(dynamic_cast<king*>(gameBoard[6][7].get()) != nullptr);
    QVERIFY(dynamic_cast<castle*>(gameBoard[5][7].get()) != nullptr);
}

void TestChess::testPieceCapture()
{
    chessboard board;
    

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }

    board.addFigure(0, 0, std::make_unique<castle>(false, 0, 0)); 
    board.addFigure(0, 1, std::make_unique<pawn>(true, 0, 1));    

    QVERIFY(board.moveSquare(0, 0, 0, 1));
    

    auto& gameBoard = board.getBoard();
    QVERIFY(dynamic_cast<castle*>(gameBoard[0][1].get()) != nullptr);
    QVERIFY(gameBoard[0][1]->isBlack() == false); 
}

void TestChess::testMoveThroughPiece()
{
    chessboard board;

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }

    board.addFigure(0, 0, std::make_unique<castle>(false, 0, 0)); 
    board.addFigure(0, 1, std::make_unique<pawn>(false, 0, 1));   

    QVERIFY(!board.moveSquare(0, 0, 0, 2));

    auto& gameBoard = board.getBoard();
    QVERIFY(dynamic_cast<castle*>(gameBoard[0][0].get()) != nullptr);
}


#ifdef Q_OS_WIN
    #include <windows.h>
#endif

int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "ru_RU.UTF-8");


    #ifdef Q_OS_WIN
        SetConsoleOutputCP(CP_UTF8);
    #endif

    QCoreApplication app(argc, argv);

    QTextStream(stdout).setEncoding(QStringConverter::Utf8);

    TestChess tc;
    return QTest::qExec(&tc, argc, argv);
}
#include "test_chess.moc"