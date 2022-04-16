#include "mainwindow.h"
#include<hakkinda.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSize screenSize = qApp->screens()[0]->size();
    boy=screenSize.height()/153.6;
    //qDebug()<<boy;
    fontsize=boy*7;
    this->setFixedSize(120*boy,120*boy);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
    this->setWindowTitle("e-uctas");
    auto appIcon = QIcon(":/icons/e-uctas.svg");
    this->setWindowIcon(appIcon);

    statusLabel=new QLabel(this);
    statusLabel->setFixedSize(this->width(),boy*5);
    statusLabel->move(0,this->height()-statusLabel->height());
    statusLabel->setText("Yeni Oyun Başlatın..");


    winplayer = new QMediaPlayer();
    winplayer->setVolume(70);
    winplayer->setMedia(QUrl::fromLocalFile("/usr/share/e-uctas/win.mp3"));

    clickplayer = new QMediaPlayer();
    clickplayer->setVolume(70);
    clickplayer->setMedia(QUrl::fromLocalFile("/usr/share/e-uctas/click.mp3"));




/**********************************************************************/
    QPixmap newhumanhumanpix(":/icons/humanhuman.svg");
    QPixmap newpchumanpix(":/icons/pchuman.svg");

    QPixmap aboutpix(":/icons/about.svg");
    QPixmap quitpix(":/icons/close.svg");

    QToolBar *toolbar = addToolBar("main toolbar");
    QAction *newgamepchuman=toolbar->addAction(QIcon(newpchumanpix), "Pc-İnsan");
    QAction *newgamehumanhuman=toolbar->addAction(QIcon(newhumanhumanpix), "İnsan-İnsan");

    QAction *hak=toolbar->addAction(QIcon(aboutpix), "Hakkında");
    toolbar->addSeparator();
    QAction *quit = toolbar->addAction(QIcon(quitpix),"Çık");
    connect( newgamepchuman, SIGNAL(triggered()), this, SLOT(newGamePcHuman()));
    connect( newgamehumanhuman, SIGNAL(triggered()), this, SLOT(newGameHumanHuman()));
    connect( hak, SIGNAL(triggered()), this, SLOT(about()));
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
//newGame();

    QPixmap pic(":/icons/e-uctas.svg");
    back=new QLabel(this);

    back->setFixedSize(this->width()-boy*20,this->width()-boy*20);
    back->move(this->width()/2-back->width()/2,this->height()/2-back->height()/2);

    back->setPixmap(pic);
    back->setScaledContents(true);


}
void   MainWindow::about(){
    QSize screenSize = qApp->screens()[0]->size();
   // qDebug()<<screenSize.width()/65<<screenSize.height()/35;

    QWidget *hk=hakkinda();

    hk->show();
    hk->move(screenSize.width()/2-hk->width()/2,screenSize.height()/2-hk->height()/2);
     hk->setWindowTitle("e-uctas");
     auto appIcon = QIcon(":/icons/about.svg");
     hk->setWindowIcon(appIcon);



}
void  MainWindow::newGamePcHuman()
{
    back->hide();
    newGameKind=true;
    gameFinishStatus=false;
    if(newGameStatus==true)
    {

        for(int i=0;i<=8;i++)
        {

                delete butonSayilarListe[i];


        }
        delete slw;

    }

    slw=sayiListeWidget();  slw->show();
     newGameStatus=true;
    statusLabel->setText("Oyun Başladı..");

    player1AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
        player1AutoSelectList.append(butonSayilarListe[j-1]->text().toInt());
    }
    currentPlayer=1;
    player1AutoSelectClick();




}

void  MainWindow::newGameHumanHuman()
{
    back->hide();
    newGameKind=false;
    gameFinishStatus=false;

    if(newGameStatus==true)
    {


        for(int i=0;i<=8;i++)
        {

                delete butonSayilarListe[i];


        }
        delete slw;

    }

    slw=sayiListeWidget();  slw->show();
      newGameStatus=true;
    statusLabel->setText("Oyun Başladı..");

    player1AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
        player1AutoSelectList.append(butonSayilarListe[j-1]->text().toInt());
    }
currentPlayer=1;//default player


}


QWidget* MainWindow::sayiListeWidget()
{
    butonSayilarListe.clear();

     addSayiListe();/// sayilar eklendi
   auto widget = new QWidget(this);
     auto layout = new QGridLayout(widget);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(0);
    //  layout->setColumnMinimumWidth(0, 37);
int radius=boy*6;
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
            QToolButton *btn=new QToolButton();
            btn->setText(QString::number(sayiSec()));
            btn->setToolTip("0");
            matrix[i][j].number=btn->text().toInt();
            matrix[i][j].player=0;
            btn->setFixedSize(boy*12,boy*12);
            connect(btn, &QToolButton::clicked, [=]() {
                if(btn->toolTip().toInt()!=0) return;
                if(gameFinishStatus==true) return;
                if(currentPlayer==1){

                   player1Click(btn->text().toInt());


                    return;
                }
                if(currentPlayer==2){

                    player2Click(btn->text().toInt());

                    if(newGameKind==true) player1AutoSelectClick();
                         return;
                }
            });

            btn->setStyleSheet("QToolButton{background-color:rgba(255,255,255,255);"
                               "color:rgba(200,200,200,0);"
                               "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                               "font-weight: 400;font-size:"+QString::number(fontsize)+"px;}");

            butonSayilarListe.append(btn);
            layout->addWidget(btn,i,j,1,1);
        }
    }
    widget->setFixedSize(80*boy-boy*2,80*boy-boy*2);
   // widget->setStyleSheet("background-color:rgba(0,200,0,50);border: 1px solid gray;border-radius: 5px;");
    widget->move(this->width()/2-widget->width()/2,this->height()/2-widget->height()/2);


    return widget;
}


void  MainWindow::player1Click(int btnnumber)
{
    if(gameFinishStatus==true) return;
    int radius=boy*6;
    clickplayer->play();//ses çalıyor
    for(int i=1;i<=9;i++)
    {
        if(btnnumber==butonSayilarListe[i-1]->text().toInt())
        {
            butonSayilarListe[i-1]->setToolTip(QString::number(currentPlayer));
            matrixMarker(butonSayilarListe[i-1]->text().toInt(),currentPlayer);
            butonSayilarListe[i-1]->setStyleSheet("background-color:rgba(0,0,200,100);"
            "color:rgba(200,200,200,0);"
            "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
            "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");

            butonSayilarListe[i-1]->setIconSize(QSize(butonSayilarListe[i-1]->width(),butonSayilarListe[i-1]->height()));
            butonSayilarListe[i-1]->setIcon(QIcon(":/icons/blue.png"));

        }

    }
    player1WinControl();
    currentPlayer=2;



}
void  MainWindow::player2Click(int btnnumber)
{
    if(gameFinishStatus==true) return;
    int radius=boy*6;
    clickplayer->play();//ses çalıyor
    for(int i=1;i<=9;i++)
    {
        if(btnnumber==butonSayilarListe[i-1]->text().toInt())
        {
            butonSayilarListe[i-1]->setToolTip(QString::number(currentPlayer));
            matrixMarker(butonSayilarListe[i-1]->text().toInt(),currentPlayer);
            butonSayilarListe[i-1]->setStyleSheet("background-color:rgba(200,0,0,100);"
                                                   "color:rgba(200,200,200,0);"
                                                  "border: 1px solid gray;border-radius: "+QString::number(radius)+"px;"
                                                                                                                   "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
            butonSayilarListe[i-1]->setIconSize(QSize(butonSayilarListe[i-1]->width(),butonSayilarListe[i-1]->height()));
            butonSayilarListe[i-1]->setIcon(QIcon(":/icons/red.png"));

        }

    }
    player2WinControl();
    currentPlayer=1;

}

void MainWindow::player1AutoSelectClick()
{
    // player1Click(5);
    player1AutoSelectList.clear();
    for(int j=1;j<=9;j++)
    {
       if(butonSayilarListe[j-1]->toolTip()=="0")
       player1AutoSelectList.append(butonSayilarListe[j-1]->text().toInt());
    }

     srand (time(NULL));
     int randomNumber = rand() % player1AutoSelectList.count() + 1;//1-9 random size sayiListe.count()=36
    // qDebug()<<"auto select player1 number:"<<randomNumber<<player1AutoSelectList.count()<<player1AutoSelectList<<player1AutoSelectList[randomNumber-1];
    // player1Click(player1[player1AutoSelectList[randomNumber-1]-1]->text().toInt());
     //  player1Click(5);
     for(int i=0;i<9;i++)
     {
      if(butonSayilarListe[i]->text().toInt()==player1AutoSelectList[randomNumber-1])
      {
          //player1AutoSelectList.removeAt(i);
         // qDebug()<<"auto select player1 number:"<<player1[i]->text().toInt();
           player1Click(butonSayilarListe[i]->text().toInt());
      }
     }
}
void MainWindow::addSayiListe()
{
    sayiListe.append(1); sayiListe.append(2); sayiListe.append(3); sayiListe.append(4);
    sayiListe.append(5); sayiListe.append(6); sayiListe.append(7); sayiListe.append(8);
    sayiListe.append(9);
    sayiListe1=sayiListe;
}

int MainWindow::sayiSec()
{
    srand (time(NULL));
    int randomNumber = rand() % sayiListe.count() + 1;//1-36 random size sayiListe.count()=36
   // qDebug()<<"rastgelesayi"<<randomNumber<<sayiListe.count();
    int temp=sayiListe[randomNumber-1];
    sayiListe.removeAt(randomNumber-1);
    return temp;
}


void MainWindow::matrixMarker(int number,int player)
{
   for(int i=0;i<=2;i++)
   {
       for(int j=0;j<=2;j++)
       {

           if(matrix[i][j].number==number)
           {
               matrix[i][j].player=player;
              /// qDebug()<<matrix[i][j].number<<matrix[i][j].player;
           }
       }

   }
}
void MainWindow::player1WinControl()
 {
    int player=1;
     bool status=false;
    for(int i=1;i<=1;i++)
    {
        for(int j=1;j<=1;j++)
        {
            //ust-orta-alt
           if(matrix[i][j].player==matrix[i-1][j].player&&
                   matrix[i][j].player==matrix[i+1][j].player&&
                   matrix[i][j].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][j].number,matrix[i-1][j].number,matrix[i+1][j].number,player);
           }
            //ustsol-orta-altsag
           if(matrix[i][j].player==matrix[i-1][j-1].player&&
                   matrix[i][j].player==matrix[i+1][j+1].player&&
                   matrix[i][j].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][j].number,matrix[i-1][j-1].number,matrix[i+1][j+1].number,player);
           }
             //ustsag-orta-altsol
           if(matrix[i][j].player==matrix[i-1][j+1].player&&
                   matrix[i][j].player==matrix[i+1][j-1].player&&
                   matrix[i][j].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][j].number,matrix[i-1][j+1].number,matrix[i+1][j-1].number,player);
           }
            //sag-orta-sol
          if(matrix[i][j].player==matrix[i][j+1].player&&
                  matrix[i][j].player==matrix[i][j-1].player&&
                  matrix[i][j].player!=0)
          {
              status=true;
              buttonWinMarker(matrix[i][j].number,matrix[i][j+1].number,matrix[i][j-1].number,player);
          }

                  // qDebug()<<matrix[i][j];
        }

    }

    for(int i=1;i<=1;i++)
    {

            //sol dik
           if(matrix[i][0].player==matrix[i-1][0].player&&
                   matrix[i][0].player==matrix[i+1][0].player&&
                   matrix[i][0].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][0].number,matrix[i-1][0].number,matrix[i+1][0].number,player);
           }
      }
    for(int i=1;i<=1;i++)
    {

            //sağ dik
           if(matrix[i][2].player==matrix[i-1][2].player&&
                   matrix[i][2].player==matrix[i+1][2].player&&
                   matrix[i][2].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[i][2].number,matrix[i-1][2].number,matrix[i+1][2].number,player);
           }
      }
    for(int i=1;i<=1;i++)
    {

            //ust yatay
           if(matrix[0][i].player==matrix[0][i-1].player&&
                   matrix[0][i].player==matrix[0][i+1].player&&
                   matrix[0][i].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[0][i].number,matrix[0][i-1].number,matrix[0][i+1].number,player);
           }
      }
    for(int i=1;i<=1;i++)
    {

            //alt yatay
           if(matrix[2][i].player==matrix[2][i-1].player&&
                   matrix[2][i].player==matrix[2][i+1].player&&
                   matrix[2][i].player!=0)
           {
               status=true;
               buttonWinMarker(matrix[2][i].number,matrix[2][i-1].number,matrix[2][i+1].number,player);
           }
      }

    if(status)
    {
       /* QMessageBox msgBox;
        msgBox.setText("Tebrikler MAVİ Oyuncu Oyunu Kazandınız"
                       "\n\nYeni Oyuna Devam Etmek İstiyor Musunuz?");
         msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Çarpanga Oyunu !");
       // QPixmap icon(":/icons/bell.svg");
        //msgBox.setWindowIcon(icon);
        QAbstractButton *tamamButton;
       // QAbstractButton *hayirButton;

       tamamButton =msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
       //hayirButton =msgBox.addButton(tr("Hayır"), QMessageBox::ActionRole);

           msgBox.exec();*/
           statusLabel->setText("Oyunu MAVİ Oyuncu Kazandı..");
           gameFinishStatus=true;///oyun bitti
          /* if(msgBox.clickedButton()==evetButton)
           {
           // qDebug()<<"devam";
               newGame();
           }*/
    }
 }

void MainWindow::player2WinControl()
 {

       int player=2;
        bool status=false;
        for(int i=1;i<=1;i++)
        {
            for(int j=1;j<=1;j++)
            {
                //ust-orta-alt
               if(matrix[i][j].player==matrix[i-1][j].player&&
                       matrix[i][j].player==matrix[i+1][j].player&&
                       matrix[i][j].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[i][j].number,matrix[i-1][j].number,matrix[i+1][j].number,player);
               }
                //ustsol-orta-altsag
               if(matrix[i][j].player==matrix[i-1][j-1].player&&
                       matrix[i][j].player==matrix[i+1][j+1].player&&
                       matrix[i][j].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[i][j].number,matrix[i-1][j-1].number,matrix[i+1][j+1].number,player);
               }
                 //ustsag-orta-altsol
               if(matrix[i][j].player==matrix[i-1][j+1].player&&
                       matrix[i][j].player==matrix[i+1][j-1].player&&
                       matrix[i][j].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[i][j].number,matrix[i-1][j+1].number,matrix[i+1][j-1].number,player);
               }
                //sag-orta-sol
              if(matrix[i][j].player==matrix[i][j+1].player&&
                      matrix[i][j].player==matrix[i][j-1].player&&
                      matrix[i][j].player!=0)
              {
                  status=true;
                  buttonWinMarker(matrix[i][j].number,matrix[i][j+1].number,matrix[i][j-1].number,player);
              }

                      // qDebug()<<matrix[i][j];
            }

        }

        for(int i=1;i<=1;i++)
        {

                //sol dik
               if(matrix[i][0].player==matrix[i-1][0].player&&
                       matrix[i][0].player==matrix[i+1][0].player&&
                       matrix[i][0].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[i][0].number,matrix[i-1][0].number,matrix[i+1][0].number,player);
               }
          }
        for(int i=1;i<=1;i++)
        {

                //sağ dik
               if(matrix[i][2].player==matrix[i-1][2].player&&
                       matrix[i][2].player==matrix[i+1][2].player&&
                       matrix[i][2].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[i][2].number,matrix[i-1][2].number,matrix[i+1][2].number,player);
               }
          }
        for(int i=1;i<=1;i++)
        {

                //ust yatay
               if(matrix[0][i].player==matrix[0][i-1].player&&
                       matrix[0][i].player==matrix[0][i+1].player&&
                       matrix[0][i].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[0][i].number,matrix[0][i-1].number,matrix[0][i+1].number,player);
               }
          }
        for(int i=1;i<=1;i++)
        {

                //alt yatay
               if(matrix[2][i].player==matrix[2][i-1].player&&
                       matrix[2][i].player==matrix[2][i+1].player&&
                       matrix[2][i].player!=0)
               {
                   status=true;
                   buttonWinMarker(matrix[2][i].number,matrix[2][i-1].number,matrix[2][i+1].number,player);
               }
          }



     if(status)
    {
     /*   QMessageBox msgBox;
        msgBox.setText("Tebrikler KIRMIZI Oyuncu Oyunu Kazandınız"
                       "\n\nYeni Oyuna Devam Etmek İstiyor Musunuz?");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Çarpanga Oyunu !");
       // QPixmap icon(":/icons/bell.svg");
        //msgBox.setWindowIcon(icon);
        QAbstractButton *tamamButton;
        //QAbstractButton *hayirButton;

       tamamButton =msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
      // hayirButton =msgBox.addButton(tr("Hayır"), QMessageBox::ActionRole);

           msgBox.exec();
           */
        statusLabel->setText("Oyunu KIRMIZI Oyuncu Kazandı..");

           gameFinishStatus=true;///oyun bitti

          /* if(msgBox.clickedButton()==evetButton)
           {
            //qDebug()<<"devam";
               newGame();
           }*/
    }
 }

void MainWindow::buttonWinMarker(int a1,int a2,int a3,int player)
{
    int radius=boy*6;
   // qDebug()<<"kazanan sayılar"<<a1<<a2<<a3<<player;
    if(player=1)
    {
        for(int i=0;i<butonSayilarListe.count();i++)
        {
            if(butonSayilarListe[i]->text().toInt()==a1&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,255,255);"
                                                    "border: 3px solid green;border-radius: "+QString::number(radius)+"px;"
               "color:rgba(200,200,200,0);"
              "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
                butonSayilarListe[i]->setIconSize(QSize(butonSayilarListe[i]->width(),butonSayilarListe[i]->height()));
                butonSayilarListe[1]->setIcon(QIcon(":/icons/blue.png"));

            }
            if(butonSayilarListe[i]->text().toInt()==a2&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,255,255);"
                                                      "color:rgba(200,200,200,0);"
                                                    "border: 3px solid green;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
                butonSayilarListe[i]->setIconSize(QSize(butonSayilarListe[i]->width(),butonSayilarListe[i]->height()));
                butonSayilarListe[1]->setIcon(QIcon(":/icons/blue.png"));

            }
            if(butonSayilarListe[i]->text().toInt()==a3&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(0,0,200,255);"
                                                      "color:rgba(200,200,200,0);"
                                                    "border: 3px solid green;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
                butonSayilarListe[i]->setIconSize(QSize(butonSayilarListe[i]->width(),butonSayilarListe[i]->height()));
                butonSayilarListe[1]->setIcon(QIcon(":/icons/blue.png"));

            }
        }

    }

    if(player=2)
    {
        for(int i=0;i<butonSayilarListe.count();i++)
        {
            if(butonSayilarListe[i]->text().toInt()==a1&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(255,0,0,255);"
                                                      "color:rgba(200,200,200,0);"
                                                    "border: 3px solid green;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
                butonSayilarListe[i]->setIconSize(QSize(butonSayilarListe[i]->width(),butonSayilarListe[i]->height()));
                butonSayilarListe[1]->setIcon(QIcon(":/icons/red.png"));

            }
            if(butonSayilarListe[i]->text().toInt()==a2&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(255,0,0,255);"
                                                      "color:rgba(200,200,200,0);"
                                                    "border: 3px solid green;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
                butonSayilarListe[i]->setIconSize(QSize(butonSayilarListe[i]->width(),butonSayilarListe[i]->height()));
                butonSayilarListe[1]->setIcon(QIcon(":/icons/red.png"));
            }
            if(butonSayilarListe[i]->text().toInt()==a3&&butonSayilarListe[i]->toolTip().toInt()==player)
            {

                butonSayilarListe[i]->setStyleSheet("background-color:rgba(255,0,0,255);"
                                                      "color:rgba(200,200,200,0);"
                                                    "border: 3px solid green;border-radius: "+QString::number(radius)+"px;"
                                                    "font-weight: 400;font-size:"+QString::number(fontsize)+"px;");
                butonSayilarListe[i]->setIconSize(QSize(butonSayilarListe[i]->width(),butonSayilarListe[i]->height()));
                butonSayilarListe[1]->setIcon(QIcon(":/icons/red.png"));
            }
        }

    }
     winplayer->play();


}
MainWindow::~MainWindow()
{

}
