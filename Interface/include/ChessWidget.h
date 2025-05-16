#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "../../game/include/chessboard.h"

class ChessWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessWidget(QWidget *parent = nullptr);
    ~ChessWidget() override = default;
    void setChessboard(chessboard* board);

signals:  
    void cellSelected(int x, int y); 
    
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
    QMap<QString, QPixmap> pieceImages; 


    void drawChessboard(QPainter& painter);
    void drawPieces(QPainter& painter);
    void drawSelection(QPainter& painter);  
    void drawCoordinates(QPainter& painter);
    QRect cellRect(int x, int y) const;
    void loadPieceImages();
    void drawKingHighlight(QPainter& painter);
  
    
};