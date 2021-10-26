#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>/// pegar acoes/posicao do mouse
#include <QPainter> /// desenhar pixels
#include <iostream> /// cout
#include <QFileDialog>
#include <QImage> /// desenhar pixels
#include <QColor> /// escolher a cor dos pixels
#include <string>

#include "CSimuladorTemperatura.h"
#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint m_mousePos;
    QPixmap pixmap;
    QImage *mImage;

    CSimuladorTemperatura *simulador;

    int timerId;
    int parallelType = 2;
    int size = 300;
    int currentGrid = 0;
    int space_between_draws = 50;
    int left_margin = 20, up_margin = 40;
    bool runningSimulator = false;
    QPoint studyPoint = QPoint(0,0);
    int studyGrid;
    QVector<double> time, temperature;

protected:
    void start_buttons();
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *e) override;

    QColor calcRGB(double temperatura);
    void runSimulator();
    void timerEvent(QTimerEvent *e) override;

private slots:
    void on_pushButton_clicked();
    void on_gridDownButton_clicked();
    void on_gridUpButton_clicked();

    void makePlot1();
    void makePlot2();
    void makePlot3();
    void makePlot4();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
};
#endif
