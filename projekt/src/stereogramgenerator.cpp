#include "stereogramgenerator.h"

StereogramGenerator::StereogramGenerator(QObject *parent) :
    QObject(parent)
{
    // uzywac
    qDebug() << "Konstruktor klasy: SteogramGenerator()";
    setDefault(96,2.7);
}


StereogramGenerator::~StereogramGenerator()
{
    if(_wygenerowano)
    {
        delete _imageGeneratedStereogram;
    }
}

void StereogramGenerator::setDefault(int DPI, double distanceBetweenEyes)
{
    _DPI                    = DPI;
    _distanceBetweenEyes    = distanceBetweenEyes; // odleglosc obiektow
    _eyeSeparation          = roundSomething(_distanceBetweenEyes*_DPI);
    _depthOfField           = (1.0/3.0);
    _farOfDots              = separateSomething(0);
    _wygenerowano           = false;
}

void StereogramGenerator::changeDefault(int currentDPI, int currentDistanceBetweenEyes)
{
    switch(currentDPI)
    {
        case 0:     _DPI = 76;      break;
        case 1:     _DPI = 96;      break;
        case 2:     _DPI = 150;     break;
        default:    _DPI = 96;      break;
    }

    switch(currentDistanceBetweenEyes)
    {
        case 0:     _distanceBetweenEyes = 2.5;     break;
        case 1:     _distanceBetweenEyes = 2.6;     break;
        case 2:     _distanceBetweenEyes = 2.7;     break;
        default:    _distanceBetweenEyes = 2.755;   break;
    }

    _eyeSeparation          = roundSomething(_distanceBetweenEyes*_DPI);
    _depthOfField           = (1.0/3.0);
    _farOfDots              = separateSomething(0);
}

int StereogramGenerator::roundSomething(double something)
{
    return ((int)((something)+0.5));
}

int StereogramGenerator::separateSomething(double something)
{
    return roundSomething((1-_depthOfField*something)*_eyeSeparation/(2-_depthOfField*something));
}

                                                        /* Algorithm for drawing an autostereogram  */
//#define round(X) (int)((X)+0.5)                         /* Often need to round rather than truncate */
//#define DPI 96                                          /* Output device has 72 pixels per inch */
//#define _eyeSeparation round(2.7*DPI)                                /* Eye separation is assumed to be 2.5 in */
//#define _depthOfField (1/3.0)                           /* Depth of field (fraction of viewing distance) */
//#define separation(Z) round((1-_depthOfField*Z)*_eyeSeparation/(2-_depthOfField*Z))        /* Stereo separation corresponding to position Z */
//#define _farOfDots separation(0)                               /* ... and corresponding to _farOfDots plane, Z=0 */

void StereogramGenerator::generate(int convex, int color, bool circles, int size, int keepAspectRatio)
{
    if(_wygenerowano)
    {
        delete _imageGeneratedStereogram;
    }

    _imageCopy = _imageToGenerate;

    Qt::AspectRatioMode aspectModel;
    if(keepAspectRatio!=0)
        aspectModel = Qt::KeepAspectRatio;
    else
        aspectModel = Qt::IgnoreAspectRatio;

    switch(size)
    {
        case 0:     *_imageCopy = _imageToGenerate->scaled(QSize(800,600),aspectModel);         break;
        case 1:     *_imageCopy = _imageToGenerate->scaled(QSize(1024,768),aspectModel);        break;
        case 2:     *_imageCopy = _imageToGenerate->scaled(1280,720,aspectModel);               break;
        case 3:     *_imageCopy = _imageToGenerate->scaled(1920,1080,aspectModel);              break;
        case 4:
            if(_imageToGenerate->height() >= 720)
                *_imageCopy = _imageToGenerate->scaledToHeight(720);
            else if(_imageToGenerate->width()>= 1280)
                *_imageCopy = _imageToGenerate->scaledToWidth(1280);
        break;
        default:    _imageCopy = _imageToGenerate;      break;
    }

    _widthOfImage_X = _imageCopy->width();
    _heightOfImage_Y = _imageCopy->height();

//    qDebug() << "size" << size;
//    qDebug() << _widthOfImage_X << " " << _heightOfImage_Y;

    _imageGeneratedStereogram = new QImage(_widthOfImage_X,_heightOfImage_Y,QImage::Format_RGB32);

    double **imageDepth = 0;
    imageDepth = new double*[_widthOfImage_X];
    for(int i=0;i<_widthOfImage_X;++i)
        imageDepth[i] = new double[_heightOfImage_Y];

    calculateImageDepth(imageDepth,convex);

    emit setStatusBarLabel("Generowanie");

    for(int y=0;y<_heightOfImage_Y;++y)
    {
        unsigned int colorOfPixel[_widthOfImage_X];
        int samePixels[_heightOfImage_Y];

        int stereoSeparationOfPoint;
        int leftEye, rightEye;

        for(int x=0;x<_widthOfImage_X;++x)
            samePixels[x]=x;

        for(int x=0;x<_widthOfImage_X;++x)
        {
            stereoSeparationOfPoint = separateSomething(imageDepth[x][y]);

            leftEye = x - stereoSeparationOfPoint/2;
            rightEye = leftEye + stereoSeparationOfPoint;

            if(0 <= leftEye && rightEye < _widthOfImage_X)
            {
                int isVisible;                                        /* First, perform hidden-surface removal */
                int tmp=1;                                            /* We will check the points (x-tmp,y) and (x+tmp,y) */
                float rayOfImageDepthAtPoint;                                           /* Z-coord of ray at these two points */

                do
                {
                                                                                            /* False if obscured */
                    rayOfImageDepthAtPoint = imageDepth[x][y] + 2*(2 - _depthOfField*imageDepth[x][y])*tmp/(_depthOfField*_eyeSeparation);
                    isVisible = imageDepth[x-tmp][y] < rayOfImageDepthAtPoint && imageDepth[x+tmp][y] < rayOfImageDepthAtPoint;             /* False if obscured */

                    tmp++;
                }
                while (isVisible && rayOfImageDepthAtPoint < 1);                        /*  Done hidden-surface removal  ... */

                if (isVisible)
                {                                      /*  ... so record the fact that pixels at */
                    int left_N_right = samePixels[leftEye];                                 /* ... leftEye and rightEye are the samePixels */
                    while (left_N_right != leftEye && left_N_right != rightEye)
                    if (left_N_right < rightEye)
                    {                                    /* But first, juggle the pointers ... */
                        leftEye = left_N_right;                                           /* ... until either samePixels[leftEye]=leftEye */
                        left_N_right = samePixels[leftEye];                                     /* ... or samePixels[leftEye]=rightEye */
                    }
                    else
                    {
                        samePixels[leftEye] = rightEye;
                        leftEye = rightEye;
                        left_N_right = samePixels[leftEye];
                        rightEye = left_N_right;
                    }

                samePixels[leftEye] = rightEye; /* This is where we actually record it */
                }
            }
        }

        for (int x=_widthOfImage_X-1 ; x>= 0 ; x--)
        {                                   /*  Now set the pixels on this scan line */
            if (samePixels[x] == x) colorOfPixel[x] = qrand()&1;/* Free choice; do it randomly */
            else colorOfPixel[x] = colorOfPixel[samePixels[x]]; /* Constrained choice; obey constraint */

            switch (color)
            {
                case 0:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*16775930); /* White */         break;
                case 1:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*14210000); /* Gray */          break;
                case 2:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*11500000); /* Purple */        break;
                case 3:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*11800000); /* Violet */        break;
                case 4:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*14245000); /* Pink */          break;
                case 5:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*14300000); /* Scarlet */       break;
                case 6:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*16000000); /* Red */           break;
                case 7:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*14250000); /* Orange */        break;
                case 8:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*9000000); /* Brown */          break;
                case 9:     _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*14272000); /* Yellow */        break;
                case 10:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*9300000); /* Pistachio */      break;
                case 11:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*125000); /* Green */           break;
                case 12:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*1830000); /* Sea green */      break;
                case 13:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*1900000); /* Sky blue */       break;
                case 14:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*300000); /* Indigo */          break;
                case 15:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*255); /* Blue */               break;
                case 16:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*16000000/_imageCopy->width()*x); /* Multi-color columns */ break;
                case 17:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*16000000/_imageCopy->height()*y); /* Multi-color rows */   break;
                default:    _imageGeneratedStereogram->setPixel(x, y, colorOfPixel[x]*16775930); /* White */         break;
            }
        }

        emit setStatusBarLabel(QString("Generowanie: ")+QString("%1").arg((y*100)/(_heightOfImage_Y-1))+QString("%"));
    }

    emit setStatusBarLabel(QString("Generowanie: 100% | Wygenerowano obrazek: ")+QString("%1").arg(_widthOfImage_X)+QString("x")+QString("%1").arg(_heightOfImage_Y));

    if(circles)
        drawCirclesOnImage(_widthOfImage_X,_heightOfImage_Y);

    // czyszczenie pami�ci
    for(int i=0;i<_widthOfImage_X;++i)
        delete [] imageDepth[i];
    delete [] imageDepth;

    _wygenerowano = true;
}

void StereogramGenerator::calculateImageDepth(double **imageDepth, int convex)
{
    float tmp;
    if(convex)
        tmp = 1.0;
    else
        tmp=-1.0;

    for(int x=0;x<_imageCopy->width();++x)
    {
        for(int y=0;y<_imageCopy->height();++y)
        {
            imageDepth[x][y] = ((double)(convex - (qGray(_imageCopy->pixel(x,y))/255.0)*tmp));
        }
    }
}

void StereogramGenerator::drawCirclesOnImage(int _widthOfImage_X, int _heightOfImage_Y)
{
    QPainter p;
    p.begin(_imageGeneratedStereogram);
    p.setBrush(QBrush(Qt::black));
    p.setPen(Qt::black);
    p.drawEllipse(_widthOfImage_X/2-_farOfDots/2,_heightOfImage_Y*16/19,20,20);
    p.drawEllipse(_widthOfImage_X/2+_farOfDots/2,_heightOfImage_Y*16/19,20,20);
    p.end();
}
