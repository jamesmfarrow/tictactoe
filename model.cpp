#include "model.h"

//initialise static variable outside of the class
int Model::level = 2;


Model::Model(QObject *parent) : QObject(parent)
{

}

bool Model::getOnePlayergame() const
{
    return onePlayerGame;
}

void Model::setOnePlayergame(bool value)
{
    onePlayerGame = value;
    twoPlayerGame = false;
    //if(onePlayerGame && !twoPlayerGame) qInfo() << "1 player true, 2 player false";
}

bool Model::getTwoPlayerGame() const
{
    return twoPlayerGame;
}

void Model::setTwoPlayerGame(bool value)
{
    twoPlayerGame = value;
    onePlayerGame = false;
    //if(twoPlayerGame && !onePlayerGame) qInfo() << "2 player true, 1 player false";
}

bool Model::getPlayer1FirstMove() const
{
    return player1FirstMove;
}

void Model::setPlayer1FirstMove(bool value)
{
    player1FirstMove = value;
    setPlayer1Move(value);
}

bool Model::squareTaken(int row, int col)
{
    if(board[row][col] != 0){
        return true;
    }

    return false;
}

void Model::updateBoard(int row, int col)
{
    //qInfo() << "Player1status: " << player1Move;
    if(player1Move) board[row][col] = 1;
    else board[row][col] = 2;

    numberOfTurns++;

    //qInfo() << "number of turns:" << numberOfTurns;
    if(numberOfTurns == 9) drawnGame = true;

    /*for(int i{}; i < 3; i++){
        for(int k{}; k<3; k++){
            std::cout << board[i][k] << " ";
            if(k == 2) std::cout << std::endl;
        }
    }*/
}

bool Model::getPlayer1Move() const
{
    return player1Move;
}

void Model::setPlayer1Move(bool value)
{
    player1Move = value; //this will be toggled true/false as each player takes turns
}

void Model::whoWon()
{
    //iterate through all 8 winning combinations to check for a win
    for(int i{};i < 3;i++)
    {
        //horizontal first
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if(board[i][0] == 1) { player1Won = true; player2Won = false; gameOver = true; return; }
            else if(board[i][0] == 2) { player2Won = true; gameOver = true; return; }
        }
        //now vertical
        else if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if(board[0][i] == 1) { player1Won = true; gameOver = true; return; }
            else if(board[0][i] == 2) { player2Won = true; gameOver = true; return; }
        }
    }
    //now diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0] == 1) { player1Won = true; gameOver = true; return; }
        else if(board[0][0] == 2) { player2Won = true; gameOver = true; return; }
    }
    else if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if(board[0][2] == 1) { player1Won = true; gameOver = true; return; }
        else if(board[0][2] == 2) { player2Won = true; gameOver = true; return; }
    }

}

bool Model::getPlayer1Won() const
{
    return player1Won;
}

void Model::setPlayer1Won(bool value)
{
    player1Won = value;
}

bool Model::getPlayer2Won() const
{
    return player2Won;
}

void Model::setPlayer2Won(bool value)
{
    player2Won = value;
}

void Model::resetGame()
{
    for(int row{}; row < 3; row++){
        for(int col{}; col < 3; col++){
            board[row][col] = 0;
        }
    }
    player1Won = false;
    player2Won = false;
    drawnGame = false;
    numberOfTurns = 0;
    AIRowMove = 0;
    AIColMove = 0;
    //qInfo() << "model reset game";
}

void Model::randomMove()
{
    int randrow{QRandomGenerator::global()->bounded(3)};
    int randcol{QRandomGenerator::global()->bounded(3)};
    //qInfo() << "model randomMOve() row:" << randrow << " col: " << randcol;
    //qInfo() << board[randrow][randcol];

    if(board[randrow][randcol] == 0){
        //if the square is available then move to that square
        setAIRowMove(randrow);
        setAIColMove(randcol);
    } else {
        //square occupied, recursive call to randonMove() functon
        randomMove();
    }
}

bool Model::getAIPlayer() const
{
    return AIPlayer;
}

void Model::setAIPlayer(bool value)
{
    AIPlayer = value;
}

int Model::getAIRowMove() const
{
    return AIRowMove;
}

void Model::setAIRowMove(int value)
{
    AIRowMove = value;
}

int Model::getAIColMove() const
{
    return AIColMove;
}

void Model::setAIColMove(int value)
{
    AIColMove = value;
}

bool Model::getDrawnGame() const
{
    return drawnGame;
}

void Model::setDrawnGame(bool value)
{
    drawnGame = value;
}


int Model::evalMinMax()
{
    int val{}, ev{};
    int player1{};
    int player2{};

    for(int i{}; i < 3;i++)
    {
        player1=0;
        player2=0;
        for(int j{};j < 3;j++)//3 in a row X/) +/- infinity
        {
            if(board[i][j] == 1) ++player1;
            if(board[i][j] == 2) ++player2;
        }
        ev = evalRowColMinMax(player1, player2);
        if(ev > 2 || ev < -2) return ev;
        val += ev;

        player1=0;
        player2=0;

        for(int j{};j < 3;j++)//3 in a col X/) +/- infinity
        {
            if(board[j][i] == 1) ++player1;
            if(board[j][i] == 2) ++player2;
        }

        ev = evalRowColMinMax(player1, player2);
        if(ev > 2 || ev < -2) return ev;
        val += ev;
    }

    player1=0;
    player2=0;

    for(int i=0; i< 3; i++)//major diagonal
    {
        if(board[i][i] == 1) ++player1;
        if(board[i][i] == 2) ++player2;
    }

    ev = evalRowColMinMax(player1, player2);
    if(ev > 2 || ev < -2) return ev;
    val += ev;


    player1=0;
    player2=0;
    for(int i=0; i< 3; i++)//minor diagonal
    {
        if(board[i][2-i] == 1) ++player1;
        if(board[i][2-i] == 2) ++player2;
    }

    ev = evalRowColMinMax(player1, player2);
    if(ev>2 || ev<-2) return ev;
    val += ev;

    return val;

}


int Model::evalRowColMinMax(int player1, int player2)
{
    if(player1 == 3) return -INT_MAX;
    else if(player2 == 3) return INT_MAX;
    else if(player1 == 2 && player2 == 0) return -2;
    else if (player2 == 2 && player1 == 0) return 2;
    else if(player1 == 1 && player2 == 0) return -1;
    else if(player2 == 1 && player1 == 0) return 1;


    return 0;
}


AIGameMove Model::minimax(bool maximising_player, int depth, int alpha, int beta)
{
    AIGameMove best_move;

    //check for winning situation
    bool isWin = minMaxWin();
    //check for a draw
    bool is_draw = minMaxDraw();

    if(isWin || is_draw || depth == 0)
    {
        if(isWin) { best_move.score = maximising_player ? -INT_MAX : INT_MAX; }
        else if(is_draw) { best_move.score = 0; }
        else { best_move.score = evalMinMax(); }

        return best_move;
    }

    if(maximising_player) best_move.score = -INT_MAX;
    else best_move.score = INT_MAX;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == 0)//check to see if space on board and dont forget to reset
            {
                //yes then set that space on the board to the correct maximising player
                if(maximising_player) board[i][j] = 2;
                else  board[i][j] = 1;
                //make a move using minimising player
                AIGameMove board_state = minimax(!maximising_player,depth - 1, alpha, beta);
                //which move gives best score?
                //set best_move to the best score
                if(maximising_player)
                {
                    if (board_state.score > best_move.score)
                    {
                        best_move.score = board_state.score;
                        best_move.setX(i);
                        best_move.setY(j);
                        if(best_move.score > alpha) alpha = best_move.score;
                    }
                }
                else if(board_state.score < best_move.score)
                {
                    best_move.score = board_state.score;
                    best_move.setX(i);
                    best_move.setY(j);
                    if(best_move.score < beta) beta = best_move.score;
                }
                //reset the board to original state
                board[i][j] = 0;
            }
        }
    }

    return best_move;
}

void Model::makeMinMaxMove()
{
    AIGameMove AImove;
    AImove = minimax();
    setAIRowMove(AImove.getX());
    setAIColMove(AImove.getY());
}

bool Model::minMaxDraw()
{
    //if this is true then it can't b a draw
    if (minMaxWin()) return false;

    //iterate through the board to find an unoccupied square
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)return false;
        }
    }

    //get here then it is a draw
    return true;
}

bool Model::minMaxWin()
{
    //iterate through all 8 winning combinations to check for a win
    for(int i{};i < 3;i++)
    {
        //horizontal first
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if(board[i][0] != 0) return true;
        }
        //now vertical
        else if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if(board[0][i] != 0) return true;
        }
    }

    //now diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0] != 0) return true;
    }
    else if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if(board[0][2] != 0) return true;
    }

    return false;
}

void Model::setAIDifficulty()
{
    level = 9;
}


