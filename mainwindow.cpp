#include <QtGui>

#include "mainwindow.h"
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    GameBoard *gameBoard = new GameBoard(10, 10, this);
    setCentralWidget(gameBoard);
}
