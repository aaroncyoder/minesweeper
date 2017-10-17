#include <QtGui>

#include "gamebutton.h"

GameButton::GameButton(QWidget *parent) :
    QPushButton(parent),
    flagged(false),
    explodingMine(false),
    neighborMineCount(0)
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

    if (!flagged) {
        this->setDisabled(true);

        if (explodingMine) {
            this->setText(QString("X"));
            emit mineExploded();
        } else {
            displayMineCount();
        }
    }
}

void GameButton::gameOverState()
{
    if (!isEnabled())
        return;

    if (explodingMine) {
        this->setText("X");
    } else {
        if (neighborMineCount > 0)
            this->setText(QString::number(neighborMineCount));
        else
            this->setText("");
    }

    this->setDisabled(true);

}

void GameButton::handleRightClick()
{
    if (flagged)
        this->setText("");
    else
        this->setText("F");

    flagged = !flagged;
}

void GameButton::displayMineCount()
{
    if (neighborMineCount > 0)
        this->setText(QString::number(neighborMineCount));
    else if (neighborMineCount == 0)
        emit clickAllNeighbors();
}

void GameButton::incNeighborMineCount()
{
    neighborMineCount++;
}


void GameButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton) {
        emit rightClicked();
    }

    QPushButton::mousePressEvent(e);
}
