#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mygraphicsitem.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

private:
    bool eventFilter(QObject *watched, QEvent *event) override;

    QGraphicsItem * drawRect(int x, int y);
    QGraphicsItem * drawEllipse(int x, int y);
    QGraphicsItem * drawStar(int x, int y);
    QBrush createBrush();

    QGraphicsScene scene;
    MyGraphicsItem * filter;
    QGraphicsView * view;
    QVector<std::function <QGraphicsItem *(int, int)>> make_figure;
    int current_figure;
};
#endif // MAINWINDOW_H
