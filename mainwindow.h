#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include<QSize>
#include<QToolButton>
#include<QScreen>
#include<QDebug>
#include<QLabel>
#include<QGridLayout>
#include<QWidget>
#include "QDateTime"
#include<random>
#include<QMessageBox>
#include<QPushButton>
#include<QToolBar>
#include<QFile>
#include<QMediaPlayer>
#include<QMediaContent>
class mx
{
public:
    int number;
    int player;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int sayiSec();
    void  addSayiListe();
    QWidget  *addPlayer1();
    QWidget  *addPlayer2();
    QWidget  *sayiListeWidget();
    void player1WinControl();
    void player2WinControl();
    void matrixMarker(int number, int player);

public slots:
    void about();
    void newGamePcHuman();
     void newGameHumanHuman();
    void player1Click(int btnnumber);
    void player2Click(int btnnumber);
    void player1AutoSelectClick();
    void buttonWinMarker(int a1, int a2, int a3, int player);
private:
    int boy;
    QList<int> sayiListe,sayiListe1;
    QList<QToolButton*> butonSayilarListe;
    QList<QToolButton*> player1;
    QList<QToolButton*> player2;
    QList<int> player1AutoSelectList;
    QList<int> player2AutoSelectList;

    QLabel *statusLabel;
   // QWidget *sayiListeWidget;
    QWidget *player2ListeWidget;
    QWidget *player1ListeWidget;
    QWidget *hakkinda();
    QGridLayout *mLayout;
    int selectNumberPlayer1=0;
    int selectNumberPlayer2=0;
    QWidget *slw;
     mx matrix[6][6];
    bool newGameStatus=false;
    bool gameFinishStatus=false;
    bool newGameKind=false;
    QLabel *back;
    QMediaPlayer* clickplayer;
    QMediaPlayer* winplayer;
   int fontsize=25;
   int currentPlayer=0;


};

#endif // MAINWINDOW_H
