#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <iostream>
#include <exception>

#include "stereogramgenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    StereogramGenerator a;

    void update();
    void openFile();
    void saveFile();
    bool wczytajPlik(QString);
    void resizeEvent(QResizeEvent *);
    /* funkcje do gry */
    void loadGame(QString);
    void statsGame(int);
    void showGame();
    void endGame();

    void setLabel_info(int w, int h, float size, bool allgray);
//    void setStatusBar_message(QString tmp);
    Ui::MainWindow *ui;
    
private slots:

    void onStatusBarChanged(QString tmp);

    void on_pushButton_Generate_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Koniec_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Games_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_wg_Graj_clicked();

    void on_pushButton_wg_Menu_clicked();


    void on_pushButton_game_Ok_clicked();

    void on_pushButton_2_end_menu_clicked();
    void on_checkBox_clicked();

    void on_pushButton_Scenariusz_clicked();

    void on_pushButton_scen_menu_clicked();

    void on_pushButton_scen_add_clicked();

    void on_pushButton_scen_dalej_clicked();

    void on_pushButton_scen2_menu_clicked();

    void on_pushButton_scen2_add_clicked();

    void on_pushButton_scen2_ok_clicked();

    void on_comboBox_activated(int index);

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
    int ktoryObrazekGra;
    /* koniec do gry */
    /* generator scenariuszy */
    QStringList fileListScen;
    QStringList haslaListScen;
    /*koniec generator scenariuszy */
};

#endif // MAINWINDOW_H
