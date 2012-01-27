#ifndef STEREOGRAMGENERATOR_H
#define STEREOGRAMGENERATOR_H

#include<iostream>
#include<QtGui>

class StereogramGenerator : public QObject
{
    Q_OBJECT
public:
        explicit StereogramGenerator(QObject *parent = 0);

//        StereogramGenerator();
        ~StereogramGenerator();

        inline void setImage(QImage *img){imageOrg = img;}
        inline QImage* getImage(){return imageStereogram;}

        void generate(int convex, bool circles=false);
        void drawCirclesOnImage(int maxX, int maxY);

        void CalculateImageDepth(QVector<QVector<double> > &imageDepth, int convex); //(between 0 and 1)

    signals:
        void setStatusBarLabel(QString tmp);
    public slots:

    private:
        QPixmap     *originalPixelmap;
        QImage      *imageOrg;
        QImage      *imageOrgCpy;
        QImage      *imageStereogram;
        QImage      *tmp;
};

#endif // STEREOGRAMGENERATOR_H
