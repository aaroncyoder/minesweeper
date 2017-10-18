#include <QtGui>

#include "gamesettingsdialog.h"

GameSettingsDialog::GameSettingsDialog(int width, int height, int mines, QWidget *parent) :
    QDialog(parent)
{

    setWindowTitle(tr("MineSweeper Settings"));

    widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(5,50);
    widthSpinBox->setValue(width);

    heightSpinBox = new QSpinBox();
    heightSpinBox->setRange(5,50);
    heightSpinBox->setValue(height);

    mineCountSpinBox = new QSpinBox();
    mineCountSpinBox->setRange(5,200);
    mineCountSpinBox->setValue(mines);

    QLabel *widthLabel = new QLabel(tr("Grid Width: "));
    QLabel *heightLabel = new QLabel(tr("Grid Height: "));
    QLabel *mineCountLabel = new QLabel(tr("Mine Count: "));

    QPushButton *okButton = new QPushButton(tr("&OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okPressed()));

    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(widthLabel, 0, 0);
    layout->addWidget(widthSpinBox, 0, 1);
    layout->addWidget(heightLabel, 1, 0);
    layout->addWidget(heightSpinBox, 1, 1);
    layout->addWidget(mineCountLabel, 2, 0);
    layout->addWidget(mineCountSpinBox, 2, 1);
    layout->addWidget(okButton, 3, 0);
    layout->addWidget(cancelButton, 3, 1);

    setLayout(layout);
    setFixedSize(layout->geometry().width(), layout->geometry().height());
}


void GameSettingsDialog::okPressed()
{
    emit widthChanged(widthSpinBox->value());
    emit heightChanged(heightSpinBox->value());
    emit mineCountChanged(mineCountSpinBox->value());

    this->close();
    this->setResult(QDialog::Accepted);
}

void GameSettingsDialog::cancelPressed()
{
    this->close();
    this->setResult(QDialog::Rejected);
}
