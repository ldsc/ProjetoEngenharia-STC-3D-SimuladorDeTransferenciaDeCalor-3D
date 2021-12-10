#ifndef C3D_H
#define C3D_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <math.h>
#include <QMouseEvent>
#include <omp.h>

#include "CSimuladorTemperatura.h"

QT_BEGIN_NAMESPACE
namespace Ui { class C3D; }
QT_END_NAMESPACE

class C3D : public QMainWindow
{
    Q_OBJECT

public:
    C3D( QWidget *parent = nullptr);
    C3D( CSimuladorTemperatura *simulador, QWidget *parent = nullptr);
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

    void minimizeAngles();
    void createPoints();
    void createTriangles();

    QVector<bool> edges(int i, int j, int g);
    QVector<QVector3D> createCube(QVector3D point);
    QVector3D produtoVetorial(QVector3D origem, QVector3D a, QVector3D b);

private:
    QPoint mousePos;
    int timerId;
    QImage *mImage;
    int size_x, size_y;
    double angle_x = 0.0;
    double angle_y = 0.0;
    double angle_z = 0.0;
    double distance = 1.0;
    int margin_x = 250;
    bool mousePress = false;
    int margin_y = 250;
    int size;
    int MAX_THREADS = omp_get_max_threads()-5;
    const float PI = 3.141592;
    double dx = 1, dy = 1, dz = 2;
    QVector<QVector<QVector3D>> cube;
    QVector<QVector<bool>> activeEdges;
    QVector<QColor> colors;
    QVector<QVector3D> drawCube;
    QVector<QVector3D> triangles;
    CSimuladorTemperatura *simulador;

};
#endif // MAINWINDOW_H
