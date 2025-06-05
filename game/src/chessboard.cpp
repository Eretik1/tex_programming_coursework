#include "../include/chessboard.h"
#include <random>
#include <algorithm>

chessboard::chessboard() {
    board.resize(8);
    for (auto& row : board) {
        row.resize(8);
    }
    setupInitialPosition();
}

const std::vector<std::vector<std::unique_ptr<figure>>>& chessboard::getBoard() const {
    return board;
}

bool chessboard::isBlackTurn() const {
    return blackTurn;
}

void chessboard::switchTurn() {
    blackTurn = !blackTurn;
}

bool chessboard::isValidPosition(int x, int y) const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void chessboard::addFigure(int X, int Y, std::unique_ptr<figure> fig) {
    if (isValidPosition(X, Y)) {
        board[X][Y] = std::move(fig);
    }
}

bool chessboard::isSquareUnderAttack(int x, int y, bool byBlack) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->isBlack() == byBlack) {
                if (board[i][j]->move(x, y, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool chessboard::isCheck(bool forBlack) const {
    auto kingPos = findKing(forBlack);
    return isSquareUnderAttack(kingPos.first, kingPos.second, !forBlack);
}

bool chessboard::hasLegalMoves(bool forBlack) {
    for (int x1 = 0; x1 < 8; ++x1) {
        for (int y1 = 0; y1 < 8; ++y1) {
            if (board[x1][y1] && board[x1][y1]->isBlack() == forBlack) {
                std::vector<std::pair<int, int>> possibleMoves;
                for (int x2 = 0; x2 < 8; ++x2) {
                    for (int y2 = 0; y2 < 8; ++y2) {
                        if (board[x1][y1]->move(x2, y2, board)) {
                            possibleMoves.emplace_back(x2, y2);
                        }
                    }
                }

                for (const auto& move : possibleMoves) {
                    int x2 = move.first;
                    int y2 = move.second;
                    
                    auto original = std::move(board[x2][y2]);
                    auto moving = std::move(board[x1][y1]);
                    
                    board[x2][y2] = std::move(moving);
                    board[x2][y2]->setPosition(x2, y2);
                    
                    bool inCheck = isCheck(forBlack);
                    
                    board[x1][y1] = std::move(board[x2][y2]);
                    board[x1][y1]->setPosition(x1, y1);
                    board[x2][y2] = std::move(original);
                    
                    if (!inCheck) {
                        return true; 
                    }
                }
            }
        }
    }
    return false; 
}

bool chessboard::isCheckmate(bool forBlack) {
    bool checkmate = isCheck(forBlack) && !hasLegalMoves(forBlack);
    if (checkmate) {
        gameOver = true;
        gameResult = forBlack ? "Белые победили!" : "Черные победили!";
    }
    return checkmate;
}

bool chessboard::isStalemate(bool forBlack) {

    return !isCheck(forBlack) && !hasLegalMoves(forBlack);
}

bool chessboard::canCastle(int x1, int y1, int x2, int y2) const {
    auto* kingPtr = dynamic_cast<king*>(board[x1][y1].get());
    if (!kingPtr || kingPtr->hasMoved()) return false;
    
    int direction = (x2 > x1) ? 1 : -1;
    int rookX = (direction > 0) ? 7 : 0;
    
    if (!board[rookX][y1] || !dynamic_cast<castle*>(board[rookX][y1].get())) 
        return false;
    
    auto* rookPtr = dynamic_cast<castle*>(board[rookX][y1].get());
    if (rookPtr->hasMoved() || rookPtr->isBlack() != kingPtr->isBlack())
        return false;
    

    for (int x = x1 + direction; x != rookX; x += direction) {
        if (board[x][y1] != nullptr) return false;
    }
    

    if (isSquareUnderAttack(x1, y1, !board[x1][y1]->isBlack()))
        return false;
        
    for (int x = x1; x != x2 + direction; x += direction) {
        if (isSquareUnderAttack(x, y1, !board[x1][y1]->isBlack()))
            return false;
    }
    
    return true;
}

void chessboard::setupFisherRandomRow(std::mt19937& gen, bool isWhite, int row) {

    for (int x = 0; x < 8; ++x) {
        board[x][row] = nullptr;
    }
    

    addFigure(0, row, std::make_unique<castle>(isWhite, 0, row));
    addFigure(7, row, std::make_unique<castle>(isWhite, 7, row));

    enum PieceType { QUEEN, KNIGHT, BISHOP };
    std::vector<PieceType> middlePieces = {QUEEN, KNIGHT, BISHOP, KNIGHT, BISHOP};
    std::shuffle(middlePieces.begin(), middlePieces.end(), gen);
    
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
    
    for (int x = 1; x < 7; ++x) {
        if (!board[x][row]) {
            addFigure(x, row, std::make_unique<king>(isWhite, x, row));
            break;
        }
    }
    
    bool lightBishop = false, darkBishop = false;
    for (int x = 0; x < 8; ++x) {
        if (auto* b = dynamic_cast<bishop*>(board[x][row].get())) {
            if ((x + row) % 2 == 0) darkBishop = true;
            else lightBishop = true;
        }
    }
    
    if (!(lightBishop && darkBishop)) {
        setupFisherRandomRow(gen, isWhite, row);
    }
}

void chessboard::setupMirroredRow(bool isWhite, int row) {

    for (int x = 0; x < 8; ++x) {
        board[x][row] = nullptr;
    }
    

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

void chessboard::setupInitialPosition() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    

    setupFisherRandomRow(gen, true, 7);  
    setupMirroredRow(false, 0);          
    
    for (int x = 0; x < 8; ++x) {
        addFigure(x, 1, std::make_unique<pawn>(false, x, 1)); 
        addFigure(x, 6, std::make_unique<pawn>(true, x, 6));  
    }
}

bool chessboard::moveSquare(int x1, int y1, int x2, int y2) {
    if (gameOver) {
        std::cout << "Игра окончена. " << gameResult << std::endl;
        return false;
    }

    if (!isValidPosition(x1, y1) || !isValidPosition(x2, y2)) {
        std::cout << "Invalid coordinates!" << std::endl;
        return false;
    }

    if (!board[x1][y1] || board[x1][y1]->isBlack() != blackTurn) {
        std::cout << "Not your turn or empty cell!" << std::endl;
        return false;
    }


    if (auto* kingPtr = dynamic_cast<king*>(board[x1][y1].get())) {
        if (abs(x2 - x1) == 2 && y1 == y2) {
            if (canCastle(x1, y1, x2, y2)) {
                int direction = (x2 > x1) ? 1 : -1;
                int rookX = (direction > 0) ? 7 : 0;
                int newRookX = x1 + direction;
                
                board[newRookX][y1] = std::move(board[rookX][y1]);
                board[newRookX][y1]->setPosition(newRookX, y1);
                if (auto* rookPtr = dynamic_cast<castle*>(board[newRookX][y1].get())) {
                    rookPtr->setMoved(true);
                }
                
                board[x2][y2] = std::move(board[x1][y1]);
                board[x2][y2]->setPosition(x2, y2);
                kingPtr->setMoved(true);
                
                switchTurn();
                enPassantTarget = {-1, -1};
                return false; 
            }
        }
    }

    if (auto* pawnPtr = dynamic_cast<pawn*>(board[x1][y1].get())) {
        if (enPassantTarget.first == x2 && enPassantTarget.second == y2 && 
            abs(x2 - x1) == 1 && (blackTurn ? y2 == y1 - 1 : y2 == y1 + 1)) {
            board[x2][blackTurn ? y2 + 1 : y2 - 1] = nullptr;
        }
        
        if (abs(y2 - y1) == 2) {
            enPassantTarget = {x2, (y1 + y2) / 2};
        } else {
            enPassantTarget = {-1, -1};
        }
    } else {
        enPassantTarget = {-1, -1};
    }

    if (board[x1][y1]->move(x2, y2, board)) {
        auto temp = std::move(board[x2][y2]);
        board[x2][y2] = std::move(board[x1][y1]);
        bool inCheck = isCheck(blackTurn);
        
        if (inCheck) {
            board[x1][y1] = std::move(board[x2][y2]);
            board[x2][y2] = std::move(temp);
            std::cout << "Invalid move - king would be in check!" << std::endl;
            return false;
        }
        
        board[x2][y2]->setPosition(x2, y2);

        if (auto* pawnPtr = dynamic_cast<pawn*>(board[x2][y2].get())) {
            if ((blackTurn && y2 == 7) || (!blackTurn && y2 == 0)) {
                board[x2][y2] = std::make_unique<queen>(blackTurn, x2, y2);
            }
        }

        if (auto* kingPtr = dynamic_cast<king*>(board[x2][y2].get())) {
            kingPtr->setMoved(true);
        }
        if (auto* rookPtr = dynamic_cast<castle*>(board[x2][y2].get())) {
            rookPtr->setMoved(true);
        }
        isCheckmate(!blackTurn);
        switchTurn();
        return true;
    } else {
        std::cout << "Invalid move!" << std::endl;
        return false;
    }
}

bool chessboard::isKingInCheck(bool isBlack) const {
    auto kingPos = findKing(isBlack);
    return isSquareUnderAttack(kingPos.first, kingPos.second, !isBlack);
}

std::pair<int, int> chessboard::findKing(bool isBlack) const {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (board[x][y] && dynamic_cast<king*>(board[x][y].get()) && 
                board[x][y]->isBlack() == isBlack) {
                return {x, y};
            }
        }
    }
    return {-1, -1}; 
}

bool chessboard::isGameOver() const {
    return gameOver;
}

std::string chessboard::getGameResult() const {
    return gameResult;
}

