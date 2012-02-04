#ifndef STEREOGRAMGENERATOR_H
#define STEREOGRAMGENERATOR_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QPainter>

/**
 * StereogramGenerator - klasa odpowiadaj�ca za generowanie stereogram�w
 * Zawiera algorytm oraz funckje pomocnicze w tworzeniu stereogramu z dostarczonego obrazka
 * Opis algorytmu znajduje si� dokumentacji.
 * @file stereogramgenerator.h
 * @note Klasa generuj�ca stereogramy
 * @see MainWindow
 */
class StereogramGenerator : public QObject
{
    Q_OBJECT
public:
        /**
         * StereogramGenerator - wst�pna inicjalizacja argument�w, konstruktor
         * Konstruktor klasy MainWindow
         * @see setDefault();
         * @see changeDefault();
         */
        explicit    StereogramGenerator(QObject *parent = 0);

        /**
         * Destruktor klasy StereogramGenerator
         */
                    ~StereogramGenerator();

        /**
         * setImage - ustawia plik, z kt�rego b�dzie tworzony stereogram
         * @param *img - przekazany obrazek do wygenerowania ( *img = *imageCpy )
         * @see getImage();
         * @see generate();
         * @return void
         */
        inline      void setImage(QImage *img){_imageToGenerate = img;}

        /**
         * getImage - zwraca wygenerowany plik ( stereogram )
         * @see setImage();
         * @see generate();
         * @return QImage - wygenerowany stereogram
         */
        inline      QImage* getImage(){return _imageGeneratedStereogram;}

        /**
         * generate - g��wna funkcja klasy StereogramGenerator, zawiera w sobie algorytm generuj�cy stereogramy oraz wywo�uje funckje pozwalaj�ce na zmian� rozmiaru, koloru, wkl�s�o�ci, rysowania pomocniczych kropek
         * @param convex - zmienna odpowiadaj�ca za "wkl�s�o��" - to czy wygenerowany obrazek b�dzie widoczny jako zwyk�y obiekt lub jako wyci�ty.
         * @param color - odpowiada za kolory w jakich ma zosta� wygenerowany stereogram
         * @param circles -  odpowiada za to czy na obrazku maj� si� pojawi� pomocnicze w zobaczeniu stereogramu k�ka
         * @param size - odpowiada za rozmiar w jakim ma by� wygenerowancy stereogram - g�ownie na potrzeby zapisu do pliku
         * @param keepAspectRatio - odpowiada za to czy obrazek po zmianie rozmiaru ma si� dopasowa� do przyj�tych poprocji czy porzuci� swoje poporcje i dopasowa� si� rozmiaru ( rozci�gn��, sp�aszczy� )
         * @see setImage();
         * @see drawCirclesOnImage();
         * @see calculateImageDepth();
         * @see roundSomething();
         * @see separateSomething();
         * @see setStatusBarLabel();
         * @return void
         */
        void        generate(int convex, int color=false, bool circles=false, int size=4, int keepAspectRatio=true);

        /**
         * setDefault - ustawia warto�ci domy�lne klasy StereogramGenerator
         * @see generate();
         * @see changeDefault();
         * @return void
         */
        void        setDefault(int DPI, double distanceBetweenEyes);

        /**
         * changeDefault - zmienia warto�ci domy�lne
         * @param currentDPI - ustawia DPI wybrane przez u�ytkownika
         * @param currentDistanceBetweenEyes - ustawia odleg�o�� mi�dzy oczay ( w calach ) wybran� przez u�ytkonika.
         * @see generate();
         * @see changeDefault();
         * @return void
         */
        void        changeDefault(int currentDPI, int currentDistanceBetweenEyes);

    signals:
        /**
         * setStatusBarLabel - sygna� wysy�any do klasy MainWindow, w kt�ra obs�uguje zmienn� ui - odpowiedzialn� za GUI
         * @param tmp - string, ci�g znak�w jaki ma si� pojawi� na status barze
         * @return void
         */
        void        setStatusBarLabel(QString tmp);
    public slots:
        // empty

    private:

        /**
         * drawCirclesOnImage - funckja rysuj�ca na obrazku pomocnicze kropki
         * ( zmienne pomagaj� okre�li� w jakim miejscu maj� si� znale�� kropki )
         * @param maxX - szeroko�� obrazka
         * @param maxY - wysoko�� obrazka
         * @see generate();
         * @see calculateImageDepth();
         * @return void
         */
        void        drawCirclesOnImage(int maxX, int maxY);

        /**
         * calculateImageDepth - funkcja oblczaj�ca "g��boko��" ( w skali szaro�ci ) pixel po pixelu
         * ( dla koloru bia�ego - 0, dla koloru czarnego - 1 )
         * @param maxX - szeroko�� obrazka
         * @param maxY - wysoko�� obrazka
         * @see generate();
         * @see drawCirclesOnImage();
         * @return void
         */
        void        calculateImageDepth(double **imageDepth, int convex);

        /**
         * roundSomething - funkcja zaokr�glaj�ca dan� liczb� ( np typu double ) do int'a
         * @param something - zmienna do zaokr�glenia
         * @see generate();
         * @see drawCirclesOnImage();
         * @return int - zwraca zaokr�glon� liczb�
         */
        int         roundSomething(double something);

//        /**
//         * separateSomething - funkcja separuj�ca ( rozdzielaj�ca ) odpowiadaj�ca pozycji something
//         * @param something - pozycja
//         * @see generate();
//         * @see roundSomething();
//         * @return int - zwraca rozdzielon� liczb�
//         */
        int         separateSomething(double something);

        QImage      *_imageToGenerate;
        QImage      *_imageCopy;
        QImage      *_imageGeneratedStereogram;
        int         _widthOfImage_X;
        int         _heightOfImage_Y;

        bool        _wygenerowano;

        double      _distanceBetweenEyes;
        double      _DPI;
        double      _depthOfField;
        int         _eyeSeparation;
        int         _farOfDots;
};

#endif // STEREOGRAMGENERATOR_H
