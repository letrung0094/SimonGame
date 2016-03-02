/* Trung Le and Johnny Le
 * CS 3505
 * Simon Game
 * 02/26/2016
 * Main view controller
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include "Game.h"
#include "QTimer"
#include "QTime"
#include "string"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PercentageComplete->setMinimum(0);
    ui->PercentageComplete->setValue(0);

    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->MemorizeLabel->hide();
    ui->YourTurnLabel->hide();
    ui->GameOverLabel->hide();
    ui->highScoresView->hide();

    //Starts the buttons on a slightly lighter shade
    ui->redButton->setStyleSheet("background-color:rgb(255, 74, 74)");
    ui->blueButton->setStyleSheet("background-color:rgb(39, 122, 255)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Starts the game, activates the buttons, and begins the round
void MainWindow::on_startButton_clicked()
{
    newGame = new Game();

    ui->startButton->setEnabled(false);
    ui->startButton->hide();
    ui->GameOverLabel->hide();
    ui->highScoresView->hide();

    //Iterates for the length of the start pattern
    for (int i = 0; i < patternLength; i++) {
        newGame->nextRound();
    }

    ui->highScoresView->clear();

    flashSequence();
}

//Displays the pattern so far on the screen
void MainWindow::flashSequence() {
    QVector<int> sequence;
    sequence = newGame->getSequence();

    QString qstr = QString::number(newGame->round);
    ui->roundNumber->setText(qstr);

    ui->PercentageComplete->setMaximum(sequence.count());
    ui->YourTurnLabel->hide();
    ui->MemorizeLabel->show();

    for (QVector<int>::iterator it = sequence.begin(); it != sequence.end(); ++it) {
        if (*it == 0) {
            //Wait 1 second, then flash blue for 1 second, then return to regular color
            delay(speed);
            flashBlue();
            delay(speed);
            ui->blueButton->setStyleSheet("background-color:rgb(39, 122, 255)");
        }
        else {
            delay(speed);
            flashRed();
            delay(speed);
            ui->redButton->setStyleSheet("background-color:rgb(255, 74, 74)");
        }
    }
    ui->MemorizeLabel->hide();
    playerTurn();
}

void MainWindow::flashBlue(){
    ui->blueButton->setStyleSheet("background-color:blue");
}

void MainWindow::flashRed(){
    ui->redButton->setStyleSheet("background-color:rgb(255, 0, 0)");
}

//Delays the execution of the program
void MainWindow::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void MainWindow::playerTurn(){
    ui->YourTurnLabel->show();
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

//End the users turn
//Adds an element to the sequence and flash sequence
void MainWindow::endTurn(){
    if (speed != 150) {
        speed -= 50;
    }

    currentCorrect = 0;
    ui->PercentageComplete->setValue(0);

    ui->YourTurnLabel->hide();
    ui->MemorizeLabel->show();
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    newGame->nextRound();
    flashSequence();
}

//Highlights the red button
void MainWindow::on_redButton_pressed()
{
    ui->redButton->setStyleSheet("background-color:rgb(255, 0, 0)");

}

//Inputs "1" into the system
void MainWindow::on_redButton_released()
{
    ui->redButton->setStyleSheet("background-color:rgb(255, 74, 74)");
        if (!(newGame->checkUserInputAgainstGenerated(1))) {
            restart();
        }
        else {
            currentCorrect++;
            ui->PercentageComplete->setValue(currentCorrect);
        }
}

//Highlights the blue button
void MainWindow::on_blueButton_pressed()
{
    ui->blueButton->setStyleSheet("background-color:blue");
}

//Inputs "0" into the system
void MainWindow::on_blueButton_released()
{
    ui->blueButton->setStyleSheet("background-color:rgb(39, 122, 255)");
    if (!(newGame->checkUserInputAgainstGenerated(0))) {
        restart();
    }
    else {
        currentCorrect++;
        ui->PercentageComplete->setValue(currentCorrect);
    }
}

//Ends game and displays game over
void MainWindow::restart() {
    newGame->gameOver();

    speed = 600;
    currentCorrect = 0;
    ui->PercentageComplete->setValue(0);

    ui->startButton->show();
    ui->startButton->setEnabled(true);

    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);

    ui->GameOverLabel->show();
    ui->YourTurnLabel->hide();

    displayHighScores();
}

//Displays the best score achieved
void MainWindow::displayHighScores(){
    ui->highScoresView->show();

    QString place = "Your Best: ";

    //Get round lost at
    int currentBest = newGame->roundLostAt;

    //Append to high scores vector and sort
    AllTimehighScores.push_back(currentBest);
    std::sort (AllTimehighScores.begin(), AllTimehighScores.end());

    //Best score is at last index
    int best = AllTimehighScores.at(AllTimehighScores.count() - 1);

    QString s = QString::number(best);
    place += s;

    if(best > 1){
        place += " rounds";
    }
    else{
        place += " round";
    }

    ui->highScoresView->addItem(place);
}

//Starts a new round when it fills
void MainWindow::on_PercentageComplete_valueChanged(int value)
{
    if (value == ui->PercentageComplete->maximum()) {
        endTurn();
    }
}
