#include "mainwindow.h"

#include <QEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QtMath>

constexpr int kSceneWidth = 800;
constexpr int kSceneHeight = 600;

constexpr int kRectWidth = 60;
constexpr int kRectHeight = 40;

constexpr int kStarMin = 30;
constexpr int kStarMax = 60;
constexpr int kStarVertex = 5;

constexpr int kEllipseMin = 40;
constexpr int kEllipseMax = 60;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene{kSceneWidth / 2 - kSceneWidth, kSceneHeight / 2 - kSceneHeight, kSceneWidth, kSceneHeight},
      current_figure(0)
{
    view = new QGraphicsView(this);
    view->setScene(&scene);
    view->installEventFilter(this);
    view->setRenderHint(QPainter::Antialiasing);

    filter = new MyGraphicsItem();
    scene.addItem(filter);

    setCentralWidget(view);
    setWindowTitle("My Figures!");

    make_figure.push_back([this](int x, int y) {return drawRect(x, y);});
    make_figure.push_back([this](int x, int y) {return drawEllipse(x, y);});
    make_figure.push_back([this](int x, int y) {return drawStar(x, y);});

    srand(time(0));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::eventFilter(QObject *watched, QEvent *event){

    if (watched != view)
        return false;
    if (event->type() == QEvent::MouseButtonPress) {
        auto mouse_event = static_cast<QMouseEvent*>(event);
        if (mouse_event->button() == Qt::LeftButton) {
            auto item = make_figure[current_figure](mouse_event->x(), mouse_event->y());
            if(++current_figure == make_figure.size())
                current_figure = 0;
            item->installSceneEventFilter(filter);
            return true;
        }
    }
    return false;
}

QGraphicsItem *MainWindow::drawRect(int x, int y)
{
    QPointF tlp = view->mapToScene(x - kRectWidth / 2, y - kRectHeight / 2);
    QPointF brp = view->mapToScene(x + kRectWidth / 2, y + kRectHeight / 2);
    return scene.addRect(QRectF(tlp, brp), QPen{Qt::NoPen}, createBrush());

}

QGraphicsItem *MainWindow::drawEllipse(int x, int y)
{
    QPointF tlp = view->mapToScene(x - kEllipseMin / 2, y - kEllipseMax / 2);
    QPointF brp = view->mapToScene(x + kEllipseMin / 2, y + kEllipseMax / 2);
    return scene.addEllipse(QRectF(tlp, brp), QPen{Qt::NoPen}, createBrush());

}

QGraphicsItem *MainWindow::drawStar(int x, int y)
{
    QVector<QPointF> pt;
    double ang = qDegreesToRadians(360.0/(kStarVertex*2));
    double cur = qDegreesToRadians(-90.0);
    for(int i=0; i<kStarVertex; ++i) {
        pt.push_back(view->mapToScene(x+kStarMax*qCos(cur)/2, y+kStarMax*qSin(cur)/2));
        cur+=ang;
        pt.push_back(view->mapToScene(x+kStarMin*qCos(cur)/2, y+kStarMin*qSin(cur)/2));
        cur+=ang;
    }
    return scene.addPolygon(QPolygonF(pt), QPen{Qt::NoPen}, createBrush());
}

QBrush MainWindow::createBrush()
{
    return QBrush(QColor(rand() % 256, rand() % 256, rand() % 256, 100 + rand() % 156));
}


