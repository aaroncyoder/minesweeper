#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>

class GameButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GameButton(QWidget *parent = 0);
    bool makeExplodable();
    
signals:
    void rightClicked();
    void mineExploded();

private slots:
    void mousePressEvent(QMouseEvent *e);

public slots:
    void handleLeftClick();
    void handleRightClick();

private:
    bool flagged;
    bool explodingMine;
};

#endif // GAMEBUTTON_H
