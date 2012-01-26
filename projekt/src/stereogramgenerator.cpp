#include "stereogramgenerator.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <cstdlib>

StereogramGenerator::StereogramGenerator()
{
    // inicjalizacja zmiennych
    //imageOrg.fill(0);
    //imageStereogram.fill(0);

    qDebug() << "Konstruktor klasy: SteogramGenerator()";
}

StereogramGenerator::~StereogramGenerator()
{
    delete originalPixelmap;
}



                                                        /* Algorithm for drawing an autostereogram  */
#define round(X) (int)((X)+0.5)                         /* Often need to round rather than truncate */
#define DPI 96                                          /* Output device has 72 pixels per inch */
#define E round(2.5*DPI)                                /* Eye separation is assumed to be 2.5 in */
#define mu (1/3.0)                                      /* Depth of field (fraction of viewing distance) */
#define separation(Z) round((1-mu*Z)*E/(2-mu*Z))        /* Stereo separation corresponding to position Z */
#define far separation(0)                               /* ... and corresponding to far plane, Z=0 */
//#define maxX 768                                        /* Image and object are both maxX by maxY pixels */
//#define maxY 256

void StereogramGenerator::generate()
{
    *imageOrg = imageOrg->scaledToHeight(1080);
    *imageOrg = imageOrg->scaledToWidth(720);
    int maxX = imageOrg->width();
    int maxY = imageOrg->height();

    qDebug() << " 2 " << maxX << " " << maxY;

    originalPixelmap = new QPixmap(imageOrg->width(),imageOrg->height());
    originalPixelmap->fromImage(*imageOrg);

//    imageStereogram = new QImage(maxX,maxY,QImage::Format_RGB32);

    imageStereogram = new QImage(maxX,maxY,QImage::Format_RGB32);

//    float Z[maxX][maxY];

      QVector<QVector<float> > Z;


//    float **Z= new float *[maxX];
//    for(int i=0;i<maxY;++i)
//    {
//        Z[i]= new float[maxY];
//    }

//    tmp = new QImage();
//    tmp = new QImage(maxX,maxY,QImage::Format_RGB32);
//    *tmp = imageOrg->copy();


    // calculate depth
    for(int x=0;x<imageOrg->width();++x)
    {
        QVector<float> vtmp;
        vtmp.clear();
        for(int y=0;y<imageOrg->height();++y)
        {
//            Z[x][y] = 1 - (qGray(imageOrg->pixel(x,y))/255.0) ;
            vtmp.append((float)(1 - (qGray(imageOrg->pixel(x,y))/255.0)));
//            Z.at(x).at(y) << (float)(1 - (qGray(imageOrg->pixel(x,y))/255.0));
            //qDebug() << x << y << Z[x][y];
        }
        Z.append(vtmp);
    }
    // end o calculation
    /////// tutaj powinno dzia³aæ - ale niestety nie dzia³a góra


    for(int y=0;y<maxY;++y)
    {
        unsigned int pix[maxX];
        int same[maxY];

        int s;
        int left, right;

        for(int x=0;x<maxX;++x)
            same[x]=x;

        for(int x=0;x<maxX;++x)
        {
//            s = separation(Z[x][y]);
             s = separation(Z.at(x).at(y));

            left = x - s/2;
            right = left + s;

            if(0 <= left && right < maxX)
            {
                int visible;                                        /* First, perform hidden-surface removal */
                int t=1;                                            /* We will check the points (x-t,y) and (x+t,y) */
                float zt;                                           /* Z-coord of ray at these two points */

                do
                {
//                    zt = Z[x][y] + 2*(2 - mu*Z[x][y])*t/(mu*E);
//                    visible = Z[x-t][y]<zt && Z[x+t][y]<zt;             /* False if obscured */
                    zt = Z.at(x).at(y) + 2*(2 - mu*Z.at(x).at(y))*t/(mu*E);
                    visible = Z.at(x-t).at(y) < zt && Z.at(x+t).at(y) < zt;             /* False if obscured */



                    t++;
                }
                while (visible && zt < 1);                        /*  Done hidden-surface removal  ... */

                if (visible)
                {                                      /*  ... so record the fact that pixels at */
                    int l = same[left];                                 /* ... left and right are the same */
                    while (l != left && l != right)
                    if (l < right)
                    {                                    /* But first, juggle the pointers ... */
                        left = l;                                           /* ... until either same[left]=left */
                        l = same[left];                                     /* ... or same[left]=right */
                    }
                    else
                    {
                        same[left] = right;
                        left = right;
                        l = same[left];
                        right = l;
                    }

                same[left] = right; /* This is where we actually record it */
                }
            }
        }

        for (int x=maxX-1 ; x>= 0 ; x--)
        {                                   /*  Now set the pixels on this scan line */
            if (same[x] == x) pix[x] = qrand()&1;/* Free choice; do it randomly */
            else pix[x] = pix[same[x]]; /* Constrained choice; obey constraint */

            //qDebug() << x << y << pix[x];
            imageStereogram->setPixel(x, y, pix[x]*16775930);
        }
    }
}

void StereogramGenerator::CalculateImageDepth()
{
}
