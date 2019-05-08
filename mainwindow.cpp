#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <QDebug>
#include <QRandomGenerator>

#include "guidocwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupDock();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDock()
{

   QDockWidget *map1 = new GuiDocWidget(tr("航迹图"), this,Qt::WindowFlags(0));
   addDockWidget(Qt::RightDockWidgetArea, map1);


}

void MainWindow::viewCentor(qreal cx,qreal cy)
{
    //myView->setSceneRect(cx-300,cy-300,600,600);
}

void MainWindow::timeProcess()
{
    static double x = 121.845269;
    static double y = 30.419375;
    mouse->upData(x,y);
    x = x+0.00005;
    double aa =QRandomGenerator::global()->bounded(10) ;
    y = y+aa/50000 ;
    qDebug()<<"timeProcess x y  aa"<<x<<y<<aa;
}

