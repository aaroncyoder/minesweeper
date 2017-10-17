#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    
private slots:
    void startNewGame();

private:
    void createActions();
    void createMenus();
    QAction *newGameAct;
    QAction *exitGameAct;
    QMenu *gameMenu;
};

#endif // MAINWINDOW_H
