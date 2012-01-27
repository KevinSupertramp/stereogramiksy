
#include "games.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Games::Games()
{

    QFile file("gry/lista.txt");
    QTextStream in(&file);
    while (!in.atEnd()) {
         QString line = in.readLine();
         listaGier.append(line);
         }
    listaGier.append("napis");
     qDebug() << listaGier.count();
     model = new QStringListModel(listaGier);
     ui->listView->setModel(model);

}
