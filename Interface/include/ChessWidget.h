#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>  
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include "../../game/include/chessboard.h"

class ChessWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessWidget(QWidget *parent = nullptr);
    ~ChessWidget() override = default;
    void setChessboard(chessboard* board);
    void networkImpact(const QString &moveStr);
    chessboard* getChessboard();

signals:  
    void cellSelected(int x, int y);
    void gameEndRequested();
    void move(const QString &massege);
    
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    chessboard* m_board = nullptr;
    QSize m_cellSize;
    int m_selectedX = -1;
    int m_selectedY = -1;
    QRect m_boardRect;
    QRect m_statusRect;  
    QRect m_buttonRect;  
    QMap<QString, QPixmap> pieceImages;
    QPushButton* m_endGameButton;

    void drawChessboard(QPainter& painter);
    void drawPieces(QPainter& painter);
    void drawSelection(QPainter& painter);  
    void drawCoordinates(QPainter& painter);
    QRect cellRect(int x, int y) const;
    void loadPieceImages();
    void drawKingHighlight(QPainter& painter);
    void setupUi();
    QString createMoveString(int x1, int y1, int x2, int y2);
    void parseMoveString(const QString &moveStr, int &x1, int &y1, int &x2, int &y2);
};