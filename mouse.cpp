
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "mouse.h"
#include "scene.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <QDebug>

#define SCALE 36000

const qreal Pi = M_PI;
const qreal TwoPi = 2 * M_PI;


static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Mouse::Mouse(QObject *parent)
    : angle(0), speed(0), mouseEyeDirection(0),
      color(200,200,200)
{
    setRotation(0);
    x_old=0;
    y_old=0;
}

QRectF Mouse::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);

}

/*经纬度更新函数*/
void Mouse::upData(double x,double y)
{
   // qDebug()<<"Mouse->upDate x  y"<<x<<y;
    x_new = (x-x_original_globe)*SCALE+ROWX/2;
    y_new = (y-y_original_globe)*SCALE+ROWY/2;

    if(x_new == x_old && y_new == y_old)
        return;

    //sadvance(1);


    QLineF lineTo(QPointF(x_old, y_old), QPointF(x_new, y_new));

    setRotation(90-lineTo.angle());
    //setPos(mapToParent(0, -(3 + sin(speed) * 3)));
    setPos(x_new,y_new);

    emit view(x_new,y_new);
    emit drow(mapToParent(-40,0),mapToParent(0,0),mapToParent(40,0));
    x_old = x_new;
    y_old = y_new;

}

/*
=======================================
  设置坐标中心原始经纬度
=======================================
*/
void Mouse::setOriginalData(double x, double y)
{
    //原始经纬度坐标
    x_original_globe = x;
    y_original_globe = y;

    x_old = 0;
    y_old = 0;

}
/*
void Mouse::advance(int step)
{
    if (!step)
        return;

    //x_new = x_old + QRandomGenerator::global()->bounded(5);
    //y_new = y_old + QRandomGenerator::global()->bounded(0);


    QLineF lineTo(QPointF(x_old, y_old), QPointF(x_new, y_new));

    setRotation(90-lineTo.angle());
    //setPos(mapToParent(0, -(3 + sin(speed) * 3)));
    setPos(x_new,y_new);

    emit view(x_new,y_new);
    emit drow(mapToParent(-40,0),mapToParent(0,0),mapToParent(40,0));
    x_old = x_new;
    y_old = y_new;

}
*/
