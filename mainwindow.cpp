#include <QtGui>

#include "mainwindow.h"
#include "gameboard.h"
#include "gamesettingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mineWidth(10),
    mineHeight(10),
    mineCount(10)
{
    gameBoard = new GameBoard(mineWidth, mineHeight, mineCount, this);
    setCentralWidget(gameBoard);

    createActions();
    createMenus();

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::startNewGame()
{
    if (gameBoard->gameStarted()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("MineSweeper"),
                     tr("Current game board will be lost.\n"
                        "Do you want to start a new game?"),
                     QMessageBox::Yes | QMessageBox::No);
        if (ret != QMessageBox::Yes) {
            return;
        }
    }

    delete gameBoard;
    gameBoard = new GameBoard(mineWidth, mineHeight, mineCount, this);
    setCentralWidget(gameBoard);


}

void MainWindow::gameSettingsDialog()
{
    GameSettingsDialog *dialog = new GameSettingsDialog(mineWidth, mineHeight, mineCount);
    dialog->setModal(true);
    connect(dialog, SIGNAL(widthChanged(int)), this, SLOT(setMineWidth(int)));
    connect(dialog, SIGNAL(heightChanged(int)), this, SLOT(setMineHeight(int)));
    connect(dialog, SIGNAL(mineCountChanged(int)), this, SLOT(setMineCount(int)));

    int dialogCode = dialog->exec();

    if (dialogCode == QDialog::Accepted)
        startNewGame();
}

void MainWindow::createActions()
{
    newGameAct = new QAction(tr("&New Game"), this);
    newGameAct->setShortcuts(QKeySequence::New);
    newGameAct->setStatusTip(tr("Start a new game"));
    connect(newGameAct, SIGNAL(triggered()), this, SLOT(startNewGame()));

    gameSettingsAct = new QAction(tr("Game &Settings"), this);
    gameSettingsAct->setStatusTip(tr("Change game settings."));
    connect(gameSettingsAct, SIGNAL(triggered()), this, SLOT(gameSettingsDialog()));

    exitGameAct = new QAction(tr("E&xit"), this);
    exitGameAct->setShortcuts(QKeySequence::Quit);
    exitGameAct->setStatusTip(tr("Exit the game"));
    connect(exitGameAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newGameAct);
    gameMenu->addAction(gameSettingsAct);
    gameMenu->addAction(exitGameAct);
}
