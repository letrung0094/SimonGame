#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "Game.h"
#include <QVector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Game* newGame;
    int patternLength = 2; //The starting pattern length
    int currentCorrect = 0; //Controls the Progress Bar
    int speed = 600; //Controls the pace of flashSequence
    QVector<int> AllTimehighScores;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayHighScores();

    void flashSequence();

    void playerTurn();

    void flashRed();

    void flashBlue();

    void delay(int millisecondsToWait);

    void endTurn();

    void restart();

private slots:
    void on_startButton_clicked();

    void on_redButton_pressed();

    void on_redButton_released();

    void on_blueButton_pressed();

    void on_blueButton_released();

    void on_PercentageComplete_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
