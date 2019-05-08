#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "scene.h"
#include "mouse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupDock();
private:
    static const int MouseCount = 1;
    QGraphicsView *myView;
    Scene *myScene;
    Mouse *mouse;

private:
    Ui::MainWindow *ui;

private slots:
    void timeProcess();
    void viewCentor(qreal,qreal );

};

#endif // MAINWINDOW_H
