#ifndef CRENDER3D_H
#define CRENDER3D_H

#include <math.h>
#include <QVector>
#include <QPainter>
#include <algorithm>
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>

#include "CSimuladorTemperatura.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CRender3D; }
QT_END_NAMESPACE

class CRender3D : public QMainWindow
{
    Q_OBJECT

public:
    CRender3D( QWidget *parent = nullptr);
    CRender3D( CSimuladorTemperatura *simulador, QWidget *parent = nullptr);
    ~CRender3D();
protected:
    void paintEvent(QPaintEvent *event) override;

    QVector3D rotate(QVector3D a);
    QColor getRGB(double x, double min, double max);

    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    void minimizeAngles();
    void createPoints();
    void createTriangles();

    QVector<bool> edges(int i, int j, int g);
    QVector<QVector3D> createCube(QVector3D point);
    QVector3D produtoVetorial(QVector3D origem, QVector3D a, QVector3D b);


private:
    int size;
    int timerId;
    QImage *mImage;
    QPoint mousePos;
    int size_x, size_y;
    int margin_x = 250;
    int margin_y = 250;
    double angle_x = 0.0;
    double angle_y = 0.0;
    double angle_z = 0.0;
    double distance = 1.0;
    bool mousePress = false;
    bool corMaterial = false;
    const float PI = 3.141592;
    double dx = 1, dy = 1, dz = 2;
    CSimuladorTemperatura *simulador;
    QVector<QVector3D> drawCube;
    QVector<QVector3D> triangles;
    QVector<QColor> colorsMaterial;
    QVector<QColor> colorsTemperature;
    QVector<QVector<QVector3D>> cube;
    QVector<QVector<bool>> activeEdges;

};
#endif // MAINWINDOW_H
