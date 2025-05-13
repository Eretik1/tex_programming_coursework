#include "../include/chessboard.h"

chessboard::chessboard() {
    board.resize(8);
    for (auto& row : board) {
        row.resize(8);
    }
    setupInitialPosition();
}

void chessboard::setupInitialPosition() {
    // Создаем случайный генератор
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    
    // Генерируем случайную расстановку для белых
    setupFisherRandomRow(gen, true, 7);
    
    // Создаем зеркальную расстановку для черных
    setupMirroredRow(false, 0);
    
    // Расставляем пешки
    for (int x = 0; x < 8; ++x) {
        addFigure(x, 1, std::make_unique<pawn>(false, x, 1)); // Черные пешки
        addFigure(x, 6, std::make_unique<pawn>(true, x, 6));  // Белые пешки
    }
}

void chessboard::setupFisherRandomRow(std::mt19937& gen, bool isWhite, int row) {
    // Очищаем ряд перед заполнением
    for (int x = 0; x < 8; ++x) {
        board[x][row] = nullptr;
    }

    // Ладьи по углам
    addFigure(0, row, std::make_unique<castle>(isWhite, 0, row));
    addFigure(7, row, std::make_unique<castle>(isWhite, 7, row));

    // Создаем вектор с типами фигур для середины: ферзь, 2 коня, 2 слона
    enum PieceType { QUEEN, KNIGHT, BISHOP };
    std::vector<PieceType> middlePieces = {QUEEN, KNIGHT, BISHOP, KNIGHT, BISHOP};

    // Перемешиваем средние фигуры
    std::shuffle(middlePieces.begin(), middlePieces.end(), gen);

    // Расставляем перемешанные фигуры (позиции 1-5)
    for (int i = 0; i < 5; ++i) {
        int x = i + 1;
        switch (middlePieces[i]) {
            case QUEEN:  
                addFigure(x, row, std::make_unique<queen>(isWhite, x, row)); 
                break;
            case KNIGHT: 
                addFigure(x, row, std::make_unique<knight>(isWhite, x, row)); 
                break;
            case BISHOP: 
                addFigure(x, row, std::make_unique<bishop>(isWhite, x, row)); 
                break;
        }
    }

    // Добавляем короля на оставшуюся позицию (6)
    // Находим пустую клетку между ладьями
    for (int x = 1; x < 7; ++x) {
        if (!board[x][row]) {
            addFigure(x, row, std::make_unique<king>(isWhite, x, row));
            break;
        }
    }

    // Проверяем цвет слонов
    bool lightBishop = false, darkBishop = false;
    for (int x = 0; x < 8; ++x) {
        if (auto* b = dynamic_cast<bishop*>(board[x][row].get())) {
            if ((x + row) % 2 == 0) darkBishop = true;
            else lightBishop = true;
        }
    }

    // Если слоны одного цвета, перегенерируем
    if (!(lightBishop && darkBishop)) {
        setupFisherRandomRow(gen, isWhite, row);
    }
}

void chessboard::setupMirroredRow(bool isWhite, int row) {
    // Очищаем ряд перед заполнением
    for (int x = 0; x < 8; ++x) {
        board[x][row] = nullptr;
    }

    // Зеркально копируем фигуры из противоположного ряда
    int sourceRow = (row == 0) ? 7 : 0;
    for (int x = 0; x < 8; ++x) {
        int mirroredX = 7 - x;
        if (!board[x][sourceRow]) continue;

        if (dynamic_cast<castle*>(board[x][sourceRow].get())) {
            addFigure(mirroredX, row, std::make_unique<castle>(isWhite, mirroredX, row));
        }
        else if (dynamic_cast<knight*>(board[x][sourceRow].get())) {
            addFigure(mirroredX, row, std::make_unique<knight>(isWhite, mirroredX, row));
        }
        else if (dynamic_cast<bishop*>(board[x][sourceRow].get())) {
            addFigure(mirroredX, row, std::make_unique<bishop>(isWhite, mirroredX, row));
        }
        else if (dynamic_cast<queen*>(board[x][sourceRow].get())) {
            addFigure(mirroredX, row, std::make_unique<queen>(isWhite, mirroredX, row));
        }
        else if (dynamic_cast<king*>(board[x][sourceRow].get())) {
            addFigure(mirroredX, row, std::make_unique<king>(isWhite, mirroredX, row));
        }
    }
}

const std::vector<std::vector<std::unique_ptr<figure>>>& chessboard::getBoard() const {
    return board;
}

void chessboard::addFigure(int X, int Y, std::unique_ptr<figure> fig) {
    if (X >= 0 && X < 8 && Y >= 0 && Y < 8) {
        board[X][Y] = std::move(fig);
    }
}

void chessboard::moveSquare(int x1, int y1, int x2, int y2) {
    if (!board[x1][y1] || board[x1][y1]->isBlack() != blackTurn) {
        std::cout << "Not your turn or empty cell!" << std::endl;
        return;
    }

    if (board[x1][y1]->move(x2, y2, board)) {
        addFigure(x2, y2, std::move(board[x1][y1]));
        board[x2][y2]->setPosition(x2, y2);
        board[x1][y1] = nullptr;
        switchTurn();
    } else {
        std::cout << "Invalid move!" << std::endl;
    }
}

bool chessboard::isBlackTurn() const {
    return blackTurn;
}

void chessboard::switchTurn() {
    blackTurn = !blackTurn;
}