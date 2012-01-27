#ifndef GAMES_H
#define GAMES_H
#include <QStringList>
#include <QStringListModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"


class Games : public MainWindow
{
public:
    Games();
    QStringList listaGier;
    QStringListModel *model;
};

#endif // GAMES_H
