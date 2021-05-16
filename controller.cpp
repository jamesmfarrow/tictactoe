#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    //GC = std::make_unique<GameChoice>(new GameChoice());
}

Controller::~Controller()
{
    delete model;
}

/*
void Controller::AIGameSelected()
{
    GC->setAIGameSelected(true);
}
*/

void Controller::setOnePlayerGame()
{
    model->setOnePlayergame(true);
}

void Controller::setTwoPlayerGame()
{
    model->setTwoPlayerGame(true);
}

void Controller::setPlayer1FirstMove(bool firstMove)
{
    model->setPlayer1FirstMove(firstMove);
}

bool Controller::squareTaken(int row, int col)
{
    return model->squareTaken(row, col);
    //qInfo() << "controller sq take" << row << " " << col;
}

void Controller::updateBoard(int row, int col)
{
    model->updateBoard(row, col);
}

bool Controller::player1ToMove()
{
    return model->getPlayer1Move();
}

void Controller::setPlayer1ToMove(bool move)
{
    model->setPlayer1Move(move);
}

bool Controller::player1HasWon()
{

    return model->getPlayer1Won();
}

bool Controller::player2HasWon()
{
    return model->getPlayer2Won();
}

bool Controller::getAIPlayer()
{
    return model->getAIPlayer();
}

void Controller::setAIPlayer(bool AI)
{
    model->setAIPlayer(AI);
}

int Controller::getAIRowMove()
{
    return model->getAIRowMove();
}

int Controller::getAIColMove()
{
    return model->getAIColMove();
}

void Controller::AIRandomMove()
{
    model->randomMove();
}

void Controller::minMaxAIMove()
{
    model->makeMinMaxMove();
}

void Controller::setAIDifficulty()
{
    model->setAIDifficulty();
}

void Controller::whoWonGame()
{
    model->whoWon();
}

bool Controller::isGameADraw()
{
    return model->getDrawnGame();
}

void Controller::resetGame()
{
    //qInfo() << "Controller reset game";
    model->resetGame();
}
