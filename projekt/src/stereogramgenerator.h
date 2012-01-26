#ifndef STEREOGRAMGENERATOR_H
#define STEREOGRAMGENERATOR_H

#include<iostream>
#include<QtGui>

class StereogramGenerator
{
    public:
        StereogramGenerator();
        ~StereogramGenerator();

        inline void setImage(QImage *img){imageOrg = img;}
        inline QImage* getImage(){return imageStereogram;}

        void generate(int convex);

        void CalculateImageDepth(QVector<QVector<float> > &imageDepth, int convex); //(between 0 and 1)

        inline int DecalageSelonLaCouleur(int ndg)
        {
                         //valeurs possibles :
                         // 1;2 etc.. ancré dans le fond
                         // -1;-2 etc.. devant le fond

            // if(ndg != 255)
            // return -3;

            int ndg2=256-ndg;
            return -4*((float)ndg2/256);

        }


    private:
        QPixmap     *originalPixelmap;
        QImage      *imageOrg;
        QImage      *imageOrgCpy;
        QImage      *imageStereogram;
        QImage      *tmp;


        // wywalilem
};

#endif // STEREOGRAMGENERATOR_H
