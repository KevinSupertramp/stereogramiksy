#ifndef GAMES_H
#define GAMES_H
#include <QStringList>
#include <QStringListModel>
#include <QObject>
//#include<QtGui>

class Games : public QObject
{
    Q_OBJECT
public:
    explicit Games(QObject *parent = 0);

    void dziala();

signals:
    void setModelOfListView(QStringListModel *model);
public slots:


public:
    QStringList listaGier;
    QStringListModel *model;
};

#endif // GAMES_H
