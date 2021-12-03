#ifndef C3D_H
#define C3D_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <math.h>
#include <QMouseEvent>

#include "CSimuladorTemperatura.h"

QT_BEGIN_NAMESPACE
namespace Ui { class C3D; }
QT_END_NAMESPACE

class C3D : public QMainWindow
{
    Q_OBJECT

public:
    C3D(CSimuladorTemperatura *_simulador, QWidget *parent = nullptr);
    ~C3D();
protected:
    void paintEvent(QPaintEvent *event) override;

    void timerEvent(QTimerEvent *e) override;
    QVector3D rotate(QVector3D a);
    QColor getRGB(int z);
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    void createPoints();

private:
    QPoint mousePos;
    QVector<QVector3D> upperPoints;
    QVector<QVector3D> lowerPoints;
    QVector<QColor> color;
    int timerId;
    QImage *mImage;
    int size_x, size_y;
    double angle_x = 0.0;
    double angle_y = 0.0;
    double angle_z = 0.0;
    double distance = 1.0;
    int margin_x = 250;
    int margin_y = 250;
    bool mousePress = false;
    int size;

    QVector<QVector3D> drawPoints_up;
    QVector<QVector3D> drawPoints_down;

    CSimuladorTemperatura *simulador;

};
#endif // MAINWINDOW_H
