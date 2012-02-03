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
        //delete _imageToGenerate;
    }
}

void StereogramGenerator::setDefault(int DPI, double distanceBetweenEyes)
{
    _DPI                    = DPI;
    _distanceBetweenEyes    = distanceBetweenEyes; // odleglosc obiektow
    _eyeSeparation          = roundSomething(_distanceBetweenEyes*DPI);
    _depthOfField           = (1.0/3.0);
    _farOfDots              = separateSomething(0);
    _wygenerowano           = false;
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

void StereogramGenerator::generate(int convex, int color, bool circles)
{
    if(_wygenerowano)
        delete _imageGeneratedStereogram;

    if(_imageToGenerate->height() >= 720)
        *_imageToGenerate = _imageToGenerate->scaledToHeight(720);
    else if(_imageToGenerate->width()>= 1280)
        *_imageToGenerate = _imageToGenerate->scaledToWidth(1280);

    _widthOfImage_X = _imageToGenerate->width();
    _heightOfImage_Y = _imageToGenerate->height();

    _imageGeneratedStereogram = new QImage(_widthOfImage_X,_heightOfImage_Y,QImage::Format_RGB32);

    double **imageDepth = 0;
    imageDepth = new double*[_widthOfImage_X];
    for(int i=0;i<_widthOfImage_X;++i)
        imageDepth[i] = new double[_heightOfImage_Y];

    calculateImageDepth(imageDepth,convex);

    emit setStatusBarLabel("Generowanie");

    for(int y=0;y<_heightOfImage_Y;++y)
    {
        unsigned int pix[_widthOfImage_X];
        int same[_heightOfImage_Y];

        int s;
        int left, right;

        for(int x=0;x<_widthOfImage_X;++x)
            same[x]=x;

        for(int x=0;x<_widthOfImage_X;++x)
        {
            s = separateSomething(imageDepth[x][y]);

            left = x - s/2;
            right = left + s;

            if(0 <= left && right < _widthOfImage_X)
            {
                int visible;                                        /* First, perform hidden-surface removal */
                int t=1;                                            /* We will check the points (x-t,y) and (x+t,y) */
                float zt;                                           /* Z-coord of ray at these two points */

                do
                {
                                                                                            /* False if obscured */
                    zt = imageDepth[x][y] + 2*(2 - _depthOfField*imageDepth[x][y])*t/(_depthOfField*_eyeSeparation);
                    visible = imageDepth[x-t][y] < zt && imageDepth[x+t][y] < zt;             /* False if obscured */

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

        for (int x=_widthOfImage_X-1 ; x>= 0 ; x--)
        {                                   /*  Now set the pixels on this scan line */
            if (same[x] == x) pix[x] = qrand()&1;/* Free choice; do it randomly */
            else pix[x] = pix[same[x]]; /* Constrained choice; obey constraint */

            switch (color)
            {
            case 0:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*16775930); /* White */
                break;
            case 1:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*14210000); /* Gray */
                break;
            case 2:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*11500000); /* Purple */
                break;
            case 3:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*11800000); /* Violet */
                break;
            case 4:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*14245000); /* Pink */
                break;
            case 5:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*14300000); /* Scarlet */
                break;
            case 6:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*16000000); /* Red */
                break;
            case 7:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*14250000); /* Orange */
                break;
            case 8:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*9000000); /* Brown */
                break;
            case 9:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*14272000); /* Yellow */
                break;
            case 10:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*9300000); /* Pistachio */
                break;
            case 11:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*125000); /* Green */
                break;
            case 12:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*1830000); /* Sea green */
                break;
            case 13:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*1900000); /* Sky blue */
                break;
            case 14:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*300000); /* Indigo */
                break;
            case 15:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*255); /* Blue */
                break;
            case 16:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*16000000/_imageToGenerate->width()*x); /* Multi-color columns */
                break;
            case 17:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*16000000/_imageToGenerate->height()*y); /* Multi-color rows */
                break;
            default:
                _imageGeneratedStereogram->setPixel(x, y, pix[x]*16775930); /* White */
                break;
            }
        }

        emit setStatusBarLabel(QString("Generowanie: ")+QString("%1").arg((y*100)/(_heightOfImage_Y-1))+QString("%"));
    }

    emit setStatusBarLabel(QString("Generowanie: 100% | Wygenerowano obrazek: ")+QString("%1").arg(_widthOfImage_X)+QString("x")+QString("%1").arg(_heightOfImage_Y));

    if(circles)
        drawCirclesOnImage(_widthOfImage_X,_heightOfImage_Y);

    // czyszczenie pamiêci
    for(int i=0;i<_widthOfImage_X;++i)
        delete [] imageDepth[i];
    delete [] imageDepth;

    _wygenerowano = true;
}

void StereogramGenerator::calculateImageDepth(double **imageDepth, int convex)
{
    float tmp;
    if(convex == 1)
        tmp = 1.0;
    else
        tmp=-1.0;

    for(int x=0;x<_imageToGenerate->width();++x)
    {
        for(int y=0;y<_imageToGenerate->height();++y)
        {
            imageDepth[x][y] = ((double)(convex - (qGray(_imageToGenerate->pixel(x,y))/255.0)*tmp));
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
