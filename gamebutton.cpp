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
            this->setObjectName("explodedMine");
            this->setText(QString("X"));
            style()->unpolish(this);
            style()->polish(this);
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

void GameButton::displayMineCount()
{
    if (neighborMineCount > 0) {
        QString objName = "mineCount";
        objName.append(QString::number(neighborMineCount));
        this->setObjectName(objName);

        this->setText(QString::number(neighborMineCount));
        style()->unpolish(this);
        style()->polish(this);
    }
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
