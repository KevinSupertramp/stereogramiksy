#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stereogramgenerator.h"
#include "games.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wczytano = false;
    //imageOrg = new QImage();
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setSizeIncrement(ui->centralWidget->width(),ui->centralWidget->height());
    ui->pushButton_Save->setDisabled(true);

    connect(&a,SIGNAL(setStatusBarLabel(QString)),this,SLOT(onStatusBarChanged(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Generate_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::openFile() // dokoñczyæ openFile
{
    if(wczytano)
        delete imageOrg;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Graphic files (*.jpg *.png *.bmp);;All files (*.*)"));
    try
    {
        if (!fileName.isEmpty())
        {
           wczytano = wczytajPlik(fileName);
           ui->pushButton_Save->setDisabled(false);
        }
    }
    catch(std::exception &e)
    {
        qDebug() << "Blad openFile() ";
    }

}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as image..."), QDir::homePath(), tr("PNG Image Files (*.png)"));
    imageCpy->save(fileName, "PNG");

}

void MainWindow::update()
{
    scaledImage = imageCpy->scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(scaledImage,Qt::AutoColor));
    scaledImage = imageCpy->scaled(ui->label_game->width(),ui->label_game->height(),Qt::KeepAspectRatio);
    ui->label_game->setPixmap(QPixmap::fromImage(scaledImage,Qt::AutoColor));
}

bool MainWindow::wczytajPlik(QString fileName)
{

//    ui->statusBar->showMessage("Generowanie stereogramu");
//    setStatusBar_message("Generowanie stereogramu | proszê czekaæ");

    QImage tmp;
    qDebug() << "wczytajPlik" << fileName;

//    StereogramGenerator a;

    /* obsluga obrazkow gif */
    if(fileName.endsWith("gif")){
        int iloscKlatek,i;
        QMovie *movie = new QMovie(fileName);
        movie->jumpToFrame(0);
        iloscKlatek = movie->frameCount();
        for(i=0;i<=iloscKlatek;i++){

            imageOrg = new QImage(movie->currentImage());
            //imageOrg = new QImage(tmp);
            qDebug() << "Numer petli" << i;
            imageCpy=imageOrg;
            a.setImage(imageCpy);
            a.generate(1);
            scaledImage = imageCpy->scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
            ui->label->setPixmap(QPixmap::fromImage(scaledImage,Qt::AutoColor));
            movie->jumpToFrame(i);


            //if(i==iloscKlatek){ i=0; movie->jumpToFrame(0);}
        }

    } else {

    QFile file(fileName);



    imageOrg = new QImage(fileName);
    imageCpy = imageOrg;
    //imageOrg->load(fileName);


    setLabel_info(imageCpy->width(),imageCpy->height(),file.size(),imageCpy->allGray());

    qDebug() << " wczytano obraz o rozdzielczoœci " << imageCpy->width() << "x" << imageCpy->height();

    a.setImage(imageCpy);

    a.generate(1);

    imageCpy = a.getImage();

    scaledImage = imageCpy->scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(scaledImage,Qt::AutoColor));
    }
    //delete imageCpy;

    qDebug() << ui->statusBar->currentMessage();

    return true;
}

void MainWindow::setLabel_info(int w, int h, float size, bool allgray)
{
    QString t;
    t.append("Wczytano obraz:\n");
    t.append(QString("  rozdzielczosc: ").toUtf8());
    t.append(QString("%1").arg(w));
    t.append("x");
    t.append(QString("%1").arg(h));
    t.append("\n");
    t.append("  rozmiar pliku: ");
    QString tmp; tmp.sprintf("%.2f",(size/1024)/1024);
    t.append(tmp);
    t.append(" MB\n");
    t.append(QString("  skala szarosci: ").toUtf8());
    t.append(QString("%1").arg(allgray));

    ui->label_info->clear();
    ui->label_info->setText(t.toUtf8());
}

void MainWindow::onStatusBarChanged(QString tmp)
{
    qDebug() << "setStatusBar_message" << tmp;
    ui->statusBar->showMessage(tmp);
}

// --------------------

// -------EVENT'Y-------
void MainWindow::resizeEvent(QResizeEvent *)
{
ui->stackedWidget->setSizeIncrement(ui->centralWidget->width(),ui->centralWidget->height());
    if(wczytano || (ui->stackedWidget->currentIndex()==3))
    {

        update();
    }
}

// --------------------

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->checkState())
    {
        a.generate(1,1);
        imageCpy = a.getImage();
    }
    else
    {
        a.generate(1,0);
        imageCpy = a.getImage();
    }
    update();
}

void MainWindow::on_pushButton_Open_clicked()
{
    openFile();
}

void MainWindow::on_pushButton_Koniec_clicked()
{
    exit(1);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_Games_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    //Games *game = new Games();
    QStringList listaGier;
    QStringListModel *model;


    QFile file("gry/lista.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {}

    QTextStream in(&file);

    while (!in.atEnd()) {
        listaGier.append(in.readLine());

         }
     model = new QStringListModel(listaGier);
     ui->listView->setModel(model);
     file.close();



}

void MainWindow::on_pushButton_Save_clicked()
{
    saveFile();
}

void MainWindow::on_pushButton_wg_Graj_clicked()
{
    QModelIndex wybor = ui->listView->currentIndex();
    loadGame(wybor.data().toString());
}

void MainWindow::on_pushButton_wg_Menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::loadGame(QString gra)
{
    ui->stackedWidget->setCurrentIndex(3);
    QFile file("gry/opisy/"+gra+".txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {}
    QTextStream in(&file);
    tytulGra = in.readLine();
    ileObrazkowGra = in.readLine().toInt();

    for(int i=0;i<ileObrazkowGra;i++){
        adresObrazkaGra.append(in.readLine());
    }
    for(int i=0;i<ileObrazkowGra;i++){
        hasloObrazkaGra.append(in.readLine());
    }
    punktyGra=ktoryObrazekGra=0;
    statsGame(0);
    showGame();



}

void MainWindow::statsGame(int wygrana)
{
    if(wygrana==1) {
        punktyGra+=10;
        ui->label_game_status->setText("Dobra odpowiedz");
        } else {
        if(ktoryObrazekGra!=0) ui->label_game_status->setText("Zla odpowiedz");
        }
    ui->lineEdit_game_nazwa->setText(tytulGra);
    ui->lineEdit_game_punkty->setText(QString::number(punktyGra)+"/"+QString::number(ileObrazkowGra*10));
}

void MainWindow::showGame()
{
    StereogramGenerator a;

    imageOrg = new QImage(adresObrazkaGra.at(ktoryObrazekGra));
    imageCpy = imageOrg;
    //imageOrg->load(fileName);

    //qDebug() << " 1 " << imageCpy->width() << " " << imageCpy->height();

    a.setImage(imageCpy);

    a.generate(1);

    imageCpy = a.getImage();

    scaledImage = imageCpy->scaled(ui->label_game->width(),ui->label_game->height(),Qt::KeepAspectRatio);
    ui->label_game->setPixmap(QPixmap::fromImage(scaledImage,Qt::AutoColor));

}
void MainWindow::on_pushButton_game_Ok_clicked()
{
    int odpowiedz=0;
    if(ui->lineEdit_game_haslo->text()==hasloObrazkaGra.at(ktoryObrazekGra)) odpowiedz=1;

    statsGame(odpowiedz);
    ktoryObrazekGra++;

    if(ktoryObrazekGra<ileObrazkowGra){
        showGame();

        } else
            {
            endGame();

            }

}

void MainWindow::endGame(){
    ui->stackedWidget->setCurrentIndex(4);
    ui->lcdNumber_end_punkty->display(punktyGra);

}

void MainWindow::on_pushButton_2_end_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


/* funkcje do scenariusza */

void MainWindow::on_pushButton_Scenariusz_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_scen_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_scen_add_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Graphic files (*.jpg *.png *.bmp);;All files (*.*)"));

     QStringListModel *model;
     fileListScen.append(fileName);
     model = new QStringListModel(fileListScen);
     ui->listView_scen_file->setModel(model);

}

void MainWindow::on_pushButton_scen_dalej_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    int ilefile = fileListScen.count();
    int ilehaslo = haslaListScen.count();
    ui->lineEdit_scen2_ile->setText(QString::number(ilefile-ilehaslo));
    ui->pushButton_scen2_ok->setEnabled(false);
}

void MainWindow::on_pushButton_scen2_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_scen2_add_clicked()
{
    QStringListModel *model;
    QString haslo = ui->lineEdit_scen2_haslo->text();
    haslaListScen.append(haslo);
    model = new QStringListModel(haslaListScen);
    ui->listView_scen2_hasla->setModel(model);
    int ilefile = fileListScen.count();
    int ilehaslo = haslaListScen.count();
    ui->lineEdit_scen2_ile->setText(QString::number(ilefile-ilehaslo));
    if(ilefile-ilehaslo==0){
        ui->pushButton_scen2_add->setEnabled(false);
        ui->pushButton_scen2_ok->setEnabled(true);
        }
}

void MainWindow::on_pushButton_scen2_ok_clicked()
{
    QFile file("gry/lista.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Blad otwarcia pliku lista.txt";
        }

    QTextStream out(&file);
    QString tytul = ui->lineEdit_scen2_tytul->text();
    out <<  tytul << endl;
    file.close();

    QFile file2( "gry/opisy/"+ui->lineEdit_scen2_tytul->text()+".txt" );
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text)){ qDebug() << "Blad otwarcia pliku nowego"; }
    QTextStream out2(&file2);
    tytul=ui->lineEdit_scen2_tytul->text();
    out2 << tytul << "\n";
    int ilefile = fileListScen.count();
    out2 << ilefile << "\n";
    for(int i=0;i<ilefile;i++){
        out2 << fileListScen.at(i) << "\n";
        }
    for(int i=0;i<ilefile;i++){
        qDebug() << haslaListScen.at(i);
        out2 << haslaListScen.at(i) << "\n";
        }

    file2.close();



}
