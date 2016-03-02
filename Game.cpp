/* Trung Le and Johnny Le
 * CS 3505
 * Simon Game
 * 02/26/2016
 * Game class implementation
*/
#include <game.h>
#include <iostream>
#include <vector>
#include <QTimer>
#include <QDebug>
#include <QTGlobal>
#include <QTime>
#include <algorithm>    // std::sort


using namespace std;

//Creates the timer and
Game::Game(){

}

//Deletes the timer
Game::~Game(){
    timer->deleteLater();
}

//Start timer
void Game::startTimer(){
    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(dummy()));
    qDebug() << "Timer started...";
    timer->start(1000);
}

//Creates a randomly generated number and returns either 1 or 0
int Game::generateRandomInt(){
    QTime now = QTime::currentTime();

    if (!alt) {
       qsrand(now.msec()*(1013));
       alt = true;
    }
    else {
        qsrand(now.msec()*now.msec()*(1753));
        alt = false;
    }


    num = qrand();

    //For debugging purposes
    if(num % 2 == 1){
        qDebug() << "Red";
    }
    else{
        qDebug() << "Blue";
    }

    return num % 2;
}

//Returns the full sequence for flashing
QVector<int> Game::getSequence() {
    return computerGeneratedSequence;
}

//Add the value to vector
void Game::addToSequence(){
    computerGeneratedSequence.push_back(generateRandomInt());
}

//Writes for a number for each second past
void Game::dummy(){
    qDebug() << i++;
    if (computerGeneratedSequence.count() != 0) {
        qDebug() << computerGeneratedSequence.at(0);
    }
}

//Checks if the value is correct and increments the int to the next
bool Game::checkUserInputAgainstGenerated(int num){
    if (num != computerGeneratedSequence.at(check)) {
        return false;
    }
    else {
        check++;
        return true;
    }
}

void Game::nextRound() {
    round++;
    check = 0;
    addToSequence();
}

//Resets parameters
void Game::gameOver() {
    roundLostAt = round;
    check = 0;
    round = -1; //So that the first round will start on 1
    computerGeneratedSequence.clear();
}


