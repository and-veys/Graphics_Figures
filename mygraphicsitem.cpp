#include "mygraphicsitem.h"

#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>



Moving::Moving():moving(false)
{

}

void Moving::start(QPointF &&ms, QGraphicsItem * it)
{
    moving = true;
    point_mouse = ms;
    point_item = it->pos();
}

void Moving::end()
{
    moving = false;
}

void Moving::move(const QPointF &ms, QGraphicsItem * it)
{
    if(moving) {
        point_item = point_item - (point_mouse - ms);
        it->setPos(point_item);
    }
}

MyGraphicsItem::MyGraphicsItem():QGraphicsItem()
{

}

MyGraphicsItem::~MyGraphicsItem()
{


}

bool MyGraphicsItem::sceneEventFilter(QGraphicsItem * item, QEvent * event) {

    if (event->type() == QEvent::GraphicsSceneMousePress) {
        auto mouse_event = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (mouse_event->button() == Qt::RightButton) {
            item->scene()->removeItem(item);
            return true;
        }
        else if(mouse_event->button() == Qt::LeftButton){
            moving.start(mouse_event->pos(), item);
            return true;
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        auto mouse_event = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (mouse_event->button() == Qt::LeftButton) {
            moving.end();
            return true;
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseMove) {
        auto mouse_event = static_cast<QGraphicsSceneMouseEvent*>(event);
        moving.move(mouse_event->pos(), item);
        return true;
    }
    return false;
}
