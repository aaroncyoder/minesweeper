#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    
private slots:
    void startNewGame();
    void gameSettingsDialog();
    void setMineWidth(int width) { mineWidth = width; }
    void setMineHeight(int height) { mineHeight = height; }
    void setMineCount(int count) { mineCount = count; }

private:
    void createActions();
    void createMenus();
    QAction *newGameAct;
    QAction *gameSettingsAct;
    QAction *exitGameAct;
    QMenu *gameMenu;
    GameBoard *gameBoard;

    int mineWidth;
    int mineHeight;
    int mineCount;
};

#endif // MAINWINDOW_H
