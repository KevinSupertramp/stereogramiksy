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

}

bool MainWindow::wczytajPlik(QString fileName)
{
    QImage tmp;
    qDebug() << "wczytajPlik" << fileName;

    StereogramGenerator a;

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

    imageOrg = new QImage(fileName);
    imageCpy = imageOrg;
    //imageOrg->load(fileName);

    qDebug() << " 1 " << imageCpy->width() << " " << imageCpy->height();

    a.setImage(imageCpy);

    a.generate(1);

    imageCpy = a.getImage();

    scaledImage = imageCpy->scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(scaledImage,Qt::AutoColor));
    }
    //delete imageCpy;
    return true;
}
// --------------------

// -------EVENT'Y-------
void MainWindow::resizeEvent(QResizeEvent *)
{
ui->stackedWidget->setSizeIncrement(ui->centralWidget->width(),ui->centralWidget->height());
    if(wczytano)
    {

        update();
    }
}

// --------------------

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


    QFile file(":new/prefix1/lista.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {}

    QTextStream in(&file);

    while (!in.atEnd()) {
        listaGier.append(in.readLine());

         }
     model = new QStringListModel(listaGier);
     ui->listView->setModel(model);



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

    while (!in.atEnd()) {
        //listaGier.append(in.readLine());

         }
}
