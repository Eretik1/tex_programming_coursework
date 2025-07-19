
#include "..\\include\\ChessWidget.h"
#include <QFileInfo>  
#include <QPainter>
#include <QPixmap>
#include <QVBoxLayout> 

const int BOARD_SIZE = 480;
const int CELL_SIZE = BOARD_SIZE / 8;
const int MARGIN = 30;
const int BUTTON_HEIGHT = 50;

ChessWidget::ChessWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(BOARD_SIZE + 2*MARGIN, BOARD_SIZE + 2*MARGIN + 80); 
    loadPieceImages();
    setupUi();
}

void ChessWidget::setupUi() {
   
    m_endGameButton = new QPushButton("Завершить игру", this);
    m_endGameButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4a4a4a;"
        "    color: white;"
        "    border: none;"
        "    padding: 15px 32px;"
        "    text-align: center;"
        "    text-decoration: none;"
        "    font-size: 16px;"
        "    margin: 4px 2px;"
        "    border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5a5a5a;"
        "}"
    );
    
   
    connect(m_endGameButton, &QPushButton::clicked, this, &ChessWidget::gameEndRequested);
}


void ChessWidget::setChessboard(chessboard* board) {
    m_board = board;
    update();
}

void ChessWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    
    m_boardRect = QRect(
        (width() - BOARD_SIZE) / 2,
        MARGIN,
        BOARD_SIZE,
        BOARD_SIZE
    );
    
    
    m_statusRect = QRect(
        m_boardRect.left(),
        m_boardRect.bottom() + 10,
        BOARD_SIZE,
        30
    );
    
   
    m_buttonRect = QRect(
        (width() - 200) / 2,  
        m_statusRect.bottom() + 20,
        200,
        50
    );
    
   
    if (m_endGameButton) {
        m_endGameButton->setGeometry(m_buttonRect);
    }
    
    
    painter.translate(m_boardRect.topLeft());
    drawChessboard(painter);
    drawSelection(painter);
    drawKingHighlight(painter);
    drawPieces(painter);
    painter.resetTransform();
    

    drawCoordinates(painter);
}

void ChessWidget::drawChessboard(QPainter& painter) {
    const QColor light(240, 217, 181);
    const QColor dark(181, 136, 99);
    
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            painter.fillRect(cellRect(x, y), (x + y) % 2 ? dark : light);
        }
    }
}

void ChessWidget::loadPieceImages() {
    QStringList pieces = {"pawn", "castle", "knight", "bishop", "queen", "king"};
    QStringList colors = {"W", "B"};

    for (const QString& piece : pieces) {
        for (const QString& color : colors) {
            QString key = piece + color;
            QString path = QString(":/img/%1%2.png").arg(piece).arg(color);
            if (QPixmap pixmap(path); !pixmap.isNull()) {
                pieceImages[key] = pixmap.scaled(CELL_SIZE, CELL_SIZE, 
                                              Qt::KeepAspectRatio, 
                                              Qt::SmoothTransformation);
            } else {
                qWarning() << "Failed to load image:" << path;
                
                pieceImages[key] = QPixmap(CELL_SIZE, CELL_SIZE);
                pieceImages[key].fill(Qt::transparent);
                QPainter p(&pieceImages[key]);
                p.setFont(QFont("Arial", CELL_SIZE/2));
                p.drawText(QRect(0, 0, CELL_SIZE, CELL_SIZE), Qt::AlignCenter, 
                          color == "W" ? "♙♖♘♗♕♔" : "♟♜♞♝♛♚");
            }
        }
    }
}

void ChessWidget::drawPieces(QPainter& painter) {
    if (!m_board || m_board->isGameOver()) return;
    
    const auto& board = m_board->getBoard();
    
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[x][y]) {
                QRect rect = cellRect(x, y);
                std::string imagePath = board[x][y]->getImagePath(); 
                
                QString key = QString::fromStdString(imagePath).remove(":/img/").remove(".png");
                if (pieceImages.contains(key)) {
                    painter.drawPixmap(rect, pieceImages[key]);
                } else {
                    
                    painter.setFont(QFont("Arial", m_cellSize.width()/2));
                    painter.drawText(rect, Qt::AlignCenter, 
                        board[x][y]->isBlack() ? "♞" : "♘");
                    qWarning() << "Image not found in cache:" << QString::fromStdString(imagePath);
                }
            }
        }
    }
}

void ChessWidget::drawSelection(QPainter& painter) {
    if (m_selectedX >= 0 && m_selectedY >= 0) {
        
        painter.setPen(QPen(QColor(100, 100, 100, 150), 3));
        painter.drawRect(cellRect(m_selectedX, m_selectedY));
        
        
        painter.fillRect(cellRect(m_selectedX, m_selectedY), 
                       QColor(200, 200, 200, 50));
    }
}

void ChessWidget::drawCoordinates(QPainter& painter) {
    

    QString statusText;
    if (m_board->isGameOver()) {
        statusText = QString::fromStdString(m_board->getGameResult());
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.setPen(Qt::red);
    }  
    else if (m_board->isCheckmate(false)) {
        statusText = "Мат белому королю!";
    } 
    else if (m_board->isCheckmate(true)) {
        statusText = "Мат черному королю!";
    }
    else if (m_board->isCheck(false)) {
        statusText = "Шах белому королю!";
    } 
    else if (m_board->isCheck(true)) {
        statusText = "Шах черному королю!";
    } 
    else {
        statusText = m_board->isBlackTurn() ? "Ход черных" : "Ход белых";
    }
    
    
    painter.setFont(QFont("Arial", 12));
    painter.setPen(Qt::black);
    painter.drawText(m_statusRect, Qt::AlignCenter, statusText);
}

QRect ChessWidget::cellRect(int x, int y) const {
    return QRect(
        x * CELL_SIZE,
        (7 - y) * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE
    );
}

void ChessWidget::mousePressEvent(QMouseEvent* event) {
    if (!m_board || !m_board->getBoard().size() || event->button() != Qt::LeftButton || m_board->isGameOver()) {
        return; 
    }

    if (!m_board || event->button() != Qt::LeftButton || m_board->isGameOver()) {
        return; 
    }

    if (!m_board || event->button() != Qt::LeftButton) 
        return;
    
    QPoint pos = event->pos() - m_boardRect.topLeft();
    
    if (m_boardRect.contains(event->pos())) {
        int x = pos.x() / CELL_SIZE;
        int y = 7 - (pos.y() / CELL_SIZE);  
        
        qDebug() << "Clicked at:" << x << y;
        
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            auto& board = m_board->getBoard();
            
            if (m_selectedX >= 0 && m_selectedY >= 0) {
                qDebug() << "Trying to move from" << m_selectedX << m_selectedY << "to" << x << y;
                
                
                if (board[m_selectedX][m_selectedY] && 
                    board[m_selectedX][m_selectedY]->isBlack() == m_board->isBlackTurn()) {
                    
                    
                    if (board[m_selectedX][m_selectedY]->move(x, y, board)) {
                        m_board->moveSquare(m_selectedX, m_selectedY, x, y);
                        qDebug() << "Move successful!";
                        QString massege = createMoveString(m_selectedX, m_selectedY, x, y);
                        emit move(massege);
                    } else {
                        qDebug() << "Invalid move!";
                    }
                } else {
                    qDebug() << "Not your piece or empty cell!";
                }
                
                
                m_selectedX = -1;
                m_selectedY = -1;
            } 
            
            else {
                if (board[x][y] && board[x][y]->isBlack() == m_board->isBlackTurn()) {
                    m_selectedX = x;
                    m_selectedY = y;
                    qDebug() << "Selected piece at:" << x << y 
                             << "Color:" << (board[x][y]->isBlack() ? "Black" : "White");
                } else {
                    qDebug() << "Can't select - wrong color or empty";
                }
            }
            update();  
        }
    }
}

void ChessWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    
    m_boardRect = QRect(
        (width() - BOARD_SIZE) / 2,
        MARGIN,
        BOARD_SIZE,
        BOARD_SIZE
    );
    
    m_statusRect = QRect(
        m_boardRect.left(),
        m_boardRect.bottom() + 10,
        BOARD_SIZE,
        30
    );
    
    m_buttonRect = QRect(
        (width() - 200) / 2,
        m_statusRect.bottom() + 20,
        200,
        50
    );
    
    if (m_endGameButton) {
        m_endGameButton->setGeometry(m_buttonRect);
    }
    
    update();
}

void ChessWidget::drawKingHighlight(QPainter& painter) {
    if (!m_board || m_board->isGameOver()) return;
    
    auto drawHighlight = [&](bool isBlack, const QColor& color) {
        auto kingPos = m_board->findKing(isBlack);
        if (kingPos.first != -1) {
            QRect rect = cellRect(kingPos.first, kingPos.second);
            painter.fillRect(rect, color);
            painter.setPen(QPen(Qt::black, 2));
            painter.drawRect(rect);
            
            
            if (m_board->isCheckmate(isBlack)) {
                painter.setFont(QFont("Arial", CELL_SIZE/3, QFont::Bold));
                painter.setPen(Qt::white);
                painter.drawText(rect, Qt::AlignCenter, "МАТ");
            }
        }
    };
    
    if (m_board->isCheckmate(false)) {
        drawHighlight(false, QColor(255, 0, 0, 150)); 
    } 
    else if (m_board->isCheck(false)) {
        drawHighlight(false, QColor(255, 182, 193, 150)); 
    }
    
    if (m_board->isCheckmate(true)) {
        drawHighlight(true, QColor(255, 0, 0, 150)); 
    } 
    else if (m_board->isCheck(true)) {
        drawHighlight(true, QColor(255, 182, 193, 150)); 
    }
}

chessboard* ChessWidget::getChessboard() {
    return m_board;
}

QString ChessWidget::createMoveString(int x1, int y1, int x2, int y2){
    return QString("MOVE%1%2%3%4").arg(x1).arg(y1).arg(x2).arg(y2);
}

void ChessWidget::parseMoveString(const QString &moveStr, int &x1, int &y1, int &x2, int &y2) {
    QRegularExpression regex("^MOVE(\\d+)(\\d+)(\\d+)(\\d+)$");
    QRegularExpressionMatch match = regex.match(moveStr);

    if (match.hasMatch()) {
        x1 = match.captured(1).toInt();
        y1 = match.captured(2).toInt();
        x2 = match.captured(3).toInt();
        y2 = match.captured(4).toInt();
    } else {
        throw std::invalid_argument("Invalid MOVE string format");
    }
}

void ChessWidget::networkImpact(const QString &moveStr){
    int X1, Y1, X2, Y2;
    parseMoveString(moveStr, X1, Y1, X2, Y2);
    m_board->moveSquare(X1, Y1, X2, Y2);
    update();  
}