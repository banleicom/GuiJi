#include "guidocwidget.h"

#include <QDebug>
#include <QRandomGenerator>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

GuiDocWidget::GuiDocWidget(const QString &title, QMainWindow *parent,Qt::WindowFlags flags):
    QDockWidget(parent,flags),
    sliderNum(250)
{
    setObjectName(QLatin1String(" Dock Widget"));
    setWindowTitle(objectName() + QLatin1String(" [*]"));

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QToolButton *zoomInIcon = new QToolButton;
    zoomInIcon->setAutoRepeat(true);
    zoomInIcon->setAutoRepeatInterval(33);
    zoomInIcon->setAutoRepeatDelay(0);
    zoomInIcon->setIcon(QPixmap(":/soure/zoomin.png"));
    zoomInIcon->setIconSize(iconSize);
    QToolButton *zoomOutIcon = new QToolButton;
    zoomOutIcon->setAutoRepeat(true);
    zoomOutIcon->setAutoRepeatInterval(33);
    zoomOutIcon->setAutoRepeatDelay(0);
    zoomOutIcon->setIcon(QPixmap(":/soure/zoomout.png"));
    zoomOutIcon->setIconSize(iconSize);
    QToolButton *printButton = new QToolButton;
    printButton->setIconSize(iconSize);
    printButton->setIcon(QIcon(QPixmap(":/soure/fileprint.png")));

    QHBoxLayout *SliderLayout = new QHBoxLayout;
    SliderLayout->addWidget(zoomInIcon);
    SliderLayout->addWidget(zoomOutIcon);
    SliderLayout->addStretch();
    SliderLayout->addWidget(printButton);

    guiScence = new Scene(this);
    guiMouse = new Mouse(this);
    guiMouse->setPos(ROWX/2, ROWY/2);
    guiMouse->setOriginalData(121.845269,30.419375);
    guiScence->drowGlobe(121.845269,30.419375);
    guiScence->addItem(guiMouse);
    connect(guiMouse,SIGNAL(drow(QPointF,QPointF,QPointF)),
            guiScence,SLOT(drowLine(QPointF,QPointF,QPointF)));
    connect(guiMouse,SIGNAL(view(qreal,qreal)),this,SLOT(viewCentor(qreal,qreal)));

    myView = new QGraphicsView;
    myView->setScene(guiScence);
    myView->setRenderHint(QPainter::Antialiasing);
   myView->setBackgroundBrush(Qt::black);
    myView->setCacheMode(QGraphicsView::CacheBackground);
    myView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    myView->setDragMode(QGraphicsView::ScrollHandDrag);
    myView->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Colliding Mice"));
    myView->resize(600, 600);
    myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //myView->setSceneRect(ROWX/2-300,ROWY/2-300,600,600);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(SliderLayout, 0, 0);
    topLayout->addWidget(myView, 1, 0);
    topLayout->setMargin(0);
    topLayout->setSpacing(0);

    QWidget *abc = new QWidget(this);
    abc->setLayout(topLayout);
    setWidget(abc);

    QTimer *timers = new QTimer(this);
    connect(timers,SIGNAL(timeout()),this,SLOT(timeProcess()));
    timers->start(1000);

    connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(printButton, SIGNAL(clicked()), this, SLOT(print()));
}


void GuiDocWidget::resizeEvent(QResizeEvent *event)
{
   vieWidth= myView->sceneRect().width();
   viewHight= myView->sceneRect().height();

}

void GuiDocWidget::viewCentor(qreal cx,qreal cy)
{
    myView->setSceneRect(cx-vieWidth/2,cy-viewHight/2,vieWidth,viewHight);
    guiScence->upDataGlobe(myView->mapToScene(0,0).rx(),myView->mapToScene(0,0).ry());
}

void GuiDocWidget::zoomIn()
{
    sliderNum+=10;
    qreal scale = qPow(qreal(2), (sliderNum - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    myView->setMatrix(matrix);

    vieWidth= myView->sceneRect().width();
    viewHight= myView->sceneRect().height();
}

void GuiDocWidget::zoomOut()
{
    sliderNum-=10;
    qreal scale = qPow(qreal(2), (sliderNum - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    myView->setMatrix(matrix);

    vieWidth= myView->sceneRect().width();
    viewHight= myView->sceneRect().height();
}

void GuiDocWidget::print()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        myView->render(&painter);
    }
}

void GuiDocWidget::timeProcess()
{
    static double x = 121.845269;
    static double y = 30.419375;
    guiMouse->upData(x,y);
    x = x+0.0001;
    y = y+0.0001;
    double aa =QRandomGenerator::global()->bounded(10) ;
}

