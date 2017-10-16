#include <QtGui>

#include "gamebutton.h"

GameButton::GameButton(QWidget *parent) :
    QPushButton(parent),
    flagged(false),
    explodingMine(false)
{
    connect(this, SIGNAL(clicked()), this, SLOT(handleLeftClick()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(handleRightClick()));
}

bool GameButton::makeExplodable()
{
    if (explodingMine)
        return false;

    explodingMine = true;
    return true;
}

void GameButton::handleLeftClick()
{
    if (!isEnabled())
        return;

    if (!flagged)
        this->setDisabled(true);

    if (explodingMine) {
        this->setText("X");
        emit mineExploded();
    }
}

void GameButton::handleRightClick()
{
    if (flagged)
        this->setText("");
    else
        this->setText("F");

    flagged = !flagged;
}


void GameButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton) {
        emit rightClicked();
    }

    QPushButton::mousePressEvent(e);
}
