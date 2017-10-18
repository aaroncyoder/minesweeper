#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

class GameButton;

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(int mineWidth, int mineHeight, int mineCount, QWidget *parent = 0);
    bool gameStarted();

signals:
    
public slots:
    void clearBoard();

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
    
};

#endif // GAMEBOARD_H
