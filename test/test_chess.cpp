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
    void testCheckmate();
    void testStalemate();
    void testCastling();
    void testEnPassant();
};

void TestChess::testInitialPosition()
{
    chessboard board;
    auto& gameBoard = board.getBoard();
    
    // Проверка наличия фигур в начальной позиции
    for (int x = 0; x < 8; ++x) {
        QVERIFY(dynamic_cast<pawn*>(gameBoard[x][1].get()) != nullptr);
        QVERIFY(dynamic_cast<pawn*>(gameBoard[x][6].get()) != nullptr);
    }

}

void TestChess::testCheckDetection()
{
    chessboard board;
    
    // Очищаем доску
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    
    // Ставим черного короля и белую ладью
    board.addFigure(0, 0, std::make_unique<king>(true, 0, 0));
    board.addFigure(7, 0, std::make_unique<castle>(false, 7, 0));
    
    QVERIFY(board.isCheck(true)); // Черный король под шахом
    QVERIFY(!board.isCheck(false)); // Белый король не под шахом
}

void TestChess::testCheckmate()
{
    chessboard board;
    
    // Очищаем доску
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    
    // Классический мат двумя ладьями
    board.addFigure(0, 0, std::make_unique<king>(true, 0, 0));
    board.addFigure(0, 7, std::make_unique<castle>(false, 0, 7));
    board.addFigure(7, 7, std::make_unique<castle>(false, 7, 7));
    
    QVERIFY(board.isCheckmate(true));
    QVERIFY(board.isGameOver());
    QCOMPARE(board.getGameResult(), QString("Белые победили!"));
}

void TestChess::testStalemate()
{
    chessboard board;
    
    // Очищаем доску
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    
    // Патовая ситуация
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
    
    // Очищаем доску
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    
    // Ставим белого короля и ладью для рокировки
    board.addFigure(4, 7, std::make_unique<king>(false, 4, 7));
    board.addFigure(7, 7, std::make_unique<castle>(false, 7, 7));
    
    // Пытаемся сделать рокировку
    QVERIFY(board.moveSquare(4, 7, 6, 7));
    
    // Проверяем новые позиции короля и ладьи
    auto& gameBoard = board.getBoard();
    QVERIFY(dynamic_cast<king*>(gameBoard[6][7].get()) != nullptr);
    QVERIFY(dynamic_cast<castle*>(gameBoard[5][7].get()) != nullptr);
}

void TestChess::testEnPassant()
{
    chessboard board;
    
    // Очищаем доску
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board.addFigure(x, y, nullptr);
        }
    }
    
    // Ставим пешки для взятия на проходе
    board.addFigure(1, 4, std::make_unique<pawn>(false, 1, 4));
    board.addFigure(2, 6, std::make_unique<pawn>(true, 2, 6));
    
    // Ход черной пешки на 2 клетки
    board.moveSquare(2, 6, 2, 4);
    
    // Белая пешка берет на проходе
    QVERIFY(board.moveSquare(1, 4, 2, 5));
    
    // Проверяем, что черная пешка снята
    auto& gameBoard = board.getBoard();
    QVERIFY(gameBoard[2][4] == nullptr);
    QVERIFY(dynamic_cast<pawn*>(gameBoard[2][5].get()) != nullptr);
}


#ifdef Q_OS_WIN
    #include <windows.h>
#endif

int main(int argc, char *argv[])
{
    // Установка локали
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Для Windows: переключаем консоль в UTF-8
    #ifdef Q_OS_WIN
        SetConsoleOutputCP(CP_UTF8);
    #endif

    QCoreApplication app(argc, argv);

    // Настраиваем вывод в UTF-8 (для Qt6)
    QTextStream(stdout).setEncoding(QStringConverter::Utf8);

    TestChess tc;
    return QTest::qExec(&tc, argc, argv);
}
#include "test_chess.moc"