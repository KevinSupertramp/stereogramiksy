#include "games.h"

Games::Games(QObject *parent) :
    QObject(parent)
{
}

void Games::dziala()
{
    emit setModelOfListView(model);
}

//Games::Games(QObject *parent) :
//    QObject(parent)
//{

////    QFile file("gry/lista.txt");
////    QTextStream in(&file);
////    while (!in.atEnd())
////    {
////         QString line = in.readLine();
////         listaGier.append(line);
////    }
////    listaGier.append("napis");
////     qDebug() << listaGier.count();
////     model = new QStringListModel(listaGier);
////     ui->listView->setModel(model);

//}
