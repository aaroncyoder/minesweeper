#ifndef GAMESETTINGSDIALOG_H
#define GAMESETTINGSDIALOG_H

#include <QDialog>

class QSpinBox;

class GameSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GameSettingsDialog(int width, int height, int mines, QWidget *parent = 0);
    void test();

signals:
    void widthChanged(int newWidth);
    void heightChanged(int newHeight);
    void mineCountChanged(int newMineCount);

private slots:
    void okPressed();
    void cancelPressed();

private:
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QSpinBox *mineCountSpinBox;
};

#endif // GAMESETTINGSDIALOG_H
