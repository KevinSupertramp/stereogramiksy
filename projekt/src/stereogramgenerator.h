#ifndef STEREOGRAMGENERATOR_H
#define STEREOGRAMGENERATOR_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QPainter>

class StereogramGenerator : public QObject
{
    Q_OBJECT
public:
        explicit    StereogramGenerator(QObject *parent = 0);
                    ~StereogramGenerator();

        inline      void setImage(QImage *img){_imageToGenerate = img;}
        inline      QImage* getImage(){return _imageGeneratedStereogram;}

        void        generate(int convex, int color=false, bool circles=false);
        void        setDefault(int DPI, double distanceBetweenEyes);

    signals:
        void        setStatusBarLabel(QString tmp);
    public slots:
        // empty

    private:
        void        drawCirclesOnImage(int maxX, int maxY);
        void        calculateImageDepth(double **imageDepth, int convex);

        int         roundSomething(double something);
        int         separateSomething(double something);

        QImage      *_imageToGenerate;
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
