#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <memory>
#include "model.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void setOnePlayerGame();
    void setTwoPlayerGame();
    void setPlayer1FirstMove(bool firstMove);

    bool squareTaken(int row, int col);
    void updateBoard(int row, int col);
    bool player1ToMove();
    void setPlayer1ToMove(bool move);

    bool player1HasWon();
    bool player2HasWon();

    bool getAIPlayer();
    void setAIPlayer(bool AI);
    int getAIRowMove();
    int getAIColMove();
    void AIRandomMove();
    void minMaxAIMove();
    void setAIDifficulty();

    void whoWonGame();
    bool isGameADraw();

    void resetGame();


signals:

private:
    //Model *model{new Model(this)};
    std::unique_ptr<Model> model{std::make_unique<Model>(new Model())};
};

#endif // CONTROLLER_H
