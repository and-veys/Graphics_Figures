#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItem>

class Moving {
public:
    Moving();
    void start(QPointF && ms, QGraphicsItem * it);
    void end();
    void move(const QPointF & ms, QGraphicsItem * res);
private:
    QPointF point_item;
    QPointF point_mouse;
    bool moving;

};

class MyGraphicsItem : public QGraphicsItem
{
public:
    MyGraphicsItem();
    ~MyGraphicsItem();

public:
    QRectF boundingRect() const override { return {}; }
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = 0) override {}

protected:
    bool sceneEventFilter(QGraphicsItem *, QEvent *) override;

private:
    Moving moving;

};

#endif // MYGRAPHICSITEM_H
