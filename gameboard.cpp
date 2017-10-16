#include <QtGui>

#include <cstdlib>
#include <ctime>

#include "gameboard.h"
#include "gamebutton.h"

GameBoard::GameBoard(int x, int y, QWidget *parent) :
    QWidget(parent),
    maxX(std::max(2,x)),
    maxY(std::max(2,y))
{

    QFile file(":/resources/gameboardstyle.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(file.readAll());
        file.close();
    }

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    grid = new GameButton*[maxY * maxX];

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            GameButton *button = new GameButton();
            gridLayout->addWidget(button, y, x);
            addButton(x, y, button);
            connect(button, SIGNAL(mineExploded()), this, SLOT(clearBoard()));
        }
    }

    setLayout(gridLayout);
    setFixedSize(QSize(maxX * buttonSize, maxY * buttonSize));

    if (parent != NULL) {
        parent->setFixedSize(QSize(maxX * buttonSize, maxY * buttonSize));
    }

    srand(time(NULL));
    for(int i = 0; i < 20; ) {
        int x = rand() % maxX;
        int y = rand() % maxY;
        if (addMine(x, y))
            i++;
    }
}

void GameBoard::clearBoard()
{
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            sendLeftClick(x, y);
        }
    }

}

void GameBoard::addButton(int x, int y, GameButton *button)
{
    if ((button == NULL) || (grid == NULL))
        return;

    grid[y * maxX + x] = button;
}

bool GameBoard::addMine(int x, int y)
{
    if (grid != NULL)
        return grid[y * maxX + x]->makeExplodable();
    else
        return false;
}

void GameBoard::sendLeftClick(int x, int y)
{
    if (grid != NULL)
        grid[y * maxX + x]->handleLeftClick();
}
