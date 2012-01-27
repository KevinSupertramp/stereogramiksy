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
#define eyeSeparation round(2.755*DPI)                                /* Eye separation is assumed to be 2.5 in */
#define depthOfField (1/2.6)                           /* Depth of field (fraction of viewing distance) */
#define separation(Z) round((1-depthOfField*Z)*eyeSeparation/(2-depthOfField*Z))        /* Stereo separation corresponding to position Z */
#define far separation(0)                               /* ... and corresponding to far plane, Z=0 */
//#define maxX 768                                        /* Image and object are both maxX by maxY pixels */
//#define maxY 256

void StereogramGenerator::generate(int convex)
{
    if(imageOrg->height() >= 720)
        *imageOrg = imageOrg->scaledToHeight(720);
    else if(imageOrg->width()>= 1280)
        *imageOrg = imageOrg->scaledToWidth(1280);

    int maxX = imageOrg->width();
    int maxY = imageOrg->height();

    qDebug() << " 2 " << maxX << " " << maxY;

    originalPixelmap = new QPixmap(imageOrg->width(),imageOrg->height());
    originalPixelmap->fromImage(*imageOrg);

    imageStereogram = new QImage(maxX,maxY,QImage::Format_RGB32);
    imageOrgCpy = new QImage(maxX,maxY,QImage::Format_RGB32);

      QVector<QVector<double> > imageDepth;

    CalculateImageDepth(imageDepth,convex);

    MainWindow::setStatusBar_message("olaBOga");

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
             s = separation(imageDepth.at(x).at(y));

            left = x - s/2;
            right = left + s;

            if(0 <= left && right < maxX)
            {
                int visible;                                        /* First, perform hidden-surface removal */
                int t=1;                                            /* We will check the points (x-t,y) and (x+t,y) */
                float zt;                                           /* Z-coord of ray at these two points */

                do
                {
                                                                                            /* False if obscured */
                    zt = imageDepth.at(x).at(y) + 2*(2 - depthOfField*imageDepth.at(x).at(y))*t/(depthOfField*eyeSeparation);
                    visible = imageDepth.at(x-t).at(y) < zt && imageDepth.at(x+t).at(y) < zt;             /* False if obscured */

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

//    QPixmap *p = new QPixmap(imageStereogram->width(),imageStereogram->height());
//            p->fromImage(*imageStereogram);

//    imageOrgCpy = &(drawRectOnImage(*originalPixelmap,maxX,maxY));
}

void StereogramGenerator::CalculateImageDepth(QVector<QVector<double> > &imageDepth, int convex)
{
    int tmp;
    if(convex == 1)
        tmp = 1;
    else
        tmp=-1;

    // calculate depth
    for(int x=0;x<imageOrg->width();++x)
    {
        QVector<double> vtmp;
        vtmp.clear();
        for(int y=0;y<imageOrg->height();++y)
        {
//            Z[x][y] = 1 - (qGray(imageOrg->pixel(x,y))/255.0) ;
            vtmp.append((float)(convex - (qGray(imageOrg->pixel(x,y))/255.0)*tmp));
//            Z.at(x).at(y) << (float)(1 - (qGray(imageOrg->pixel(x,y))/255.0));
            //qDebug() << x << y << Z[x][y];
        }
        imageDepth.append(vtmp);
    }
    // end o calculation
}

QImage StereogramGenerator::drawRectOnImage(QPixmap &pix, int maxX, int maxY)
{
    QPainter p;
    p.begin(&pix);
    p.setPen(Qt::black);
    p.drawEllipse(maxX/2-far/2,maxY*19/20,30,30);
    p.drawEllipse(maxX/2+far/2,maxY*19/20,30,30);
    p.end();

    return (pix.toImage());

//    imageStereogram->fill(pix);
}
