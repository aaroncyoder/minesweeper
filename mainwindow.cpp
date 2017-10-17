#include <QtGui>

#include "mainwindow.h"
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    GameBoard *gameBoard = new GameBoard(10, 10, this);
    setCentralWidget(gameBoard);

    createActions();
    createMenus();

    setFixedSize(gameBoard->width(), gameBoard->height() + gameMenu->height());
}

void MainWindow::startNewGame()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("MineSweeper"),
                 tr("Current game board will be lost.\n"
                    "Do you want to start a new game?"),
                 QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        GameBoard *gameBoard = new GameBoard(10, 10, this);
        setCentralWidget(gameBoard);
    }
}

void MainWindow::createActions()
{
    newGameAct = new QAction(tr("&New Game"), this);
    newGameAct->setShortcuts(QKeySequence::New);
    newGameAct->setStatusTip(tr("Start a new game"));
    connect(newGameAct, SIGNAL(triggered()), this, SLOT(startNewGame()));

    exitGameAct = new QAction(tr("E&xit"), this);
    exitGameAct->setShortcuts(QKeySequence::Quit);
    exitGameAct->setStatusTip(tr("Exit the game"));
    connect(exitGameAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newGameAct);
    gameMenu->addAction(exitGameAct);
}
