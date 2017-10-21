#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>

class GameButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GameButton(QWidget *parent = 0);
    bool makeExplodable();
    void displayMineCount();
    void incNeighborMineCount();
    bool unTouched();
    bool winningState();
    void gameOverState();
    void resetGameButton();

signals:
    void rightClicked();
    void mineExploded();
    void mineMarked(bool flagged);
    void clickAllNeighbors();

private slots:
    void mousePressEvent(QMouseEvent *e);

public slots:
    void handleLeftClick();
    void handleRightClick();

private:
    bool flagged;
    bool explodingMine;
    int neighborMineCount;
    bool gameOver;
};

#endif // GAMEBUTTON_H
