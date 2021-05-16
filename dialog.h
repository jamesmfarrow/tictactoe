#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>


#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setPlayer1Square(int row, int col);
    void setPlayer2Square(int row, int col);

    void player1Won();
    void player2Won();
    void gameIsADraw();

    void randMovePlayer();
    void minMaxMove();
    void AIDifficulty();
    void checkGameStatus();


private slots:
    void buttonClicked(int row, int col);
    void onePlayerGame();
    void twoPlayerGame();
    void player1FirstMove();
    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    QPushButton *buttons[3][3];
    //Controller *controller{new Controller(this)};
    std::unique_ptr<Controller> controller{std::make_unique<Controller>(new Controller())};
    //GameChoice *gc{new GameChoice(this)};
    //std::unique_ptr<Controller> controller;
    //std::unique_ptr<GameChoice> gc;
    bool AIGame{false};
    void init();
    void reset();
};
#endif // DIALOG_H
