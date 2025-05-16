
#include "..\\include\\ChessWidget.h"
#include <QFileInfo>  
#include <QPainter>
#include <QPixmap>

const int BOARD_SIZE = 480;
const int CELL_SIZE = BOARD_SIZE / 8;
const int MARGIN = 30;

ChessWidget::ChessWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(BOARD_SIZE + 2*MARGIN, BOARD_SIZE + 2*MARGIN);
    loadPieceImages();
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
        (height() - BOARD_SIZE) / 2,
        BOARD_SIZE,
        BOARD_SIZE
    );
    
    painter.translate(m_boardRect.topLeft());
    
    drawChessboard(painter);
    drawSelection(painter);  
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
    if (!m_board) return;
    
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
    painter.setFont(QFont("Arial", 12));
    painter.setPen(Qt::black);
    
    for (int y = 0; y < 8; ++y) {
        QRect rect(
            m_boardRect.right() + 5,
            m_boardRect.top() + y * CELL_SIZE + CELL_SIZE/2 - 10,
            20,
            20
        );
        painter.drawText(rect, Qt::AlignLeft, QString::number(8 - y));
    }
    
    for (int x = 0; x < 8; ++x) {
        QRect rect(
            m_boardRect.left() + x * CELL_SIZE + CELL_SIZE/2 - 10,
            m_boardRect.bottom() + 5,
            20,
            20
        );
        painter.drawText(rect, Qt::AlignTop, QString(QChar('a' + x)));
    }
    
    QString turnText = m_board->isBlackTurn() ? "Ход черных" : "Ход белых";
    QRect turnRect(
        m_boardRect.left(),
        m_boardRect.bottom() + 30,
        BOARD_SIZE,
        20
    );
    painter.drawText(turnRect, Qt::AlignCenter, turnText);
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
    update();
}