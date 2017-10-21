#include <QtGui>

#include <cstdlib>
#include <ctime>

#include "gameboard.h"
#include "gamebutton.h"

GameBoard::GameBoard(int mineWidth, int mineHeight, int mineCount, QWidget *parent) :
    QWidget(parent),
    maxX(std::max(2,mineWidth)),
    maxY(std::max(2,mineHeight)),
    mineCount(mineCount),
    timer(NULL),
    gameOverState(false)
{
    QFile file(":/resources/gameboardstyle.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(file.readAll());
        file.close();
    }

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    grid = new GameButton*[maxY * maxX];
    Q_CHECK_PTR(grid);

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            GameButton *button = new GameButton();
            button->setFixedSize(buttonSize, buttonSize);
            gridLayout->addWidget(button, y + 1, x);
            addButton(x, y, button);
            connect(button, SIGNAL(mineExploded()), this, SLOT(clearBoard()));
        }
    }

    connectAllNeighbors();

    mineCountLCD = new QLCDNumber(3);
    mineCountLCD->setFixedSize(40, 40);
    mineCountLCD->setSegmentStyle(QLCDNumber::Flat);
    mineCountLCD->setContentsMargins(QMargins(0,0,0,4));

    timeCountLCD = new QLCDNumber(3);
    timeCountLCD->setFixedSize(40, 40);
    timeCountLCD->setSegmentStyle(QLCDNumber::Flat);
    timeCountLCD->setContentsMargins(QMargins(0,0,0,4));

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeCountLCD()));

    resetGameBoard(mineCount);

    QPushButton *newGameButton = new QPushButton("New");
    newGameButton->setFixedSize(40, 40);
    newGameButton->setObjectName("newGameButton");
    connect (newGameButton, SIGNAL(clicked()), parent, SLOT(startNewGame()));

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(mineCountLCD);
    topLayout->addStretch();
    topLayout->addWidget(newGameButton);
    topLayout->addStretch();
    topLayout->addWidget(timeCountLCD);
    gridLayout->addLayout(topLayout, 0, 0, 1, maxX);

    setLayout(gridLayout);
    setFixedSize(gridLayout->minimumSize());
}

bool GameBoard::gameStarted()
{
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (!getGrid(x, y)->unTouched())
                return true;
        }
    }

    return false;
}

void GameBoard::clearBoard()
{
    gameOverState = true;
    timer->stop();

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            getGrid(x, y)->gameOverState();
        }
    }

}

void GameBoard::decrementMineCounter(bool marked)
{
    if (marked)
        mineCountLCD->display(mineCountLCD->value() - 1);
    else
        mineCountLCD->display(mineCountLCD->value() + 1);
}

void GameBoard::handleButtonClick()
{
    if (!timer->isActive() && !gameOverState)
        timer->start(1000);

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (!getGrid(x, y)->winningState())
                return;
        }
    }

    timer->stop();
    emit boardIsWinner();
    clearBoard();
}

void GameBoard::updateTimeCountLCD()
{
    timeCountLCD->display(timeCountLCD->value() + 1);
}

void GameBoard::addButton(int x, int y, GameButton *button)
{
    if (button == NULL)
        return;

    grid[y * maxX + x] = button;
    connect(button, SIGNAL(mineMarked(bool)), this, SLOT(decrementMineCounter(bool)));
    connect(button, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(button, SIGNAL(rightClicked()), this, SLOT(handleButtonClick()));

}

bool GameBoard::addMine(int x, int y)
{
    return getGrid(x, y)->makeExplodable();
}

void GameBoard::incrementAdjacentNeighbors(int x, int y)
{
    int xLeft = x - 1;
    int xRight = x + 1;
    int yUp = y - 1;
    int yDown = y + 1;

    if (yUp >= 0)
        getGrid(x, yUp)->incNeighborMineCount();
    if (yDown < maxY)
        getGrid(x, yDown)->incNeighborMineCount();

    if (xLeft >= 0) {
        getGrid(xLeft, y)->incNeighborMineCount();
        if (yUp >= 0)
            getGrid(xLeft, yUp)->incNeighborMineCount();
        if (yDown < maxY)
            getGrid(xLeft, yDown)->incNeighborMineCount();
    }
    if (xRight < maxX) {
        getGrid(xRight, y)->incNeighborMineCount();
        if (yUp >= 0)
            getGrid(xRight, yUp)->incNeighborMineCount();
        if (yDown < maxY)
            getGrid(xRight, yDown)->incNeighborMineCount();
    }
}

void GameBoard::connectAllNeighbors()
{
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            GameButton *button = getGrid(x, y);
            int xLeft = x - 1;
            int xRight = x + 1;
            int yUp = y - 1;
            int yDown = y + 1;

            if (yUp >= 0)
                connect(button, SIGNAL(clickAllNeighbors()), getGrid(x, yUp), SLOT(handleLeftClick()));
            if (yDown < maxY)
                connect(button, SIGNAL(clickAllNeighbors()), getGrid(x, yDown), SLOT(handleLeftClick()));

            if (xLeft >= 0) {
                connect(button, SIGNAL(clickAllNeighbors()), getGrid(xLeft, y), SLOT(handleLeftClick()));
                if (yUp >= 0)
                    connect(button, SIGNAL(clickAllNeighbors()), getGrid(xLeft, yUp), SLOT(handleLeftClick()));
                if (yDown < maxY)
                    connect(button, SIGNAL(clickAllNeighbors()), getGrid(xLeft, yDown), SLOT(handleLeftClick()));
            }
            if (xRight < maxX) {
                connect(button, SIGNAL(clickAllNeighbors()), getGrid(xRight, y), SLOT(handleLeftClick()));
                if (yUp >= 0)
                    connect(button, SIGNAL(clickAllNeighbors()), getGrid(xRight, yUp), SLOT(handleLeftClick()));
                if (yDown < maxY)
                    connect(button, SIGNAL(clickAllNeighbors()), getGrid(xRight, yDown), SLOT(handleLeftClick()));
            }

        }
    }
}

GameButton *GameBoard::getGrid(int x, int y)
{
    return grid[y * maxX + x];
}

void GameBoard::resetGameBoard(int mineCount)
{
    this->mineCount = mineCount;
    gameOverState = false;

    if (timer->isActive())
        timer->stop();

    timeCountLCD->display(0);
    mineCountLCD->display(mineCount);

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            getGrid(x, y)->resetGameButton();
        }
    }

    mineCount = std::min(mineCount, maxX*maxY);
    srand(time(NULL));
    for(int i = 0; i < mineCount; ) {
        int x = rand() % maxX;
        int y = rand() % maxY;
        if (addMine(x, y)) {
            i++;
            incrementAdjacentNeighbors(x, y);
        }
    }
}

void GameBoard::animateButtons()
{
    int right = this->geometry().right();
    int bottom = this->geometry().bottom();
    int range = maxX * maxY;
    const int maxAnimate = 200;

    this->show();

    srand(time(NULL));

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if ((rand() % range) <= maxAnimate) {
                getGrid(x, y)->animateButton(rand() % right, rand() % bottom,
                                             200 + rand() % 800);

            }
        }
    }
}
