#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

class GameButton;

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(int x, int y, QWidget *parent = 0);

signals:
    
public slots:
    void clearBoard();

private:
    GameButton **grid;
    void addButton(int x, int y, GameButton *button);
    bool addMine(int x, int y);
    void sendLeftClick(int x, int y);
    int maxX;
    int maxY;
    static const int buttonSize = 20;
    
};

#endif // GAMEBOARD_H
