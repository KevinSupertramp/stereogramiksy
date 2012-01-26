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
    Ui::MainWindow *ui;
    
private slots:


    void on_pushButton_Generate_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Koniec_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Games_clicked();

    void on_pushButton_Save_clicked();

private:
    //Ui::MainWindow *ui;

    QString *fileName;
    QImage *imageOrg, *imageCpy;
    QImage scaledImage;
    bool wczytano;
};

#endif // MAINWINDOW_H
