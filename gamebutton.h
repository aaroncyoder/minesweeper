#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>

class QPropertyAnimation;

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
    void animateButton(int right, int bottom, int duration);

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
    QPropertyAnimation *animation;
};

#endif // GAMEBUTTON_H
