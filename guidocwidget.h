#ifndef GUIDOCWIDGET_H
#define GUIDOCWIDGET_H

#include <QDockWidget>
#include "scene.h"
#include "mouse.h"

class GuiDocWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit GuiDocWidget(const QString &title, QMainWindow *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);

protected:
    void resizeEvent(QResizeEvent *e) override;
private:

    Scene *guiScence;
    Mouse *guiMouse;
    QGraphicsView *myView;

    qreal vieWidth;  //视口宽
    qreal viewHight;  //视口高

    int sliderNum;

private slots:
    void timeProcess();
    void viewCentor(qreal,qreal );

    void zoomIn();
    void zoomOut();
    void print();
};

#endif // GUIDOCWIDGET_H
