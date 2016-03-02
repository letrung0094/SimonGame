/* Trung Le and Johnny Le
 * CS 3505
 * Simon Game
 * 02/26/2016
 * Game class header
*/
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <QTimer>
#include <QVector>
using namespace std;

class Game : public QObject
{
    Q_OBJECT
private:
    QVector<int> computerGeneratedSequence;
    QVector<int> playerInputSequence;
    int i = 0;
    int check = 0; //Used to track which indices have been checked
    int num; //Number added to sequence
    bool alt = false; //Allows for greater randomness
public:
    int round = -1; //Init for a pattern length of two
    int roundLostAt;
    Game();
    ~Game();

    int generateRandomInt();
    void addToSequence();
    QVector<int> getSequence();

    bool checkUserInputAgainstGenerated(int num);
    void gameOver();
    void startTimer();
    QTimer *timer; //Timer Pointer

public slots:
    void dummy();
    void nextRound();
};

#endif // GAME_H


