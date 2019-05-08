#ifndef SCENCE_H
#define SCENCE_H

#include <QtWidgets>
#include "mouse.h"

#define COLX   0
#define COLY   0
#define ROWX   10000
#define ROWY   10000
#define MAXR   100

#define TITEM  99

#define SIN    1/360

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = 0);
    void drowGlobe(double x, double y);
    void upDataGlobe(qreal,qreal);
    void upDataViewSize(qreal,qreal);
private:
    qreal viewSizeHight;
    qreal viewSizeWight;

    QGraphicsTextItem *txtitem_x[TITEM];
    QGraphicsTextItem *txtitem_Y[TITEM];
private slots:
    void drowLine(QPointF lpot, QPointF cpot, QPointF rpot);
    QString decToint(double x);

};

#endif // SCENCE_H
