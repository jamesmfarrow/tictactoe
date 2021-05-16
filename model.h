#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <QRandomGenerator>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "aigamemove.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    bool getOnePlayergame() const;
    void setOnePlayergame(bool value);

    bool getTwoPlayerGame() const;
    void setTwoPlayerGame(bool value);

    bool getPlayer1FirstMove() const;
    void setPlayer1FirstMove(bool value);

    bool squareTaken(int row, int col);
    void updateBoard(int row, int col);

    bool getPlayer1Move() const;
    void setPlayer1Move(bool value);

    void whoWon();

    bool getPlayer1Won() const;
    void setPlayer1Won(bool value);

    bool getPlayer2Won() const;
    void setPlayer2Won(bool value);

    void resetGame();

    //make a random move
    void randomMove();

    //AIPlayer status
    bool getAIPlayer() const;
    void setAIPlayer(bool value);

    //get and set the
    int getAIRowMove() const;
    void setAIRowMove(int value);
    int getAIColMove() const;
    void setAIColMove(int value);

    //below true AI MINMAX code
    int evalMinMax();
    int evalRowColMinMax(int playerX, int playerO);
    AIGameMove minimax(bool maximising_player = true, int depth = level, int alpha = -INT_MAX, int beta = INT_MAX);
    void makeMinMaxMove();
    bool minMaxDraw();
    bool minMaxWin();
    void setAIDifficulty();

    bool getDrawnGame() const;
    void setDrawnGame(bool value);

signals:

private:
    bool onePlayerGame;
    bool twoPlayerGame;
    bool player1FirstMove;
    bool player1Move;
    bool AIPlayer;

    bool player1Won{false};
    bool player2Won{false};

    bool gameOver;
    bool drawnGame;

    int board[3][3]{};
    int numberOfTurns{0};
    int AIRowMove;
    int AIColMove;
    static int level;

};

#endif // MODEL_H
