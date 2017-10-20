#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

class GameButton;
class QLCDNumber;

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(int mineWidth, int mineHeight, int mineCount, QWidget *parent = 0);
    bool gameStarted();

signals:
    void boardIsWinner();

public slots:
    void clearBoard();
    void decrementMineCounter(bool marked);
    void handleButtonClick();
    void updateTimeCountLCD();

private:
    GameButton **grid;
    void addButton(int x, int y, GameButton *button);
    bool addMine(int x, int y);
    void incrementAdjacentNeighbors(int x, int y);
    void connectAllNeighbors();
    GameButton *getGrid(int x, int y);
    int maxX;
    int maxY;
    static const int buttonSize = 20;
    QLCDNumber *mineCountLCD;
    QLCDNumber *timeCountLCD;
    QTimer *timer;
};

#endif // GAMEBOARD_H
