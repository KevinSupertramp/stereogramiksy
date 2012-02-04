/**
 *  @mainpage
 *  @par Stereogramiksy
 *  @author Micha� Franczyk, Micha� Golonka, Szymon Jagie�a
 *  @date 2012.02.04
 *  @version 1.1
 *  @par program wykorzystuje biblioteke Qt
 *  @brief Program do generowania stereogram�w.
 *
 *      Generator Stereorgam�w.
 *         - Program do generowania stereogram�w, umo�liwia edycj� ustawie� generowania:
 *              -# rozstaw oczu
 *              -# DPI ekranu
 *              -# zmiana koloru bia�ego na inny ( do wyboru kilka )
 *              -# dodanie pomocniczych kropek na obrazek
 *              -# zapis obrazka do wybranego formatu oraz wybranej rozdzielczo�ci
 *              -# zmian� ustawie� dopasowania do okna
 *
 *         - Program wy�wietla r�wnie� podstawowe informacje o:
 *              -# rozdzielczo�ci pliku
 *              -# podaje informacje czy obrazek jest w skali szaro�ci
 *              -# rozmiar wczytanego pliku w MB
 *
 *      Gra - zgadnij ( zobacz ) co jest na stereogramie
 *         - Program umo�liwia tryb gry;
 *              -# mo�na gra� w dost�pne w li�cie gier gry
 *              -# trzeba odpowiedzie� na zadane pytanie, je�li odpowied� b�dzie poprawna dostaniemy za to punkty
 *              -# je�li poszczeg�lna gra sk�ada si� z wi�cej ni� jeden, poziom�w - wtedy mo�na usyzka� wi�cej ni� 10 punkt�w.
 *                  I zostaniemy automatycznie przeniesieni do nowego poziomu.
 *         - Pogram umo�liwia tryb - stw�rz scenariusz
 *              -# mo�emy zrobi� w�asny poziom gry
 *              -# mo�e on by� dowolnie skomplikowany
 *              -# wszystko jest zapisywane do pliku - dlatego �atwo podzieli� si� p�niej dan� gr� ze znajomymi
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringListModel>

#include "stereogramgenerator.h"

/**
 * Ui - namespace - do u�ywania obiekt�w stworzonych za pomoc� Designer'a w QtCreatorze
 * @see mainwindow.ui
 * @see MainWindow
 */
namespace Ui
{
    class MainWindow;
}

/**
 * Main Window - G��wna Klasa .
 * Klasa, kontroluj�ca wszelkie dzia�ania aplikacji.
 * @note MainWindow musi dzia�a�.
 * @file mainwindow.h
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    /**
     * MainWindow - r�czne dodawanie/ustawianie element�w.
     * Konstruktor klasy MainWindow
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Destruktor klasy MainWindow
     */
    ~MainWindow();

private slots:
    void setLabel_info(int w, int h, float size, bool allgray);

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

    void on_pushButton_Oprogramie_clicked();

    void on_pushButton_oprogramie_menu_clicked();

    void on_comboBox_DPI_activated(int index);

    void on_comboBox_RozstawOczu_activated(int index);

    void on_checkBox_wkleslosc_clicked();

    void on_checkBox_dopasujDoOkna_clicked();

private:
    /**
     * update - od�wie�aj�ca okienko - dopasowuje rozmiar wczytanego, a nast�pnie wygenerowanego pliku ( stereogramu )
     * @param dopasuj - czy obrazek ma by� dopasowany do okna ( domy�lan warto�� - tak )
     * @see openFile();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void update(bool dopasuj=true);

    /**
     * openFile - okienko dialogowe do wyboru pliku.
     * @see wczytajPlik();
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @return void
     */
    void openFile();

    /**
     * saveFile - zapisuje plik ( stereogram ) - w okre�lonej rozdzielczo�ci, wybranym rozszerzeniem oraz innymi ustawieniami
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void saveFile();

    /**
     * wczytajPlik - metoda wczytuj�ca obrazek
     * @param fileName - string nazwy pliku.
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return bool
     */
    bool wczytajPlik(QString fileName);

    /**
     * resizeEvent - event odpowiadaj�cy za updatowanie rozmiaru obrazka
     * @param event - rozszerzenie obrazka
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void resizeEvent(QResizeEvent *);


    /**
     * setElementsDisabled - pozwala na �atwe "w��czanie" lub "wy��czanie" element�w
     * @param disabled - czy dane elementy maj� by� w��czone b�d� nie
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void setElementsDisabled(bool disabled);

    /**
      * Zmienna *ui - pozwala si� odwo�ywa� do obiekt�w stworzonych przez Designer'a
      * Zmienna prywatna.
      */
    Ui::MainWindow *ui;

    /**
      * Zmienna *fileName - wczytuje �cie�k� dost�pu do pliku oraz jego nazw�.
      * Zmienna prywatna.
      */
    QString *fileName;

    /**
      * Zmienna *imageOrg - wczytany oryginalny obrazek
      * Zmienna prywatna.
      */
    QImage *imageOrg;

    /**
      * Zmienna *imageCpy - na pocz�tku przechowuje kopi� imageOrg a potem sam stereogram.
      * Zmienna prywatna.
      */
    QImage *imageCpy;

    /**
      * Zmienna *imageToSave - przechowuje obrazek gotowy do zapisania.
      * Zmienna prywatna.
      */
    QImage *imageToSave;

    /**
      * Zmienna scaledImage - przechowuje kopi� imageCpy - odpowiednio dopasowan� do rozmiaru okna
      * Zmienna prywatna.
      */
    QImage scaledImage;

    /**
      * Zmienna wczytano - na wej�ciu false, po wygenerowaniu true | pomaga w optymalizacji zu�ycia pami�ci
      * Zmienna prywatna.
      */
    bool wczytano;


    /**
      * Zmienna _stereogramGenerator - obiekt klasy StereogramGenerator - odpowiedzialny za obs�ug� generowania stereogramu
      * Zmienna prywatna.
      */
    StereogramGenerator _stereogramGenerator;



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


    /* funkcje do gry */
    void loadGame(QString);
    void statsGame(int);
    void showGame();
    void endGame();

};

#endif // MAINWINDOW_H
