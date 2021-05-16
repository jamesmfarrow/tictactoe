#include "dialog.h"
#include "ui_dialog.h"



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //controller = std::make_unique<Controller>(new Controller());
    //gc = std::make_unique<GameChoice>(new GameChoice);
    init();
}

Dialog::~Dialog()
{
    //delete controller;
    delete ui;
}

void Dialog::init()
{
    //use reset function to set up board and sreste variables
    reset();

    QPushButton *onePlayer{new QPushButton("1 Player Game", this)};
    QPushButton *twoPlayer{new QPushButton("2 Player Game", this)};

    ui->buttonBox->addButton(onePlayer, QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(twoPlayer, QDialogButtonBox::ButtonRole::ActionRole);

    connect(onePlayer, &QPushButton::clicked, this, &Dialog::onePlayerGame);
    connect(twoPlayer, &QPushButton::clicked, this , &Dialog::twoPlayerGame);

}

void Dialog::reset()
{
    //set the buttons on the baord disabled
    for(int i{0}; i <= 8; i++){
        buttons[i/3][i%3] = new QPushButton(this);
        buttons[i/3][i%3]->setFixedSize(QSize(150,150));
        buttons[i/3][i%3]->setDisabled(true);

        connect(buttons[i/3][i%3], &QPushButton::clicked, [=] {buttonClicked(i/3, i%3);});

        ui->gridLayout->addWidget(buttons[i/3][i%3], i/3, i%3); // add the buttons to the ui grid
    }
    controller->resetGame();//call functions in model to reset variables
}

void Dialog::buttonClicked(int row, int col)
{
    //check if clicked suqare is available, if its occupied simply return
    if(controller->squareTaken(row, col)){
        //qInfo() << "Square occupied";
        return;
    }
    else
    {
        //the space is free so update board to reflect
        controller->updateBoard(row, col);
        //player to play first
        if(controller->player1ToMove())//is it player 1 turn to move?
        {
            setPlayer1Square(row, col);
            //checkGameStatus();
            controller->whoWonGame();
            if(controller->player1HasWon()) { player1Won(); reset(); return; }
            if(controller->player2HasWon()) { player2Won(); reset(); return; }
            if(controller->isGameADraw()) { gameIsADraw(); return; }
            //none human player code placed here when human player first
            if(controller->getAIPlayer())
            {
                //randMovePlayer();
                minMaxMove();
                return;
            }
        }
        else
        {
            //player 2 play first, check if AI player is true(minmax move) otherwise its a human move
            if(controller->getAIPlayer())
            {
                //randMovePlayer();
                minMaxMove();
                return;
            }
            setPlayer2Square(row, col);
            //checkGameStatus();
            controller->whoWonGame();
            if(controller->player1HasWon()) { player1Won(); reset(); return; }
            if(controller->player2HasWon()) { player2Won(); reset(); return; }
            if(controller->isGameADraw()) { gameIsADraw(); return; }
        }
    }
}

//update the GUI to show player 1 move
void Dialog::setPlayer1Square(int row, int col)
{
    QPixmap pixmap(":/files/resources/420-4201654_png-file-svg-tic-tac-toe-cross-clipart.png.jpeg");
    QIcon ButtonIcon(pixmap);
    buttons[row][col]->setIcon(ButtonIcon);
    buttons[row][col]->setIconSize(QSize(120, 120));
    controller->setPlayer1ToMove(false);//toggled true/false depending on who's turn
}

//update gui to show player 2 move
void Dialog::setPlayer2Square(int row, int col)
{
    QPixmap pixmap(":/files/resources/circle.png");
    QIcon ButtonIcon(pixmap);
    buttons[row][col]->setIcon(ButtonIcon);
    buttons[row][col]->setIconSize(QSize(120, 120));
    controller->setPlayer1ToMove(true);//toggled true/false depending on who's turn
}

void Dialog::AIDifficulty()
{
    //ask the user if computer is to play easy or hard
    QMessageBox::StandardButton btn{QMessageBox::question(this, "First Move", "Computer player set to level hard?")};
    if(btn == QMessageBox::StandardButton::Yes){
        controller->setAIDifficulty();
    }
}

void Dialog::checkGameStatus()
{
    controller->whoWonGame();
    if(controller->player1HasWon()) { player1Won(); reset(); return; }
    if(controller->player2HasWon()) { player2Won(); reset(); return; }
    if(controller->isGameADraw()) { gameIsADraw(); return; }
}

void Dialog::player1Won()
{
    QMessageBox::information(this, "player1", "Player 1(X) has won the game");
}

void Dialog::player2Won()
{
    QMessageBox::information(this, "player2", "Player 2(O) has won the game");
}

void Dialog::gameIsADraw()
{
    QMessageBox::information(this, "Draw", "Game is a draw - nobody has won!");
}

//here 1 player game clicked
void Dialog::onePlayerGame()
{
    reset();
    for(int i{0}; i <= 8; i++){
        buttons[i/3][i%3]->setEnabled(true);
    }

    controller->setOnePlayerGame();
    controller->setAIPlayer(true);
    AIDifficulty();
    player1FirstMove();//ask if player 1 wants to go first

}

//two player game clicked
void Dialog::twoPlayerGame()
{
    reset();
    for(int i{0}; i <= 8; i++){
        buttons[i/3][i%3]->setEnabled(true);
    }

    controller->setTwoPlayerGame();
    controller->setAIPlayer(false);
    player1FirstMove();//ask if player 1 wants to go first

}

void Dialog::player1FirstMove()
{

    QMessageBox::StandardButton btn{QMessageBox::question(this, "First Move", "Player 1(X) to take first move?")};
    if(btn == QMessageBox::StandardButton::Yes)
    {
        controller->setPlayer1FirstMove(true);//yes player 1 takes first move
    }
    else
    {
        controller->setPlayer1FirstMove(false);//no player 1 plays second
        if(controller->getAIPlayer())//check to see if AI player is in play and if so then make a move
        {
            //randMovePlayer();
            minMaxMove();
        }
    }



    /*gc->exec();
    if(controller->getAIPlayer())//check to see if AI player is in play and if so then make a move
    {
        //randMovePlayer();
        minMaxMove();
    }
    */


}

void Dialog::minMaxMove()
{
    controller->minMaxAIMove();//call the minmax function
    //extract row/col from model minmax will not return an occupied square
    int minMaxRow{controller->getAIRowMove()};
    int minMaxCol{controller->getAIColMove()};
    controller->updateBoard(minMaxRow, minMaxCol);
    setPlayer2Square(minMaxRow, minMaxCol);
    //checkGameStatus();
    controller->whoWonGame();
    if(controller->player1HasWon()) { player1Won(); reset(); return; }
    if(controller->player2HasWon()) { player2Won(); reset(); return; }
    if(controller->isGameADraw()) { gameIsADraw(); return; }
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}


/*commented out but left in just in case, minmax is computer player
void Dialog::randMovePlayer()
{
    controller->AIRandomMove();
    int randRow{controller->getAIRowMove()};
    int randCol{controller->getAIColMove()};
    controller->updateBoard(randRow, randCol);
    setPlayer2Square(randRow, randCol);
    controller->whoWonGame();
    if(controller->player1HasWon()) { player1Won(); reset(); return; }
    if(controller->player2HasWon()) { player2Won(); reset(); return; }
    if(controller->isGameADraw()) { gameIsADraw(); return; }
}
*/

