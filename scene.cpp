#include "scene.h"

#include <math.h>

Scene::Scene(QObject *parent):
    QGraphicsScene(parent)
{
    setSceneRect(COLX, COLY, ROWX, ROWY);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    //坐标网格
    for(int i=COLX;i<=ROWX;i++){         //经度
        if(i%MAXR==0){
            QGraphicsLineItem *pItemleft = new QGraphicsLineItem();
            QPen penleft = pItemleft->pen();
            penleft.setColor(QColor(184,134,11));
            penleft.setWidth(0.5);
            pItemleft->setPen(penleft);
            pItemleft->setLine(i,COLX,i,ROWX);
            addItem(pItemleft);

        }
    }

    for(int j=COLY;j<=ROWY;j++){            //纬度
        if(j%MAXR==0){
            QGraphicsLineItem *pItemright = new QGraphicsLineItem();
            QPen penleft = pItemright->pen();
            penleft.setColor(QColor(10,134,184));
            penleft.setWidth(0.5);
            pItemright->setPen(penleft);
            pItemright->setLine(COLY,j,ROWY,j);
            addItem(pItemright);
        }
    }

    /*
    QPolygonF myPolygon1;
        myPolygon1 << QPointF(0,10) << QPointF(20,10);
        QPolygonF myPolygon2;
        myPolygon2 << QPointF(10,0) << QPointF(10,20);
        QPixmap pixmap(20, 20);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);

        QVector<qreal> dashes;//line style--虚线
        qreal space = 2;
        dashes << 2 << space << 2 <<space;
        QPen pen(Qt::lightGray,1);
        pen.setDashPattern(dashes);
        pen.setWidth(1);

        painter.setPen(pen);
        painter.translate(0, 0);
        painter.drawPolyline(myPolygon1);
        painter.drawPolyline(myPolygon2);
        setBackgroundBrush(pixmap);
       */
}

//绘制经纬度坐标值
void Scene::drowGlobe(double x, double y)
{
    for(int i=-TITEM/2;i<=TITEM/2;i++)//经度
    {
        int a = i+TITEM/2;
        txtitem_x[a] = new QGraphicsTextItem();
        txtitem_x[a]->setPlainText(decToint(x+(double)i*SIN)+"E");
        txtitem_x[a]->setPos(QPointF(ROWX/2+(double)i*100-25, ROWX/2-290));
        txtitem_x[a]->setDefaultTextColor(QColor(184,134,11));  // 文本色
        addItem(txtitem_x[a]);

    }

    for(int i=-TITEM/2;i<=TITEM/2;i++)//纬度
    {
        int a = i+TITEM/2;
        txtitem_Y[a] = new QGraphicsTextItem();
        txtitem_Y[a]->setPlainText(decToint(y+((double)i+1)*SIN)+"N");
        txtitem_Y[a]->setPos(QPointF(ROWY/2-300,ROWY/2+(double)i*100-20));
        txtitem_Y[a]->setDefaultTextColor(QColor(10,134,184));  // 文本色
        addItem(txtitem_Y[a]);

    }
}

void Scene::upDataGlobe(qreal w, qreal h)
{
    for(int i=-TITEM/2;i<=TITEM/2;i++)//经度
    {
        //txtitem_x[i+4]->setPos(QPointF(ROWX/2+(double)i*100-25, h-viewSizeHight/2+10));
        txtitem_x[i+TITEM/2]->setPos(QPointF(ROWX/2+(double)i*100-25, h+10));
    }

    for(int i=-TITEM/2;i<=TITEM/2;i++)//纬度
    {
        //txtitem_Y[i+4]->setPos(QPointF(w-viewSizeWight/2,ROWY/2+(double)i*100-20));
        txtitem_Y[i+TITEM/2]->setPos(QPointF(w,ROWY/2+(double)i*100-20));
    }
}

void Scene::upDataViewSize(qreal w, qreal h)
{
     viewSizeHight = h;
     viewSizeWight = w;
}

void Scene::drowLine(QPointF lpot, QPointF cpot, QPointF rpot)
{
    //左侧扫迹
    QGraphicsLineItem *pItemleft = new QGraphicsLineItem();
    QPen penleft = pItemleft->pen();
    penleft.setColor(QColor(230,0, 0));
    penleft.setWidth(1);
    pItemleft->setPen(penleft);
    pItemleft->setLine(QLineF(lpot.x(), lpot.y(), cpot.x(), cpot.y()));

    //右侧航迹
    QGraphicsLineItem *pItemright = new QGraphicsLineItem();
    QPen penright = pItemright->pen();
    penright.setColor(QColor(0,230, 0));
    penright.setWidth(1);
    pItemright->setPen(penright);
    pItemright->setLine(QLineF(rpot.x(), rpot.y(), cpot.x(), cpot.y()));

    //添加
    addItem(pItemleft);
    addItem(pItemright);

}


QString Scene::decToint(double x)
{
    double dou;  //保存小数
    double dd = floor(x);
    dou = x-dd;
    double hh = floor(dou * 60);
    dou = dou*60 - hh;
    double ss = floor(dou * 60);

    QString y = QString::number(dd,'f',0) +"°" + QString::number(hh,'f',0) +"\'" + QString::number(ss,'f',0) + "\"" ;
    return y;

}

