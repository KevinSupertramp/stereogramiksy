/**
 *  @mainpage
 *  @par Stereogramiksy
 *  @author Micha³ Franczyk, Micha³ Golonka, Szymon Jagie³a
 *  @date 2012.02.04
 *  @version 1.1
 *  @par program wykorzystuje biblioteke Qt
 *  @brief Program do generowania stereogramów.
 *
 *      Generator Stereorgamów.
 *         - Program do generowania stereogramów, umo¿liwia edycjê ustawieñ generowania:
 *              -# rozstaw oczu
 *              -# DPI ekranu
 *              -# zmiana koloru bia³ego na inny ( do wyboru kilka )
 *              -# dodanie pomocniczych kropek na obrazek
 *              -# zapis obrazka do wybranego formatu oraz wybranej rozdzielczoœci
 *              -# zmianê ustawieñ dopasowania do okna
 *
 *         - Program wyœwietla równie¿ podstawowe informacje o:
 *              -# rozdzielczoœci pliku
 *              -# podaje informacje czy obrazek jest w skali szaroœci
 *              -# rozmiar wczytanego pliku w MB
 *
 *      Gra - zgadnij ( zobacz ) co jest na stereogramie
 *         - Program umo¿liwia tryb gry;
 *              -# mo¿na graæ w dostêpne w liœcie gier gry
 *              -# trzeba odpowiedzieæ na zadane pytanie, jeœli odpowiedŸ bêdzie poprawna dostaniemy za to punkty
 *              -# jeœli poszczególna gra sk³ada siê z wiêcej ni¿ jeden, poziomów - wtedy mo¿na usyzkaœ wiêcej ni¿ 10 punktów.
 *                  I zostaniemy automatycznie przeniesieni do nowego poziomu.
 *         - Pogram umo¿liwia tryb - stwórz scenariusz
 *              -# mo¿emy zrobiæ w³asny poziom gry
 *              -# mo¿e on byæ dowolnie skomplikowany
 *              -# wszystko jest zapisywane do pliku - dlatego ³atwo podzieliæ siê póŸniej dan¹ gr¹ ze znajomymi
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringListModel>

#include "stereogramgenerator.h"

/**
 * Ui - namespace - do u¿ywania obiektów stworzonych za pomoc¹ Designer'a w QtCreatorze
 * @see mainwindow.ui
 * @see MainWindow
 */
namespace Ui
{
    class MainWindow;
}

/**
 * Main Window - G³ówna Klasa .
 * Klasa, kontroluj¹ca wszelkie dzia³ania aplikacji.
 * @note MainWindow musi dzia³aæ.
 * @file mainwindow.h
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    /**
     * MainWindow - rêczne dodawanie/ustawianie elementów.
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
     * update - odœwie¿aj¹ca okienko - dopasowuje rozmiar wczytanego, a nastêpnie wygenerowanego pliku ( stereogramu )
     * @param dopasuj - czy obrazek ma byæ dopasowany do okna ( domyœlan wartoœæ - tak )
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
     * saveFile - zapisuje plik ( stereogram ) - w okreœlonej rozdzielczoœci, wybranym rozszerzeniem oraz innymi ustawieniami
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void saveFile();

    /**
     * wczytajPlik - metoda wczytuj¹ca obrazek
     * @param fileName - string nazwy pliku.
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return bool
     */
    bool wczytajPlik(QString fileName);

    /**
     * resizeEvent - event odpowiadaj¹cy za updatowanie rozmiaru obrazka
     * @param event - rozszerzenie obrazka
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void resizeEvent(QResizeEvent *);


    /**
     * setElementsDisabled - pozwala na ³atwe "w³¹czanie" lub "wy³¹czanie" elementów
     * @param disabled - czy dane elementy maj¹ byæ w³¹czone b¹dŸ nie
     * @see update();
     * @see saveFile();
     * @see resizeEvent();
     * @see wczytajPlik();
     * @return void
     */
    void setElementsDisabled(bool disabled);

    /**
      * Zmienna *ui - pozwala siê odwo³ywaæ do obiektów stworzonych przez Designer'a
      * Zmienna prywatna.
      */
    Ui::MainWindow *ui;

    /**
      * Zmienna *fileName - wczytuje œcie¿kê dostêpu do pliku oraz jego nazwê.
      * Zmienna prywatna.
      */
    QString *fileName;

    /**
      * Zmienna *imageOrg - wczytany oryginalny obrazek
      * Zmienna prywatna.
      */
    QImage *imageOrg;

    /**
      * Zmienna *imageCpy - na pocz¹tku przechowuje kopiê imageOrg a potem sam stereogram.
      * Zmienna prywatna.
      */
    QImage *imageCpy;

    /**
      * Zmienna *imageToSave - przechowuje obrazek gotowy do zapisania.
      * Zmienna prywatna.
      */
    QImage *imageToSave;

    /**
      * Zmienna scaledImage - przechowuje kopiê imageCpy - odpowiednio dopasowan¹ do rozmiaru okna
      * Zmienna prywatna.
      */
    QImage scaledImage;

    /**
      * Zmienna wczytano - na wejœciu false, po wygenerowaniu true | pomaga w optymalizacji zu¿ycia pamiêci
      * Zmienna prywatna.
      */
    bool wczytano;


    /**
      * Zmienna _stereogramGenerator - obiekt klasy StereogramGenerator - odpowiedzialny za obs³ugê generowania stereogramu
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
