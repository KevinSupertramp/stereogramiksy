#ifndef STEREOGRAMGENERATOR_H
#define STEREOGRAMGENERATOR_H

#include<iostream>
#include<QtGui>

#include "mainwindow.h"

class StereogramGenerator : MainWindow
{
    public:
        StereogramGenerator();
        ~StereogramGenerator();

        inline void setImage(QImage *img){imageOrg = img;}
        inline QImage* getImage(){return imageStereogram;}

        void generate(int convex);
        QImage drawRectOnImage(QPixmap &pix, int maxX, int maxY);

        void CalculateImageDepth(QVector<QVector<double> > &imageDepth, int convex); //(between 0 and 1)

    private:
        QPixmap     *originalPixelmap;
        QImage      *imageOrg;
        QImage      *imageOrgCpy;
        QImage      *imageStereogram;
        QImage      *tmp;


        // wywalilem
};

#endif // STEREOGRAMGENERATOR_H
