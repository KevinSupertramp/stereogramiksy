#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <iostream>
#include <exception>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void update();
    void openFile();
    void saveFile();
    bool wczytajPlik(QString);
    void resizeEvent(QResizeEvent *);
    void loadGame(QString);

    void setLabel_progres(QString tmp);
    void setStatusBar_message(QString tmp);
    Ui::MainWindow *ui;
    
private slots:


    void on_pushButton_Generate_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Koniec_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Games_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_wg_Graj_clicked();

    void on_pushButton_wg_Menu_clicked();

protected:
//    Ui::MainWindow *ui;

    QString *fileName;
    QImage *imageOrg, *imageCpy;
    QImage scaledImage;
    bool wczytano;

    /* do gry */
    QString tytulGra;
    int ileObrazkowGra;
    QStringList adresObrazkaGra;
    QStringList hasloObrazkaGra;
    int  punktyGra;
    /* koniec do gry */
};

#endif // MAINWINDOW_H
